#ifndef __WEAPON_ZEUS_CHOICE_AI_H__
#define __WEAPON_ZEUS_CHOICE_AI_H__

#include "WeaponChoiceAI.h"
#include "GameTeam.h"

/**
*	 宙斯的武器选择
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
    *	对于宙斯，当更换了攻击目标后，就把计数归0 
    */
    virtual void changeTarget()
    {
        m_attackCount   =   0;
    }

    virtual void attack() override
    {
        // 要统计一下近距离攻击的次数
        if (m_pOwner->getWeaponControlSystem()->getCurrentWeaponType() == NORMAL_LONG_RANGE_WEAPON)
        {
            m_attackCount =   0;
        }
        else
        {
            m_attackCount++;
        }

        // 攻击完成后，就需要思考是否需要换一种攻击方式
        WeaponChoiceAI::attack();
    }

protected:
    /**
    *	 宙斯拥有3种攻击方式
    *   （1）普通近距离攻击
    *   （2）丢斧头（普通远距离攻击）
    *   （3）重击
    *    如果宙斯在远距离的攻击位置处，那么就会使用飞锤，如果在近距离攻击位置就会按照
    *    4次普通加1次重击的顺序
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
    *	如果是普通攻击，就需要按照4次普通加1次重击的顺序
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

    int m_attackCount;                    // 统计近距离攻击的次数
};

#endif