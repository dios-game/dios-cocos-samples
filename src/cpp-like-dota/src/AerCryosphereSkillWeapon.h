#ifndef __AER_CRYOSPHERE_SKILL_WEAPON_H__
#define __AER_CRYOSPHERE_SKILL_WEAPON_H__

#include "Weapon.h"
#include "GameCharacter.h"
#include "TimeTool.h"
#include "GameMap.h"
#include "MessageDispatcher.h"

/**
*	��ʿ�ı�Ȧ�����������Χ��ɫ��ɹ�����ͬʱ�Ὣ��Χ��ɫ�ƿ� 
*/
class AerCryosphereSkillWeapon : public Weapon
{
public:
    AerCryosphereSkillWeapon(GameCharacter* owner):Weapon(owner, AER_CRYOSPHERE_SKILL_WEAPON)
        , m_actionName("atk2"), m_effectRadius(300), m_attRadius(220), m_lethality(20)
    {
        m_minAttackInterval =   4;
    }

    ~AerCryosphereSkillWeapon()
    {

    }

    virtual void attack(GameCharacter* target) override
    {
        m_pOwner->getShape()->playAction(m_actionName, false,
            std::bind(&AerCryosphereSkillWeapon::onAttackEffect, this, std::placeholders::_1));

        // ��¼һ�µ�ǰ��ʱ��
        m_lastAttackTime        =   TimeTool::getSecondTime();
        m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
        m_targetId              =   target->getId();
    }

    virtual bool isInAttackRange(GameCharacter* target) override
    {
        auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
        auto tmpTargetPos   =   target->getMovingEntity().getPosition();
        return (tmpOwnerPos - tmpTargetPos).getLengthSq() <= m_attRadius * m_attRadius;
    }

    virtual bool isReadyForNextAttack() override
    {
        return m_nextAttackReadyTime < TimeTool::getSecondTime();
    }

    virtual bool isAttacking() override
    {
        return m_pOwner->getShape()->getCurrentAnimationName() == m_actionName;
    }

private:
    /**
    *	ʩչ�������ŵ�Ҫ��ʼ 
    */
    void onAttackEffect(string evt)
    {
        // ��԰뾶�ڵĵ������һ���˺���ͬʱ���õ��˱���������һ��
        auto tmpEffectedCharacters  =   getAffectedCharacters();
        for (auto tmpIterator = tmpEffectedCharacters.begin(); tmpIterator != tmpEffectedCharacters.end(); 
            tmpIterator++)
        {
            // ���ζ�ÿ����ɫ���һ����Ӱ��
            effectLethality(*tmpIterator);
        }

        // ����������
        m_pOwner->getAttribute().setEnergy(0);
    }

    /**
    *	 ���ػ���Ӱ��Ľ�ɫ
    */
    vector<GameCharacter*> getAffectedCharacters()
    {
        // ��ȡ�뾶�ڵĽ�ɫ
        auto tmpPos =   m_pOwner->getShape()->getPosition();
        vector<GameCharacter*>  tmpCharacters   =   
            GamepMapSingleton->getCharactersInRadius(tmpPos, m_effectRadius);

        // �޳���ͬ���͵�
        for (auto tmpIterator = tmpCharacters.begin(); tmpIterator != tmpCharacters.end(); )
        {
            if ((*tmpIterator)->getType() == m_pOwner->getType())
            {
                tmpIterator =   tmpCharacters.erase(tmpIterator);
            }
            else
            {
                tmpIterator++;
            }
        }
        return tmpCharacters;
    }

    /**
    *	�ü��ܶ���Ӱ���ɫ��Ӱ�� 
    */
    void effectLethality(GameCharacter* target)
    {
        /**
        *	�������Ϊ��ͨ������ 
        */
        auto tmpMsg = TelegramNormalAttack::create(m_pOwner->getId(), target->getId(), m_pOwner->getAttribute());
        tmpMsg->senderAtt.setAttack(m_lethality);
        Dispatch->dispatchMessage(*tmpMsg);

        /**
        *	 ����ǹ���Ŀ�꣬ͬʱ�����ܻ�״̬
        */
        if (target->getId() == m_targetId)
        {
            target->getFSM()->changeState(GameCharacterHitedState::create());
        }
    }

    /**
    *	Ŀǰ�������α���������Ҳ��ʱ������ 
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // ���һ�ι���ʱ��
    double          m_nextAttackReadyTime;          // ��һ�ι���׼�����ʱ��
    int             m_targetId;                     // Ŀ��id

    const string    m_actionName;                   // ��Ӧ�Ľ�ɫ�Ķ���
    const float     m_effectRadius;                 // ��Ӱ��ķ�Χ
    const float     m_attRadius;                    // ���𹥻��İ뾶
    const float     m_lethality;                    // ɱ����
};

#endif