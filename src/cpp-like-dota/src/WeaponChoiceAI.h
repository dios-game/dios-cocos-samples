#ifndef __WEAPON_CHOICE_AI_H__
#define __WEAPON_CHOICE_AI_H__

#include <assert.h>
#include "WeaponControlSystem.h"
#include "GameCharacter.h"

class Weapon;

/**
*	��Ҫ�ǿ��ǵ���ʱʹ��ʲô�������ڲ�ͬ�Ľ�ɫ���в�ͬ���߼��ģ����Խ�
*   ��һ���߼�������һ���������ÿһ�ֽ�ɫʵ��һ����������������ѡ��
*   �������߼�
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
    *	ÿһ�ε��ã�������ݵ�ǰ���ѡ��һ�����ʵ��������ú���ֻ���������ĵط�������
    *   ��1�����趨����Ŀ���ʱ�򱻵���
    *   ��2����ÿ�η�������֮��ᱻ����
    *   ��������ÿ��ֻ��
    */
    void update()
    {
        // ��������һ�¸����������߼�
        choiceWeapon();
    }

    /**
    *	���ڵ��õ� 
    */
    virtual void regularUpdate(float dm)
    {

    }

    /**
    *	��Ϊ����ʲô������֮ǰ�Ĺ����йأ�������ÿ�ι�����ʱ����Ҫ�ص��ú�������Щ
    *   ��ɫ������������ȥ���Ǹ÷���
    */
    virtual void attack()
    {
        update();
    }

    /**
    *	�������˵�ǰ����Ŀ���ʱ�򱻵��ã�������ܻ�Ӱ���ɫ����ѡ����߼�
    */
    virtual void changeTarget()
    {

    }

    /**
    *	������ͨ��AI��Ĭ����������е��������Ч��
    */
    virtual bool userOrder(WeaponTypeEnum aType)
    {
        return false;
    }

protected:
    /**
    *	�ڴ˴���װ����������ѡ���߼� 
    */
    virtual void choiceWeapon() {}
    
    /**
    *	�ṩ�Ŀ�ݷ�����ѡ������ 
    */
    void changeWeapon(WeaponTypeEnum aType)
    {
        m_pOwner->getWeaponControlSystem()->changeWeapon(aType);
    }

    GameCharacter*    m_pOwner;                // ��Ӧ����������ϵͳ
};

#endif