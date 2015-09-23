#ifndef __ZEUS_THUMP_SKILL_WEAPON_H__
#define __ZEUS_THUMP_SKILL_WEAPON_H__

#include "NormalCloseRangeWeapon.h"

/**
*	 宙斯的重击技能，@_@ 因为表现很像近距离攻击，这里偷个懒，对于计算先不做任
*    何改动
*/
class ZeusThumpSkillWeapon : public NormalCloseRangeWeapon
{
public:
    ZeusThumpSkillWeapon(GameCharacter* owner):NormalCloseRangeWeapon(owner, 3, "atk2")
    {
        // 需要手动设置一下
        m_weaponType    =  ZEUS_THUMP_SKILL_WEAPON; 
    }

protected:
    /**
    *	 目前重击的作用效果和普攻一样，只是攻击力变成原来的1.5倍
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