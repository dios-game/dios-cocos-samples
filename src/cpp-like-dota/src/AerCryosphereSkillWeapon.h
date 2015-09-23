#ifndef __AER_CRYOSPHERE_SKILL_WEAPON_H__
#define __AER_CRYOSPHERE_SKILL_WEAPON_H__

#include "Weapon.h"
#include "GameCharacter.h"
#include "TimeTool.h"
#include "GameMap.h"
#include "MessageDispatcher.h"

/**
*	骑士的冰圈攻击，会对周围角色造成攻击，同时会将周围角色推开 
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

        // 记录一下当前的时间
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
    *	施展动画播放到要开始 
    */
    void onAttackEffect(string evt)
    {
        // 会对半径内的敌人造成一定伤害，同时会让敌人被向四周震开一下
        auto tmpEffectedCharacters  =   getAffectedCharacters();
        for (auto tmpIterator = tmpEffectedCharacters.begin(); tmpIterator != tmpEffectedCharacters.end(); 
            tmpIterator++)
        {
            // 依次对每个角色造成一定得影响
            effectLethality(*tmpIterator);
        }

        // 将能量归零
        m_pOwner->getAttribute().setEnergy(0);
    }

    /**
    *	 返回会受影响的角色
    */
    vector<GameCharacter*> getAffectedCharacters()
    {
        // 获取半径内的角色
        auto tmpPos =   m_pOwner->getShape()->getPosition();
        vector<GameCharacter*>  tmpCharacters   =   
            GamepMapSingleton->getCharactersInRadius(tmpPos, m_effectRadius);

        // 剔除相同类型的
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
    *	该技能对受影响角色的影响 
    */
    void effectLethality(GameCharacter* target)
    {
        /**
        *	这里就作为普通攻击吧 
        */
        auto tmpMsg = TelegramNormalAttack::create(m_pOwner->getId(), target->getId(), m_pOwner->getAttribute());
        tmpMsg->senderAtt.setAttack(m_lethality);
        Dispatch->dispatchMessage(*tmpMsg);

        /**
        *	 如果是攻击目标，同时进入受击状态
        */
        if (target->getId() == m_targetId)
        {
            target->getFSM()->changeState(GameCharacterHitedState::create());
        }
    }

    /**
    *	目前限制两次冰冻的条件也是时间问题 
    */
    float           m_minAttackInterval;
    double          m_lastAttackTime;               // 最近一次攻击时间
    double          m_nextAttackReadyTime;          // 下一次攻击准备完毕时间
    int             m_targetId;                     // 目标id

    const string    m_actionName;                   // 对应的角色的动画
    const float     m_effectRadius;                 // 受影响的范围
    const float     m_attRadius;                    // 发起攻击的半径
    const float     m_lethality;                    // 杀伤力
};

#endif