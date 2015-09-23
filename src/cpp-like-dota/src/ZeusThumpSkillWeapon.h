#ifndef __ZEUS_THUMP_SKILL_WEAPON_H__
#define __ZEUS_THUMP_SKILL_WEAPON_H__

#include "NormalCloseRangeWeapon.h"

/**
*	 ��˹���ػ����ܣ�@_@ ��Ϊ���ֺ�������빥��������͵���������ڼ����Ȳ�����
*    �θĶ�
*/
class ZeusThumpSkillWeapon : public NormalCloseRangeWeapon
{
public:
    ZeusThumpSkillWeapon(GameCharacter* owner):NormalCloseRangeWeapon(owner, 3, "atk2")
    {
        // ��Ҫ�ֶ�����һ��
        m_weaponType    =  ZEUS_THUMP_SKILL_WEAPON; 
    }

protected:
    /**
    *	 Ŀǰ�ػ�������Ч�����չ�һ����ֻ�ǹ��������ԭ����1.5��
    */
    virtual void onAttackEffect(string evt) override
    {
        auto tmpAttribute   =   m_pOwner->getAttribute();
        tmpAttribute.setAttack(tmpAttribute.getAttack());
        auto tmpMsg = TelegramNormalAttack::create(m_pOwner->getId(), m_targetId, tmpAttribute);
        Dispatch->dispatchMessage(*tmpMsg);
    }
};

#endif