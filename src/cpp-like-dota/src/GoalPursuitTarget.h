#ifndef __GOAL_PURSUIT_TARGET_H__
#define __GOAL_PURSUIT_TARGET_H__

#include "Goal.h"
#include "GameCharacter.h"
#include "EntityManager.h"

/**
* ׷��һ��ָ��Ŀ���ԭ��Ŀ�ֱ꣬����Ŀ����ʧ
*/
class GoalPursuitTarget : public Goal<GameCharacter>
{
public:
    GoalPursuitTarget(GameCharacter* owner, int targetId):Goal<GameCharacter>(owner)
    {
        m_targetId  =   targetId;
    }

    virtual string getGoalDescribe()
    {
        char tmpStr[40];
        sprintf(tmpStr, "GoalPursuitTarget : targetId = %d", m_targetId);
        return tmpStr;
    }

protected:
    virtual void activate() override
    {
        // @_@ ��Ϊ���ǽ�ɫĿ�꣬��������ֱ���޸Ľ�ɫ��������Ϊ
        m_pOwner->getSteeringBehaviros()->setTargetId(m_targetId);
        m_pOwner->getSteeringBehaviros()->pursuitOn();
    }

    virtual GoalStateEnum process() override
    {
        activateIfInactive();

        // ֱ����ɫ�����ڣ����϶���Ŀ��ʧ��
        if (!isTargetAlive())
        {
            m_goalState = failed;
        }

        return m_goalState;
    }

    virtual void terminate() override
    {
        m_pOwner->getSteeringBehaviros()->pursuitOff();
    }

private:
    bool isTargetAlive()
    {
        auto tmpCharacter   =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
        return tmpCharacter != nullptr && tmpCharacter->isAlive();
    }

    int     m_targetId;                 // Ҫ׷����Ŀ��
};

#endif