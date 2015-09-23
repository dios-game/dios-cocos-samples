#ifndef __WEAPON_CONTROL_SYSTEM_H__
#define __WEAPON_CONTROL_SYSTEM_H__

#include <map>
#include "Weapon.h"

using namespace std;

class GameCharacter;
class WeaponChoiceAI;

/**
* ��������ϵͳ�����︺��ά����ɫ���ϵ����й�����ʽ��������ͨ���������ܹ����ȣ�����
* ʹ�����ַ�ʽ���������߼�Ҳ��������ڹ�����ʽӦ����Ҫ����ĳЩ�������ó�ʹ��ĳ��
* ����������
*/
class WeaponControlSystem
{
public:
    WeaponControlSystem(GameCharacter* owner);
    ~WeaponControlSystem();

    /**
    * ��������ϵͳ����������� 
    */
    void addWeapon(Weapon* aWeapon);

    /**
    *	����һ�½�ɫ����������ϵͳ��˼�����֣����ݵ�ǰ���ѡ����ȷ������
    */
    void update();

    /**
    *	���ڱ����õĺ�������Щ�߼�����Ҫ����һЩ�����
    */
    void regularUpdate(float dm);

    /**
    *	���ù���Ŀ���ʱ����� 
    */
    void setAttackTarget(int targetId);

    /**
    * ʹ�õ�ǰ�������ҹ���ĳ��Ŀ�� 
    */
    void takeWeaponAndAttack(GameCharacter* target);

    /**
    * ����ʹ�õ�ǰ����������£�target�Ƿ��ڹ�����Χ��
    */
    bool isInAttackRange(GameCharacter* target);

    /**
    * @_@ ��Ҫ����Ϊ������ϵͳ������ʱ�򣬽�ɫ�ǲ��ܸ���λ�õģ�����
    */
    bool canCharacterMove();

    /**
    *	 ��������ѡ���AI����
    */
    void setWeaponChoiceAI(WeaponChoiceAI* aAI);

    /**
    *	������������������ɹ��ͷ���true�����򷵻�false 
    *   force��ʾ�Ƿ�ǿ�Ƹ�������
    */
    bool changeWeapon(WeaponTypeEnum type, bool force = false);

    /**
    *	���ص�ǰ���������� 
    */
    WeaponTypeEnum getCurrentWeaponType() { return m_currentWeapon->getWeaponType(); }

    /**
    *	����ָ���������͵�����
    */
    Weapon* getWeaponByType(WeaponTypeEnum aType);

private:
    /**
    *	 �Ƿ�����ϵͳ������
    */
    bool satisfySysAttack();

    GameCharacter*                              m_pOwner;           // ��ǰ����ӵ����

    CC_SYNTHESIZE_READONLY(Weapon*, m_currentWeapon, CurrentWeapon);// ��ǰ����
    Weapon*                                     m_readyToUseWeapon; // ��Ҫ��������ʱ�򣬶�ǰһ���������ڽ����У����п�����Ҫ�������������ȱ���һ�£��ȵ���һ����������

    CC_SYNTHESIZE_READONLY(WeaponChoiceAI*, m_weaponChoiceAI, WeaponChoiceAI);// ����ѡ��AI�����Ҳ��¶��ȥ
    
    typedef map<WeaponTypeEnum, Weapon*> WeaponMap;
    WeaponMap        m_allWeapons;                                  // ��ǰ��ɫӵ�е���������

    int                                         m_targetId;         // ��ʱ��¼��һ�ι�����Ŀ���id

    /**
    *	���˶����������й������Ҫ�󣬾����м任��������Ҳ������ϵͳ����С��������¼� 
    */
    float                                      m_lastAttackTime;   // ���һ�ι���
    float                                      m_nextAttackTime;   // ��һ������Ĺ���ʱ��
    const float                                 m_minAttackInterval;// ��������С���
};

#endif