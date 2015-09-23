#ifndef __WEAPON_SPIRIT_USER_CHOICE_AI_H__
#define __WEAPON_SPIRIT_USER_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "TimeTool.h"
#include "RefreshUIMsg.h"
#include "UIViewManager.h"

/**
*	 由用户控制的精灵武器选择AI，用户的关于技能选择的请求也是直接与它交互
*/
class WeaponSpiritUserChoiceAI : public WeaponChoiceAI
{
public:
    WeaponSpiritUserChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner)
    {
        // 开始的时候，下一个攻击方式就是普通远距离攻击
    }

    virtual void attack() override
    {
        if (m_pOwner->getWeaponControlSystem()->getCurrentWeaponType() != NORMAL_LONG_RANGE_WEAPON)
        {
            m_pOwner->getWeaponControlSystem()->changeWeapon(NORMAL_LONG_RANGE_WEAPON);
        }
    }

    /**
    *	玩家如果想人工干预角色对技能的选择就要通过这个接口，但是就算人工干预了，很多
    *   时候还是会和游戏AI牵扯到关系
    */
    virtual bool userOrder(WeaponTypeEnum aType) override
    {
        if (!testUserOrder(aType))
        {
            return false;
        }

        // 设置玩家选择的武器作为下一次选择的武器
        m_pOwner->getWeaponControlSystem()->changeWeapon(aType, true);
        return true;
    }

protected:

    /**
    *   传入的直接是武器类型的枚举值
    */
    bool testUserOrder(WeaponTypeEnum aType)
    {
        return m_pOwner->getWeaponControlSystem()->getWeaponByType(aType)->isReadyForNextAttack();
    }
};

#endif