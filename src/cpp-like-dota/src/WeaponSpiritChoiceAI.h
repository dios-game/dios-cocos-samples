#ifndef __WEAPON_SPIRIT_CHOICE_AI_H__
#define __WEAPON_SPIRIT_CHOICE_AI_H__

#include "WeaponChoiceAI.h"

/**
*	 Ñ©¾«ÁéµÄÎäÆ÷Ñ¡Ôñ
*/
class WeaponSpiritChoiceAI : public WeaponChoiceAI
{
public:
    WeaponSpiritChoiceAI(GameCharacter* owner): WeaponChoiceAI(owner)
    {

    }

    virtual void regularUpdate(float dm)
    {
        if (m_pOwner->getWeaponControlSystem()->getWeaponByType(SPIRIT_SNOWSTORM_SKILL_WEAPON)->isReadyForNextAttack())
        {
            changeWeapon(SPIRIT_SNOWSTORM_SKILL_WEAPON);
        }
        else
        {
            if (m_pOwner->getWeaponControlSystem()->getWeaponByType(SPIRIT_FREEZE_SKILL_WEAPON)->isReadyForNextAttack())
            {
                changeWeapon(SPIRIT_FREEZE_SKILL_WEAPON);
            }
            else
            {
                changeWeapon(NORMAL_LONG_RANGE_WEAPON);
            }
        }
    }
};

#endif