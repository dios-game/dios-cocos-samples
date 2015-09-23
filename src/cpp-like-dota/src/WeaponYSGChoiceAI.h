#ifndef __WEAPON_YSG_CHOICE_AI_H__
#define __WEAPON_YSG_CHOICE_AI_H__

#include "WeaponYSGChoiceAI.h"

/**
*	ʯͷ�˵�����ѡ��
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
    *	ʯͷ��Ҳ��ֻ��
    *   ��1����ͨ�����빥��
    *   ��2��ʯͷ��
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