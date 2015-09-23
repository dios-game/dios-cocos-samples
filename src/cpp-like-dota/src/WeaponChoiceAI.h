#ifndef __WEAPON_CHOICE_AI_H__
#define __WEAPON_CHOICE_AI_H__

#include <assert.h>
#include "WeaponControlSystem.h"
#include "GameCharacter.h"

class Weapon;

/**
*	主要是考虑到何时使用什么武器对于不同的角色是有不同的逻辑的，所以将
*   这一块逻辑独立成一个对象，针对每一种角色实现一个子类来描述整个选择
*   武器的逻辑
*/
class WeaponChoiceAI
{
public:
    WeaponChoiceAI(GameCharacter* owner)
    {
        m_pOwner            =   owner;
    }

    virtual ~WeaponChoiceAI()
    {

    }

    /**
    *	每一次调用，都会根据当前情况选择一个合适的武器，该函数只会在少数的地方被调用
    *   （1）在设定攻击目标的时候被调用
    *   （2）在每次发动攻击之后会被调用
    *   这是用在每次只在
    */
    void update()
    {
        // 真正考虑一下更换武器的逻辑
        choiceWeapon();
    }

    /**
    *	定期调用的 
    */
    virtual void regularUpdate(float dm)
    {

    }

    /**
    *	因为是用什么武器与之前的攻击有关，所以在每次攻击的时候需要回调该函数，有些
    *   角色可以在子类中去覆盖该方法
    */
    virtual void attack()
    {
        update();
    }

    /**
    *	当更改了当前攻击目标的时候被调用，这个可能会影响角色武器选择的逻辑
    */
    virtual void changeTarget()
    {

    }

    /**
    *	对于普通的AI，默认情况下所有的命令都是无效的
    */
    virtual bool userOrder(WeaponTypeEnum aType)
    {
        return false;
    }

protected:
    /**
    *	在此处封装真正的武器选择逻辑 
    */
    virtual void choiceWeapon() {}
    
    /**
    *	提供的快捷方法来选择武器 
    */
    void changeWeapon(WeaponTypeEnum aType)
    {
        m_pOwner->getWeaponControlSystem()->changeWeapon(aType);
    }

    GameCharacter*    m_pOwner;                // 对应的武器控制系统
};

#endif