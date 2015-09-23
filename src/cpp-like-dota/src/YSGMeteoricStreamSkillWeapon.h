#ifndef __YSG_METEORIC_STREAM_SKILL_WEAPON_H__
#define __YSG_METEORIC_STREAM_SKILL_WEAPON_H__

#include "Weapon.h"
#include "MeteoricStream.h"

/**
*	 ʯͷ�˵���ʯ����
*/
class YSGMeteoricStreamSkillWeapon : public Weapon
{
public:
    YSGMeteoricStreamSkillWeapon(GameCharacter* owner):Weapon(owner, YSG_METEORIC_STREAM_SKILL_WEAPON)
        , m_actionName("atk2"), m_attRadius(650)
    {
        m_minAttackInterval     =   6;
        m_nextAttackReadyTime   =   0;
    }

    ~YSGMeteoricStreamSkillWeapon()
    {

    }

    virtual void attack(GameCharacter* target) override
    {
        m_pOwner->getShape()->playAction(m_actionName, false,
            std::bind(&YSGMeteoricStreamSkillWeapon::onAttackEffect, this, std::placeholders::_1));

        m_lastAttackTime        =   TimeTool::getSecondTime();
        m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
        m_targetPos             =   target->getShape()->getPosition();
    }

    virtual bool isInAttackRange(GameCharacter* target) override
    {
        auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
        auto tmpTargetPos   =   target->getMovingEntity().getPosition();
        return (tmpOwnerPos - tmpTargetPos).getLengthSq() <= m_attRadius * m_attRadius;
    }

    virtual bool isReadyForNextAttack() override
    {
        return m_nextAttackReadyTime < TimeTool::getSecondTime();
    }

    virtual bool isAttacking() override
    {
        return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
    }

private:
    /**
    *	ʩչ�������ŵ�Ҫ��ʼ����ʱ��ʼ����ʯ
    */
    void onAttackEffect(string evt)
    {
        // ��m_targetPos������ʯ��@_@�����ֱ���ڵ�ͼ�ϵ����λ�÷���һ����ʯ����
        auto tmpMeteoricStream  =   MeteoricStream::create(m_pOwner->getId());
        tmpMeteoricStream->setPosition(m_targetPos);
        GamepMapSingleton->addChildToPlayerLayer(tmpMeteoricStream);

        // ��������ֵ
        m_pOwner->getAttribute().setEnergy(0);

        // ��Ҫ�����ͷ��ߺ�Ŀ������λ�����޸���ʯ����ķ���
        if (m_targetPos.x < m_pOwner->getMovingEntity().getPosition().x)
        {
            tmpMeteoricStream->setScaleX(-1);
        }
    }

    /**
    *	Ŀǰ����������ʯ������Ҳ��ʱ������ 
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // ���һ�ι���ʱ��
    double          m_nextAttackReadyTime;          // ��һ�ι���׼�����ʱ��

    const string    m_actionName;                   // ��Ӧ�Ľ�ɫ�Ķ���
    const float     m_attRadius;                    // ���𹥻��İ뾶

    Vec2            m_targetPos;                    // Ŀ�����꣨�ڴ˴�����ʯ��
};

#endif