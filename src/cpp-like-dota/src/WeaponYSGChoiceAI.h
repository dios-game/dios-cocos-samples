#ifndef __WEAPON_YSG_CHOICE_AI_H__
#define __WEAPON_YSG_CHOICE_AI_H__

#include "WeaponYSGChoiceAI.h"

/**
*	石头人的武器选择
*/
class WeaponYSGChoiceAI : public WeaponChoiceAI
{
public:
    WeaponYSGChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner)
    {

    }

    virtual ~WeaponYSGChoiceAI()
    {

    }

protected:
    /**
    *	石头人也就只有
    *   （1）普通近距离攻击
    *   （2）石头雨
    */
    virtual void choiceWeapon() override
    {
        if (m_pOwner->getAttribute().getEnergy() == 600)
        {
            changeWeapon(YSG_METEORIC_STREAM_SKILL_WEAPON);
        }
        else
        {
            changeWeapon(NORMAL_CLOSE_RANGE_WEAPON);
        }
    }
};

#endif