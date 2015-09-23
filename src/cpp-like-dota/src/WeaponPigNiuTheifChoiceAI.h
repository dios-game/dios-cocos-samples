#ifndef __WEAPON_PIG_NIU_THEIF_CHOICE_AI_H__
#define __WEAPON_PIG_NIU_THEIF_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "GameTeam.h"

/**
*	 ��ţ������ѡ��������AI
*   @_@��Ҫ�ǿ��ǵ���������ɫӵ�еĹ�����ʽ����һ�����̹���+һ��Զ�̹���
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
    *	�����������͵Ľ�ɫ��ʹ��ʲô������ȫ������λ���йأ�����͸���λ�ñ��
    *   ��ѡ������
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