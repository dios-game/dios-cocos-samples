#ifndef __WEAPON_AER_CHOICE_AI_H__
#define __WEAPON_AER_CHOICE_AI_H__

#include "WeaponChoiceAI.h"

/**
*	 ��ʿѡ��������AI
*/
class WeaponAerChoiceAI : public WeaponChoiceAI
{
public:
    WeaponAerChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner)
    {

    }

    virtual ~WeaponAerChoiceAI()
    {

    }

protected:
    /**
    *	 ��ʿֻ�����ֹ�����ʽ����ͨ�Ľ����빥���ͱ�Ȧ���������ǽ����빥������ǰ���߼�
    *    �����и��ʵ�ʹ�ñ�Ȧ����
    */
    virtual void choiceWeapon() override
    {
        changeWeapon(choiceCloseOrCryosphere());
    }

private:
    WeaponTypeEnum choiceCloseOrCryosphere()
    {
        if (m_pOwner->getAttribute().getEnergy() == 600)
        {
            return AER_CRYOSPHERE_SKILL_WEAPON;
        }
        else
        {
            return NORMAL_CLOSE_RANGE_WEAPON;
        }
    }
};

#endif