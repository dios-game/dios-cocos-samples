#ifndef __SPIRIT_FREEZE_SKILL_WEAPON_H__
#define __SPIRIT_FREEZE_SKILL_WEAPON_H__

#include "cocos2d.h"
#include "Weapon.h"
#include "GameCharacterState.h"

using namespace std;

/**
*	雪精灵的冰冻魔法，用该技能攻击对手可以在对手身上产生冰冻效果，让对手
*   进入冻结状态若干时间
*/
class SpiritFreezeSkillWeapon : public Weapon
{
public:
    SpiritFreezeSkillWeapon(GameCharacter* owner);
    virtual ~SpiritFreezeSkillWeapon();

    virtual void attack(GameCharacter* target) override;

    virtual bool isInAttackRange(GameCharacter* target) override;

    virtual bool isReadyForNextAttack() override;

    virtual bool isAttacking() override;

    virtual void update(float dm) override;

private:
    /**
    *	施展动画播放到要开始 
    */
    void onAttackEffect(string evt);

    /**
    *	目标是否存在 
    */
    bool isTargetAlive();

    /**
    *	目前限制两次冰冻的条件也是时间问题 
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // 最近一次攻击时间
    double          m_nextAttackReadyTime;          // 下一次攻击准备完毕时间

    int             m_targetId;                     // 攻击目标id

    const string    m_actionName;                   // 动作名称
    const float     m_attRadius;                    // 攻击半径

private:
    bool            m_lastTestIsReady;              // 最近一次调用isReadyForNextAttack
};

#endif