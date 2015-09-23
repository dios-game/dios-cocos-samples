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
    // ���������ͬʱҲ�������еĳ�Ա����Ϊ��Ա���ڶ���
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

    // �����ǰλ���Ѿ������ˣ��ͻ����һ����0��ʼ����С�Ļ�û��ʹ�õ�λ��
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
    // ����ɾ����ǰ��������״̬�ĳ�Ա
    removeDeadCharacter();

    // ���鼶��Ĵ���˼��һ��
    m_teamBrain->process();

    // ���øöӵ����г�Ա��update
    for (auto tmpIterator = m_members.begin(); tmpIterator != m_members.end();)
    {
        auto tmpMember  =   *tmpIterator;
        tmpIterator++;
        tmpMember->update(dm);
    }

    // ��ɾ����������״̬�Ķ�Ա
    removeDeadCharacter();

    // ���¶���λ��
    auto tmpTeamPos =   m_formation.getFormationAnchor();
    if (iscollectiveForwardState())
    {
        tmpTeamPos.setPoint(tmpTeamPos.x + dm * m_advanceRate, tmpTeamPos.y);
        m_formation.setFormationAnchor(tmpTeamPos);
    }
    else if (isFollowPlayerState())
    {
        // ��������ʼ�ո�����ǰ�����
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

    // �ж��Ƿ���Ա�ɾ��
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
    *  @_@ ��Ȼ�Һ���ֱ�ӵ��ö����Ա�Ľӿڣ�����Ϊ�˽ṹ�ͣ��ǲ��������ֱ�Ӳ�����Ա
    *  ��������Ϣ
    */ 
    auto tmpMsg =   Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_COLLECTIVE_FORWARD);
    sendMessageToAllMember(*tmpMsg);

    // ͬʱ��ê����ÿһ֡����ǰ�ƶ���@_@������д��ͨ���ٶ������������ƶ�
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
