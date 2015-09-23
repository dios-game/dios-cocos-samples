#ifndef __GOAL_TEAM_GUARD_H__
#define __GOAL_TEAM_GUARD_H__

#include "GoalComposite.h"
#include "GameTeam.h"
#include "GoalTeamAttackTargetTeam.h"

/**
*	����Ŀ�꣬�����Ŀ�꿿��һ�������ͷ��𹥻� 
*/
class GoalTeamGuard : public GoalComposite<GameTeam>
{
public:
    GoalTeamGuard(GameTeam* owner):GoalComposite<GameTeam>(owner), m_guardDistance(700)
    {

    }

protected:
    virtual void activate() override
    {

    }

    virtual GoalStateEnum process() override
    {
        activateIfInactive();

        auto tmpTarget  =   getTeamInGuradDistance();
        if (tmpTarget != nullptr && m_subgoalList.size() == 0)
        {
            addSubgoal(new GoalTeamAttackTargetTeam(m_pOwner, tmpTarget));
        }

        processSubgoals();
        return active;
    }

private:
    // �������Ҷ��������ľ��䷶Χ�ڣ��ͷ��أ����򷵻�null
    GameTeam* getTeamInGuradDistance()
    {
        // @_@ ������ʱ�򵥼�����Ҷ�����0
        GameTeam* tmpPlayerTeam =   TeamMgr->getTeamFromId(0);
        if (tmpPlayerTeam != nullptr)
        {
            auto tmpDistance    =   m_pOwner->getTeamFormation().getFormationAnchor().x - 
                tmpPlayerTeam->getTeamFormation().getFormationAnchor().x;
            if (tmpDistance <= m_guardDistance)
            {
                return tmpPlayerTeam;
            }
        }

        return nullptr;
    }

    const float m_guardDistance;            // �������
};

#endif