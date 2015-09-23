#ifndef __GOAL_TEAM_THINK_H__
#define __GOAL_TEAM_THINK_H__

#include "GoalComposite.h"
#include "GoalTeamAdvance.h"
#include "GoalTeamAttackTargetTeam.h"
#include "TeamManager.h"
#include "TimeTool.h"

class GameTeam;

/**
* 属于队伍级别的最高目标，在此处会对环境进行判断，然后设置当前队伍的合适目标 
*/
class GoalTeamThink : public GoalComposite<GameTeam>
{
public:
    GoalTeamThink(GameTeam* owner):GoalComposite<GameTeam>(owner), m_processInterval(0.2)
    {
        m_lastProcessTime   =   -1;
    }

    // @_@ 临时使用的，方便外部设置目标
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
    float       m_lastProcessTime;              // 作为队伍的大脑也没有必要process太快
    const float m_processInterval;
};

#endif