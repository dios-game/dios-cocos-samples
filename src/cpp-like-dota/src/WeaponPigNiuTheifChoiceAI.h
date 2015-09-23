#ifndef __WEAPON_PIG_NIU_THEIF_CHOICE_AI_H__
#define __WEAPON_PIG_NIU_THEIF_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "GameTeam.h"

/**
*	 猪、牛、盗贼选择武器的AI
*   @_@主要是考虑到这三个角色拥有的攻击方式都是一个进程攻击+一个远程攻击
*/
class WeaponPigNiuTheifChoiceAI : public WeaponChoiceAI
{
public:
    WeaponPigNiuTheifChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner)
    {

    }

    virtual ~WeaponPigNiuTheifChoiceAI()
    {

    }

protected:
    /**
    *	对于这种类型的角色，使用什么武器完全与所在位置有关，这里就根据位置编号
    *   来选择武器
    */
    virtual void choiceWeapon() override
    {
        int tmpPosId    =   m_pOwner->getMovingEntity().getFormationPosId();
        if ( tmpPosId>= 0 && tmpPosId <= 2 )
        {
            changeWeapon(NORMAL_CLOSE_RANGE_WEAPON);
        }
        else
        {
            auto tmpCharacter   =   m_pOwner->getTeam()->getMemberIdFromFormation(tmpPosId % 3);
            if (tmpCharacter != nullptr)
            {
                changeWeapon(NORMAL_LONG_RANGE_WEAPON);
            }
            else
            {
                changeWeapon(NORMAL_CLOSE_RANGE_WEAPON);
            }
        }
    }
};

#endif