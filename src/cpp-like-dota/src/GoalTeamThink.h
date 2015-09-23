#ifndef __GOAL_TEAM_THINK_H__
#define __GOAL_TEAM_THINK_H__

#include "GoalComposite.h"
#include "GoalTeamAdvance.h"
#include "GoalTeamAttackTargetTeam.h"
#include "TeamManager.h"
#include "TimeTool.h"

class GameTeam;

/**
* ���ڶ��鼶������Ŀ�꣬�ڴ˴���Ի��������жϣ�Ȼ�����õ�ǰ����ĺ���Ŀ�� 
*/
class GoalTeamThink : public GoalComposite<GameTeam>
{
public:
    GoalTeamThink(GameTeam* owner):GoalComposite<GameTeam>(owner), m_processInterval(0.2)
    {
        m_lastProcessTime   =   -1;
    }

    // @_@ ��ʱʹ�õģ������ⲿ����Ŀ��
    void addSubgoal(Goal* aGoal)
    {
        GoalComposite<GameTeam>::addSubgoal(aGoal);
    }

    virtual void activate() override
    {

    }

    virtual GoalStateEnum process() override
    {
        if (TimeTool::getSecondTime() - m_lastProcessTime > m_processInterval)
        {
            m_lastProcessTime   =   TimeTool::getSecondTime();
            return GoalComposite<GameTeam>::process();
        }
        return active;
    }

private:
    float       m_lastProcessTime;              // ��Ϊ����Ĵ���Ҳû�б�Ҫprocess̫��
    const float m_processInterval;
};

#endif