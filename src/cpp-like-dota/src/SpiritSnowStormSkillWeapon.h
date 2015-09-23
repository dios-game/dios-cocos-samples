#ifndef __SPIRIT_SNOW_STORM_SKILL_WEAPON_H__
#define __SPIRIT_SNOW_STORM_SKILL_WEAPON_H__

#include "Weapon.h"

/**
*	 雪精灵的暴风雪技能，就是在目标身上卷起一个龙卷风，
*/
class SpiritSnowStormSkillWeapon : public Weapon
{
public:
    SpiritSnowStormSkillWeapon(GameCharacter* owner);

    virtual void attack(GameCharacter* target);
    virtual bool isInAttackRange(GameCharacter* target);
    virtual bool isReadyForNextAttack();
    virtual bool isAttacking();
    virtual void update(float dm);

private:
    /**
    *	 角色动画播放到开始产生龙卷风的那一帧了
    */
    void onAttackEffect(string evt);

    /**
    *	目标是否存在 
    */
    bool isTargetAlive();

    float           m_attRadius;                    // 攻击半径
    const string    m_actionName;                   // 开火的时候的角色动画

    int             m_targetId;

    bool            m_lastTestIsReady;              // 最近一次调用isReadyForNextAttack结果
};

#endif