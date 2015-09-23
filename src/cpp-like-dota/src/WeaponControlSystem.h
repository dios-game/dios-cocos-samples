#ifndef __WEAPON_CONTROL_SYSTEM_H__
#define __WEAPON_CONTROL_SYSTEM_H__

#include <map>
#include "Weapon.h"

using namespace std;

class GameCharacter;
class WeaponChoiceAI;

/**
* 武器控制系统，这里负责维护角色身上的所有攻击方式，包括普通攻击、技能攻击等，包括
* 使用哪种方式来攻击的逻辑也在这里，关于攻击方式应该是要根据某些环境来得出使用某种
* 武器来攻击
*/
class WeaponControlSystem
{
public:
    WeaponControlSystem(GameCharacter* owner);
    ~WeaponControlSystem();

    /**
    * 给该武器系统添加武器类型 
    */
    void addWeapon(Weapon* aWeapon);

    /**
    *	调用一下角色的武器控制系统的思考部分，根据当前情况选择正确的武器
    */
    void update();

    /**
    *	定期被调用的函数，有些逻辑还是要依赖一些间隔的
    */
    void regularUpdate(float dm);

    /**
    *	设置攻击目标的时候调用 
    */
    void setAttackTarget(int targetId);

    /**
    * 使用当前武器并且攻击某个目标 
    */
    void takeWeaponAndAttack(GameCharacter* target);

    /**
    * 返回使用当前武器的情况下，target是否在攻击范围内
    */
    bool isInAttackRange(GameCharacter* target);

    /**
    * @_@ 主要是因为在武器系统攻击的时候，角色是不能更新位置的，所以
    */
    bool canCharacterMove();

    /**
    *	 设置武器选择的AI部分
    */
    void setWeaponChoiceAI(WeaponChoiceAI* aAI);

    /**
    *	更换武器，如果更换成功就返回true，否则返回false 
    *   force表示是否强制更换武器
    */
    bool changeWeapon(WeaponTypeEnum type, bool force = false);

    /**
    *	返回当前武器的类型 
    */
    WeaponTypeEnum getCurrentWeaponType() { return m_currentWeapon->getWeaponType(); }

    /**
    *	返回指定武器类型的武器
    */
    Weapon* getWeaponByType(WeaponTypeEnum aType);

private:
    /**
    *	 是否满足系统攻击的
    */
    bool satisfySysAttack();

    GameCharacter*                              m_pOwner;           // 当前武器拥有者

    CC_SYNTHESIZE_READONLY(Weapon*, m_currentWeapon, CurrentWeapon);// 当前武器
    Weapon*                                     m_readyToUseWeapon; // 当要求换武器的时候，而前一个武器正在进行中，就有可能需要将更换的武器先保存一下，等到上一个武器用完

    CC_SYNTHESIZE_READONLY(WeaponChoiceAI*, m_weaponChoiceAI, WeaponChoiceAI);// 武器选择AI，这个也暴露出去
    
    typedef map<WeaponTypeEnum, Weapon*> WeaponMap;
    WeaponMap        m_allWeapons;                                  // 当前角色拥有的所有武器

    int                                         m_targetId;         // 临时记录上一次攻击的目标的id

    /**
    *	除了独立的武器有攻击间隔要求，就算中间换了武器，也有武器系统的最小攻击间隔事件 
    */
    float                                      m_lastAttackTime;   // 最近一次攻击
    float                                      m_nextAttackTime;   // 下一次允许的攻击时间
    const float                                 m_minAttackInterval;// 攻击的最小间隔
};

#endif