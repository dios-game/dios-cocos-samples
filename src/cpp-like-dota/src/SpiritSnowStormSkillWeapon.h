#ifndef __SPIRIT_SNOW_STORM_SKILL_WEAPON_H__
#define __SPIRIT_SNOW_STORM_SKILL_WEAPON_H__

#include "Weapon.h"

/**
*	 ѩ����ı���ѩ���ܣ�������Ŀ�����Ͼ���һ������磬
*/
class SpiritSnowStormSkillWeapon : public Weapon
{
public:
    SpiritSnowStormSkillWeapon(GameCharacter* owner);

    virtual void attack(GameCharacter* target);
    virtual bool isInAttackRange(GameCharacter* target);
    virtual bool isReadyForNextAttack();
    virtual bool isAttacking();
    virtual void update(float dm);

private:
    /**
    *	 ��ɫ�������ŵ���ʼ������������һ֡��
    */
    void onAttackEffect(string evt);

    /**
    *	Ŀ���Ƿ���� 
    */
    bool isTargetAlive();

    float           m_attRadius;                    // �����뾶
    const string    m_actionName;                   // �����ʱ��Ľ�ɫ����

    int             m_targetId;

    bool            m_lastTestIsReady;              // ���һ�ε���isReadyForNextAttack���
};

#endif