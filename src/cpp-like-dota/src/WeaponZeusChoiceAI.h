#ifndef __WEAPON_ZEUS_CHOICE_AI_H__
#define __WEAPON_ZEUS_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "GameTeam.h"

/**
*	 ��˹������ѡ��
*/
class WeaponZeusChoiceAI : public WeaponChoiceAI
{
public:
    WeaponZeusChoiceAI(GameCharacter* owner):WeaponChoiceAI(owner)
    {
        m_attackCount =   0;
    }

    virtual ~WeaponZeusChoiceAI()
    {

    }

    /**
    *	������˹���������˹���Ŀ��󣬾ͰѼ�����0 
    */
    virtual void changeTarget()
    {
        m_attackCount   =   0;
    }

    virtual void attack() override
    {
        // Ҫͳ��һ�½����빥���Ĵ���
        if (m_pOwner->getWeaponControlSystem()->getCurrentWeaponType() == NORMAL_LONG_RANGE_WEAPON)
        {
            m_attackCount =   0;
        }
        else
        {
            m_attackCount++;
        }

        // ������ɺ󣬾���Ҫ˼���Ƿ���Ҫ��һ�ֹ�����ʽ
        WeaponChoiceAI::attack();
    }

protected:
    /**
    *	 ��˹ӵ��3�ֹ�����ʽ
    *   ��1����ͨ�����빥��
    *   ��2������ͷ����ͨԶ���빥����
    *   ��3���ػ�
    *    �����˹��Զ����Ĺ���λ�ô�����ô�ͻ�ʹ�÷ɴ�������ڽ����빥��λ�þͻᰴ��
    *    4����ͨ��1���ػ���˳��
    */
    virtual void choiceWeapon() override
    {
        int tmpPosId            =   m_pOwner->getMovingEntity().getFormationPosId();
        WeaponTypeEnum tmpType  =   NORMAL_CLOSE_RANGE_WEAPON;
        if ( tmpPosId>= 0 && tmpPosId <= 2 )
        {
            tmpType =   choiceCloseAttOrThump();
        }
        else
        {
            auto tmpCharacter   =   m_pOwner->getTeam()->getMemberIdFromFormation(tmpPosId % 3);
            if (tmpCharacter != nullptr)
            {
                tmpType             =   NORMAL_LONG_RANGE_WEAPON;
            }
            else
            {
                tmpType =   choiceCloseAttOrThump();
            }
        }

        changeWeapon(tmpType);
    }

private:
    /**
    *	�������ͨ����������Ҫ����4����ͨ��1���ػ���˳��
    */
    WeaponTypeEnum choiceCloseAttOrThump()
    {
        if (m_attackCount <= 4)
        {
            return NORMAL_CLOSE_RANGE_WEAPON;
        }
        else
        {
            m_attackCount   =   0;
            return ZEUS_THUMP_SKILL_WEAPON;
        }
    }

    int m_attackCount;                    // ͳ�ƽ����빥���Ĵ���
};

#endif