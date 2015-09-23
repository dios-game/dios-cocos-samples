#include "SpiritFreezeSkillWeapon.h"
#include "EntityManager.h"
#include "TimeTool.h"
#include "RefreshUIMsg.h"
#include "UIViewManager.h"

SpiritFreezeSkillWeapon::SpiritFreezeSkillWeapon( GameCharacter* owner ):Weapon(owner, SPIRIT_FREEZE_SKILL_WEAPON)
    , m_actionName("atk3"), m_attRadius(600)
{
    m_minAttackInterval     =   6;
    m_lastTestIsReady       =   false;
    m_lastAttackTime        =   0;
    m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
}

SpiritFreezeSkillWeapon::~SpiritFreezeSkillWeapon()
{

}

void SpiritFreezeSkillWeapon::attack( GameCharacter* target )
{
    // 攻击时也需要播放动画
    m_pOwner->getShape()->playAction(m_actionName, false,
        std::bind(&SpiritFreezeSkillWeapon::onAttackEffect, this, std::placeholders::_1));

    // 记录一下当前的时间
    m_lastAttackTime        =   TimeTool::getSecondTime();
    m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
    m_targetId              =   target->getId();
}

bool SpiritFreezeSkillWeapon::isInAttackRange( GameCharacter* target )
{
    auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
    auto tmpTargetPos   =   target->getMovingEntity().getPosition();
    return (tmpOwnerPos - tmpTargetPos).getLengthSq() <= m_attRadius * m_attRadius;
}

bool SpiritFreezeSkillWeapon::isReadyForNextAttack()
{
    return m_nextAttackReadyTime < TimeTool::getSecondTime();
}

bool SpiritFreezeSkillWeapon::isAttacking()
{
    return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
}

void SpiritFreezeSkillWeapon::onAttackEffect( string evt )
{
    if (!isTargetAlive())
    {
        return;
    }

    /**
    *	 @_@ 发起攻击，其实就是让敌人进入冻结状态，显示这一块暂时也放在
    *   状态里面，以后可能还是使用消息的方式，但是目前图简单，先直接修改
    *   目标的状态
    */
    auto tmpTarget  =   
        dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    tmpTarget->getFSM()->changeState(GameCharacterFrozenState::create());

    // @_@ 应该还会造成伤害，这里暂时留着不写
}

bool SpiritFreezeSkillWeapon::isTargetAlive()
{
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpCharacter != nullptr && tmpCharacter->isAlive();
}

void SpiritFreezeSkillWeapon::update( float dm )
{
    if (m_pOwner != dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity()))
    {
        return;
    }

    auto tmpIsReady =   isReadyForNextAttack();
    if (!m_lastTestIsReady)
    {
        // 如果最近一次调用isReadyForNextAttack还是没有成功的话，就必须在下一帧中刷新冷却进度
        int tmpRatio   =   (TimeTool::getSecondTime() - m_lastAttackTime) / m_minAttackInterval * 100;
        tmpRatio       =   tmpRatio > 100 ? 100 : tmpRatio;
        RefreshUIMsg tmpMsg(REFRESH_UI_SKILL2_COOLING, (void *)tmpRatio);
        UIViewMgr->refreshView(tmpMsg);
    }
    m_lastTestIsReady   =   tmpIsReady;
}
