#ifndef __NORMAL_LONG_RANGE_WEAPON_H__
#define __NORMAL_LONG_RANGE_WEAPON_H__

#include "Weapon.h"
#include "GameCharacter.h"
#include "Projectile.h"

/**
*	��ͨԶ���빥�����������Ƿ����һ��������ȥ����Ŀ�� 
*/
class NormalLongRangeWeapon : public Weapon
{
public:
    /**
    *	����ʱ��Ҫָ������ġ��ӵ����͡�����Ҫ��TMD�����н�ɫ��һ������
    */
    NormalLongRangeWeapon(GameCharacter* owner, ProjectileTypeEnum type, float attDistance, 
        string attAnimationName = "atk1",float minAttackInterval = 2);

    virtual void attack(GameCharacter* target);
    virtual bool isInAttackRange(GameCharacter* target);
    virtual bool isReadyForNextAttack();
    virtual bool isAttacking();

private:
    /**
    *	�����䡰�ӵ���ʱ�� 
    */
    void onLaunchProjectile(string evt);

    /**
    *	Ŀ���Ƿ���� 
    */
    bool isTargetAlive();

    float           m_attRadius;                    // �����뾶
    float           m_minAttInterval;               // ��С�������
    const string    m_actionName;                   // �����ʱ��Ľ�ɫ����

    double   m_lastAttackTime;                         // ���һ�η��͹�����ʱ��
    double   m_nextAttackReadyTime;                    // 

    int     m_targetId;

    ProjectileTypeEnum m_projectileType;            // ���ӵ�������
};

#endif