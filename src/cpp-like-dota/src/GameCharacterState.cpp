#include "GameCharacterState.h"
#include "TeamManager.h"
#include "GoalCharacterThink.h"
#include "EntityManager.h"

void GameCharacterFrozenState::onEnter( GameCharacter *owner )
{
    // 限制角色最大速度为0来让角色无法移动
    m_maxSpeed      =   owner->getMovingEntity().getMaxSpeed();
    owner->getMovingEntity().setMaxSpeed(0);

    // 停止当前动画
    owner->getShape()->freezeAnimation();

    // @_@ 在角色身上放置一个冰块，暂时先放在这里吧
    ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/xuejingling_VFX.ExportJson");
    m_iceCake   =   Armature::create("xuejingling_VFX");
    m_iceCake->setPosition(owner->getShape()->getCenterPosLocation());
    owner->getShape()->addChild(m_iceCake, 10);
    m_iceCake->getAnimation()->play("atk3");

    // 还需要根据角色形象的大小来对冰块进行缩放
    float tmpShapeW     =   owner->getShape()->getContentSize().width;
    float tmpShapeH     =   owner->getShape()->getContentSize().height;
    float tmpShapeWToH  =   tmpShapeW / tmpShapeH;
    const float tmpIceH     =   140;
    const float tmpIceW     =   50;
    const float tmpIceWToH  = tmpIceW / tmpIceH;
    if (tmpShapeWToH >= tmpIceWToH)
    {
        // 如果角色宽一些
        m_iceCake->setScale(tmpShapeW * 0.6 / tmpIceW);
    }
    else
    {
        m_iceCake->setScale(tmpShapeH * 0.6 / tmpIceH);
    }
}

void GameCharacterFrozenState::update( GameCharacter *owner, float dm )
{
    m_frozenTime    +=  dm;
    if (m_frozenTime >= m_maxFrozenTime)
    {
        owner->getFSM()->changeState(GameCharacterFreeState::create());
    }
}

void GameCharacterFrozenState::onExit( GameCharacter *owner )
{
    owner->getMovingEntity().setMaxSpeed(m_maxSpeed);

    owner->getShape()->unfreezeAnimation(true);

    m_iceCake->removeFromParent();
}

GameCharacterFrozenState::GameCharacterFrozenState()
{
    // @_@ 先这样写吧，冻结2秒钟
    m_maxFrozenTime =   2;
    m_frozenTime    =   0;
}


void GameCharacterHitedState::onEnter( GameCharacter* owner )
{
    // 播放受击动画
    owner->getShape()->playAction(m_actionName, false);

    // 同时该角色呆滞
    owner->dullOn();
}

void GameCharacterHitedState::update( GameCharacter *owner, float dm )
{
    // 动画播放完毕后就退出
    if (owner->getShape()->getCurrentAnimationName() != m_actionName)
    {
        owner->getFSM()->changeState(GameCharacterFreeState::create());
    }
}

void GameCharacterHitedState::onExit( GameCharacter *owner )
{
    owner->dullOff();
}

void GameCharacterTimidState::update( GameCharacter *owner, float dm )
{
    // 每次更新都会判断血量是否满足逃跑条件
    auto tmpAttribute   =   owner->getAttribute();
    if (tmpAttribute.getHp() / tmpAttribute.getFullHp() <= 0.7)
    {
        auto tmpCurrentTeam =   owner->getTeam();
        auto tmpNextTeam    =   TeamMgr->getNextTeam(tmpCurrentTeam->getTeamId());
        if (tmpNextTeam != nullptr)
        {
            // 从队伍除名并清除该角色的当前目标
            tmpCurrentTeam->removeMember(owner);
            owner->getBrain()->removeAllSubgoals();

            // 加入下一个队伍，同时开启恢复阵型的驱动力
            tmpNextTeam->addMember(owner);

            // 切换状态为逃跑中
            owner->getFSM()->changeState(GameCharacterEscapeToNextTeam::create());
            owner->getFSM()->setGlobalState(nullptr);
        }
    }
}

void GameCharacterEscapeToNextTeam::onEnter( GameCharacter* owner )
{
    // 同时把角色的最大速度和最大
    m_originMaxForce    =   owner->getMovingEntity().getMaxForce();
    m_originMaxSpeed    =   owner->getMovingEntity().getMaxSpeed();
    owner->getMovingEntity().setMaxForce(2 * m_originMaxForce);
    owner->getMovingEntity().setMaxSpeed(2 * m_originMaxSpeed);

    owner->getSteeringBehaviros()->keepFormationOn();

    // @_@ 下面是临时写的
    owner->getSteeringBehaviros()->pursuitOff();
    owner->getSteeringBehaviros()->setTraction(Vec2::ZERO);
}

void GameCharacterEscapeToNextTeam::onExit( GameCharacter *owner )
{
    owner->getSteeringBehaviros()->keepFormationOff();
    owner->getMovingEntity().setMaxForce(m_originMaxForce);
    owner->getMovingEntity().setMaxSpeed(m_originMaxSpeed);
}

bool GameCharacterEscapeToNextTeam::onMessage( GameCharacter *owner, Telegram& msg )
{
    // 在逃跑中收到进攻消息的时候，切换到攻击
    switch (msg.type)
    {
    case TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET:
        {
            owner->getFSM()->changeState(GameCharacterFreeState::create());
            return true;
        }

    default:
        break;
    }

    return false;
}
