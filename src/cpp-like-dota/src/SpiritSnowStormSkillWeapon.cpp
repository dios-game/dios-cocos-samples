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
    // �Ȳ��Ŷ���
    m_pOwner->getShape()->playAction(m_actionName, false, 
        std::bind(&SpiritSnowStormSkillWeapon::onAttackEffect, this, std::placeholders::_1));

    m_targetId              =   target->getId();

    // ͬʱ����������
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
    // ����ѩ׼���õ������������ﵽ600
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

    // �ڵ�ǰĿ������λ�ò���һ������磬����������ͻ��ڹ̶�λ�ö���Χ�Ľ�ɫ
    // ����Ӱ��
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
    // @_@ ���֮ǰ�ǲ���ʹ�ã�����θ��º����ʹ�ã��ͻ���һ��UI�¼�
    // @_@ �������һ�����⣬ֻ�����ǲ��÷�����Ϣ
    if (m_pOwner != dynamic_cast<GameCharacter*>(EntityMgr->getmainEntity()))
    {
        return;
    }

    auto tmpIsReady =   isReadyForNextAttack();
    if (!m_lastTestIsReady && tmpIsReady)
    {
        // @_@ ����UI�¼�
        RefreshUIMsg    tmpMsg(REFRESH_UI_SKILL1_USABLE);
        UIViewMgr->refreshView(tmpMsg);
    }
    else if (m_lastTestIsReady && !tmpIsReady)
    {
        // ֮ǰ���ԣ������ֲ������ˣ�Ҳ����һ����Ϣ
        RefreshUIMsg    tmpMsg(REFRESH_UI_SKILL1_UNUSABLE);
        UIViewMgr->refreshView(tmpMsg);
    }
    m_lastTestIsReady   =   tmpIsReady;
}
