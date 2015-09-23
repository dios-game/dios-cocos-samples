#ifndef __YSG_METEORIC_STREAM_SKILL_WEAPON_H__
#define __YSG_METEORIC_STREAM_SKILL_WEAPON_H__

#include "Weapon.h"
#include "MeteoricStream.h"

/**
*	 石头人的陨石攻击
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
    *	施展动画播放到要开始，此时开始下陨石
    */
    void onAttackEffect(string evt)
    {
        // 在m_targetPos处下陨石，@_@这里就直接在地图上的这个位置放置一个陨石算了
        auto tmpMeteoricStream  =   MeteoricStream::create(m_pOwner->getId());
        tmpMeteoricStream->setPosition(m_targetPos);
        GamepMapSingleton->addChildToPlayerLayer(tmpMeteoricStream);

        // 归零能量值
        m_pOwner->getAttribute().setEnergy(0);

        // 需要根据释放者和目标的相对位置来修改陨石下落的方向
        if (m_targetPos.x < m_pOwner->getMovingEntity().getPosition().x)
        {
            tmpMeteoricStream->setScaleX(-1);
        }
    }

    /**
    *	目前限制两次陨石的条件也是时间问题 
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // 最近一次攻击时间
    double          m_nextAttackReadyTime;          // 下一次攻击准备完毕时间

    const string    m_actionName;                   // 对应的角色的动画
    const float     m_attRadius;                    // 发起攻击的半径

    Vec2            m_targetPos;                    // 目标坐标（在此处下陨石）
};

#endif