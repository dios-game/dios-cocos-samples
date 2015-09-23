#ifndef __WEAPON_SPIRIT_USER_CHOICE_AI_H__
#define __WEAPON_SPIRIT_USER_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "TimeTool.h"
#include "RefreshUIMsg.h"
#include "UIViewManager.h"

/**
*	 ���û����Ƶľ�������ѡ��AI���û��Ĺ��ڼ���ѡ�������Ҳ��ֱ����������
*/
class WeaponSpiritUserChoiceAI : public WeaponChoiceAI
{
public:
    WeaponSpiritUserChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner)
    {
        // ��ʼ��ʱ����һ��������ʽ������ͨԶ���빥��
    }

    virtual void attack() override
    {
        if (m_pOwner->getWeaponControlSystem()->getCurrentWeaponType() != NORMAL_LONG_RANGE_WEAPON)
        {
            m_pOwner->getWeaponControlSystem()->changeWeapon(NORMAL_LONG_RANGE_WEAPON);
        }
    }

    /**
    *	���������˹���Ԥ��ɫ�Լ��ܵ�ѡ���Ҫͨ������ӿڣ����Ǿ����˹���Ԥ�ˣ��ܶ�
    *   ʱ���ǻ����ϷAIǣ������ϵ
    */
    virtual bool userOrder(WeaponTypeEnum aType) override
    {
        if (!testUserOrder(aType))
        {
            return false;
        }

        // �������ѡ���������Ϊ��һ��ѡ�������
        m_pOwner->getWeaponControlSystem()->changeWeapon(aType, true);
        return true;
    }

protected:

    /**
    *   �����ֱ�����������͵�ö��ֵ
    */
    bool testUserOrder(WeaponTypeEnum aType)
    {
        return m_pOwner->getWeaponControlSystem()->getWeaponByType(aType)->isReadyForNextAttack();
    }
};

#endif