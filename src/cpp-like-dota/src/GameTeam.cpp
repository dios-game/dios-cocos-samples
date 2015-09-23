#include "GameTeam.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "GameCharacter.h"
#include "GoalTeamThink.h"

int GameTeam::m_nextValidId =   0;

GameTeam::GameTeam()
{
    m_teamId        =   m_nextValidId++;
    m_advanceRate   =   0;
    m_teamBrain     =   new GoalTeamThink(this);
    m_teamState     =   GAME_TEAM_STATE_ACTIVE;
    setStayState();
    m_lastUpdateTime    =   0;
}

GameTeam::~GameTeam()
{
    // 析构队伍的同时也析构所有的成员，因为成员属于队伍
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end(); tmpIterator++)
    {
        CC_SAFE_RELEASE_NULL(*tmpIterator);
    }
    m_members.clear();

    CC_SAFE_DELETE(m_teamBrain);
    m_teamBrain =   nullptr;
}

void GameTeam::addMember(GameCharacter* player, int posId)
{
    // player->retain();
    player->setTeam(this);

    // 如果当前位置已经有人了，就会给他一个从0开始的最小的还没有使用的位置
    bool tmpPosIdUsed       =   false;
    map<int, int> tmpUsedIds;
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end(); tmpIterator++)
    {
        auto tmpPosId   =   (*tmpIterator)->getMovingEntity().getFormationPosId();
        tmpUsedIds.insert(map<int, int>::value_type(tmpPosId, tmpPosId));
        if (tmpPosId == posId)
        {
            tmpPosIdUsed    =   true;
        }
    }
    if (!tmpPosIdUsed)
    {
        player->getMovingEntity().setFormationPosId(posId);
        m_members.push_back(player);
    }
    else
    {
        for (auto tmpMinPosIdUnused = 0; tmpMinPosIdUnused < 9 ; tmpMinPosIdUnused++)
        {
            if (tmpUsedIds.find(tmpMinPosIdUnused) == tmpUsedIds.end())
            {
                player->getMovingEntity().setFormationPosId(tmpMinPosIdUnused);
                m_members.push_back(player);
                break;
            }
        }
    }
}

void GameTeam::removeMember( GameCharacter* player )
{
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end(); tmpIterator++)
    {
        if (*tmpIterator == player)
        {
            m_members.erase(tmpIterator);
            player->setTeam(nullptr);
            break;
        }
    }
}

void GameTeam::update(float dm)
{
    dm  =   TimeTool::getSecondTime() - m_lastUpdateTime;
    m_lastUpdateTime    =   TimeTool::getSecondTime();
    //CCLOG("GameTeam::update");
    // 首先删除当前处于死亡状态的成员
    removeDeadCharacter();

    // 队伍级别的大脑思考一下
    m_teamBrain->process();

    // 调用该队的所有成员的update
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end();)
    {
        auto tmpMember  =   *tmpIterator;
        tmpIterator++;
        tmpMember->update(dm);
    }

    // 再删除处于死亡状态的队员
    removeDeadCharacter();

    // 更新队伍位置
    auto tmpTeamPos =   m_formation.getFormationAnchor();
    if (iscollectiveForwardState())
    {
        tmpTeamPos.setPoint(tmpTeamPos.x + dm * m_advanceRate, tmpTeamPos.y);
        m_formation.setFormationAnchor(tmpTeamPos);
    }
    else if (isFollowPlayerState())
    {
        // 否则队伍就始终跟随最前面的人
        auto tmpFormationX    =   0;
        for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end(); tmpIterator++)
        {
            auto tmpXPos    =   (*tmpIterator)->getMovingEntity().getPosition().x;
            if (m_formation.getFormationType() == Formation::FORMATION_TYPE_RIGHT && 
                tmpFormationX < tmpXPos)
            {
                tmpFormationX   =   tmpXPos;
            }
            if (m_formation.getFormationType() == Formation::FORMATION_TYPE_LEFT &&
                tmpFormationX > tmpXPos)
            {
                tmpFormationX   =   tmpXPos;
            }
        }
        tmpTeamPos.setPoint(tmpFormationX, tmpTeamPos.y);
        m_formation.setFormationAnchor(tmpTeamPos);
    }

    // 判断是否可以被删除
    if (m_members.size() == 0)
    {
        setCanRemove();
    }
}

GameTeam* GameTeam::create(GameTeamTypeEnum teamType)
{
    auto pRet   =   new GameTeam();
    if (pRet != nullptr)
    {
        pRet->autorelease();
        pRet->m_teamType    =   teamType;
        TeamMgr->registerTeam(pRet);
    }

    return pRet;
}

void GameTeam::removeDeadCharacter()
{
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end();)
    {
        if ((*tmpIterator)->isDead())
        {
            CC_SAFE_RELEASE_NULL(*tmpIterator);
            tmpIterator = m_members.erase(tmpIterator);
        }
        else
        {
            tmpIterator++;
        }
    }
}

void GameTeam::sendMessageToAllMember( Telegram& msg )
{
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end(); tmpIterator++)
    {
        sendMessageToOneMember(msg, *tmpIterator);
    }
}

void GameTeam::sendMessageToOneMember( Telegram& msg, GameCharacter* aCharacter )
{
    msg.receiverId  =   aCharacter->getId();
    Dispatch->dispatchMessage(msg);
}

void GameTeam::collectiveForwardStart()
{
    /**
    *  @_@ 虽然我很想直接调用队伍成员的接口，但是为了结构型，是不允许队伍直接操作队员
    *  必须走消息
    */ 
    auto tmpMsg =   Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_COLLECTIVE_FORWARD);
    sendMessageToAllMember(*tmpMsg);

    // 同时让锚点在每一帧中向前移动，@_@先这样写，通过速度来控制阵型移动
    if (this->getTeamFormation().getFormationType() == Formation::FORMATION_TYPE_RIGHT)
    {
        m_advanceRate   =   80;
    }
    else if (this->getTeamFormation().getFormationType() == Formation::FORMATION_TYPE_LEFT)
    {
        m_advanceRate   =   -80;
    }

    setCollectiveForwardState();
}

void GameTeam::collectiveForwardEnd()
{
    auto tmpMsg =   Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_CANCEL_COLLECTIVE_FORWARD);
    sendMessageToAllMember(*tmpMsg);

    m_advanceRate   =   0;

    setFollowPlayerState();
}

GameCharacter* GameTeam::getMemberIdFromFormation( int posId )
{
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end(); tmpIterator++)
    {
        if ((*tmpIterator)->getMovingEntity().getFormationPosId() == posId)
        {
            return *tmpIterator;
        }
    }

    return nullptr;
}
