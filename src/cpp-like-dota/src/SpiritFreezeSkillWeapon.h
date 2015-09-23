#ifndef __SPIRIT_FREEZE_SKILL_WEAPON_H__
#define __SPIRIT_FREEZE_SKILL_WEAPON_H__

#include "cocos2d.h"
#include "Weapon.h"
#include "GameCharacterState.h"

using namespace std;

/**
*	ѩ����ı���ħ�����øü��ܹ������ֿ����ڶ������ϲ�������Ч�����ö���
*   ���붳��״̬����ʱ��
*/
class SpiritFreezeSkillWeapon : public Weapon
{
public:
    SpiritFreezeSkillWeapon(GameCharacter* owner);
    virtual ~SpiritFreezeSkillWeapon();

    virtual void attack(GameCharacter* target) override;

    virtual bool isInAttackRange(GameCharacter* target) override;

    virtual bool isReadyForNextAttack() override;

    virtual bool isAttacking() override;

    virtual void update(float dm) override;

private:
    /**
    *	ʩչ�������ŵ�Ҫ��ʼ 
    */
    void onAttackEffect(string evt);

    /**
    *	Ŀ���Ƿ���� 
    */
    bool isTargetAlive();

    /**
    *	Ŀǰ�������α���������Ҳ��ʱ������ 
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // ���һ�ι���ʱ��
    double          m_nextAttackReadyTime;          // ��һ�ι���׼�����ʱ��

    int             m_targetId;                     // ����Ŀ��id

    const string    m_actionName;                   // ��������
    const float     m_attRadius;                    // �����뾶

private:
    bool            m_lastTestIsReady;              // ���һ�ε���isReadyForNextAttack
};

#endif