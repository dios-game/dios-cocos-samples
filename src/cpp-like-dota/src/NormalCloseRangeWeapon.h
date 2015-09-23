#ifndef __NORMAL_CLOSE_RANGE_WEAPON_H__
#define __NORMAL_CLOSE_RANGE_WEAPON_H__

#include "GameCharacter.h"
#include "Weapon.h"

/**
*   ��ͨ�Ľ����빥��������������������н�ս�ͽ�ɫ�ر�����������ս�������ı��־��ǹ��������Ĳ���
*   @usage������������Ҫ�ڹ�������֡����֡�¼�
*/
class NormalCloseRangeWeapon : public Weapon
{
public:
    NormalCloseRangeWeapon(GameCharacter* owner, float minAttackInterval = 2, string actionName = "atk1");
    virtual ~NormalCloseRangeWeapon();

    virtual void attack(GameCharacter* target) override;
    virtual bool isInAttackRange(GameCharacter* target) override;
    virtual bool isReadyForNextAttack() override;
    virtual bool isAttacking() override;

protected:
    /**
    *	 ��ͨ�����빥������ֱ�Ӳ��Ŷ������ض�֡��ʱ������ã�������֡�¼�
    */
    virtual void onAttackEffect(string evt);

    /**
    *	��ʱ���� 
    */
    int             m_targetId;                     // ��ʱ���浱ǰ�����Ľ�ɫid

private:
    /**
    *  ��Ӧ�Ķ����ļ��еĶ������ƣ���Ҫ�ǿ��ǵ����������ļ���ʱ���������淶��ԭ��
    *  ��ͨ�Ľ����빥�����������Ͼ�ֻ��Ҫ���Ŷ�����OK��
    */
    const string m_actionName;

    /**
    * ��ͨ�����ķ�Χƫ�� 
    */
    const int   m_xOffset;                          // �����߾��뱻�����ߵ�x�����ϵľ����ȥ˫�������ʣ�µ�ֵ
    const int   m_yOffset;                          // ��������y�����ϵ�����ƫ��Ӧ���뱻�����ߵİ뾶�йأ����ǿ��ܻ�С��뾶

    /**
    *  ��ͨ���������ƻ����Ͼ�ֻ����̹������
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // ���һ�ι���ʱ��
    double          m_nextAttackReadyTime;          // ��һ�ι���׼�����ʱ��
};

#endif