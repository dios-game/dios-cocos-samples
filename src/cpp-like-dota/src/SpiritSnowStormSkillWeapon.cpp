#include "SpiritSnowStormSkillWeapon.h"
#include "GameCharacter.h"
#include "TimeTool.h"
#include "EntityManager.h"
#include "Tornado.h"
#include "RefreshUIMsg.h"
#include "UIViewManager.h"

SpiritSnowStormSkillWeapon::SpiritSnowStormSkillWeapon( GameCharacter* owner ) 
    :Weapon(owner, SPIRIT_SNOWSTORM_SKILL_WEAPON), m_actionName("atk2")
{
    m_attRadius         =   650;
    m_lastTestIsReady   =   false;
}

void SpiritSnowStormSkillWeapon::attack( GameCharacter* target )
{
    // 先播放动画
    m_pOwner->getShape()->playAction(m_actionName, false, 
        std::bind(&SpiritSnowStormSkillWeapon::onAttackEffect, this, std::placeholders::_1));

    m_targetId              =   target->getId();

    // 同时把能量归零
    m_pOwner->getAttribute().setEnergy(0);
}

bool SpiritSnowStormSkillWeapon::isInAttackRange( GameCharacter* target )
{
    auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
    auto tmpTargetPos   =   target->getMovingEntity().getPosition();
    return (tmpOwnerPos - tmpTargetPos).getLengthSq() <= m_attRadius * m_attRadius;
}

bool SpiritSnowStormSkillWeapon::isReadyForNextAttack()
{
    // 暴风雪准备好的条件是能量达到600
    return m_pOwner->getAttribute().getEnergy() >= 600;
}

bool SpiritSnowStormSkillWeapon::isAttacking()
{
    return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
}

void SpiritSnowStormSkillWeapon::onAttackEffect( string evt )
{
    if (!isTargetAlive())
    {
        return;
    }

    // 在当前目标所在位置产生一个龙卷风，龙卷风产生后就会在固定位置对周围的角色
    // 产生影响
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    auto tmpTornado     =   Tornado::create(m_pOwner->getId());
    tmpTornado->setPosition(tmpCharacter->getShape()->getPosition());
    GamepMapSingleton->addChildToPlayerLayer(tmpTornado);
}

bool SpiritSnowStormSkillWeapon::isTargetAlive()
{
    auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpCharacter != nullptr && tmpCharacter->isAlive();
}

void SpiritSnowStormSkillWeapon::update( float dm )
{
    // @_@ 如果之前是不能使用，而这次更新后可以使用，就会向发一个UI事件
    // @_@ 这里忽略一个问题，只有主角采用发出消息
    if (m_pOwner != dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity()))
    {
        return;
    }

    auto tmpIsReady =   isReadyForNextAttack();
    if (!m_lastTestIsReady && tmpIsReady)
    {
        // @_@ 发出UI事件
        RefreshUIMsg    tmpMsg(REFRESH_UI_SKILL1_USABLE);
        UIViewMgr->refreshView(tmpMsg);
    }
    else if (m_lastTestIsReady && !tmpIsReady)
    {
        // 之前可以，现在又不可以了，也发出一个消息
        RefreshUIMsg    tmpMsg(REFRESH_UI_SKILL1_UNUSABLE);
        UIViewMgr->refreshView(tmpMsg);
    }
    m_lastTestIsReady   =   tmpIsReady;
}
