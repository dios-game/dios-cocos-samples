#ifndef __GOAL_TEAM_ADVANCE_H__
#define __GOAL_TEAM_ADVANCE_H__

#include "Goal.h"
#include "GameTeam.h"
#include "MathTool.h"

/**
* ���鼯����ǰ�ƶ���Ŀ�꣬�ƶ���ָ����xλ��
* @_@ ����ֻ�ܶ����ƽ���OK�ˣ�����Ҫ��ʲô��ǰ�Ļ���
*/
class GoalTeamAdvance : public Goal<GameTeam>
{
public:
    GoalTeamAdvance( GameTeam* owner, float xPos ):Goal<GameTeam>(owner)
    {
        m_xPos  =   xPos;
    }

protected:
    virtual void activate() override
    {
        m_pOwner->collectiveForwardStart();
    }

    virtual GoalStateEnum process() override
    {
        activateIfInactive();

        // ��ǰ����λ�ú󲢰ں���������Ŀ��
        if (abs(m_pOwner->getTeamFormation().getFormationAnchor().x - m_xPos) <= 30)
        {
            m_goalState =   completed;
        }

        if (m_pOwner->getTeamFormation().getFormationType() == Formation::FORMATION_TYPE_RIGHT)
        {
            if (m_pOwner->getTeamFormation().getFormationAnchor().x >= m_xPos)
            {
                m_goalState =   completed;
            }
        }
        else
        {
            if (m_pOwner->getTeamFormation().getFormationAnchor().x <= m_xPos)
            {
                m_goalState =   completed;
            }
        }

        return m_goalState;
    }

    virtual void terminate() override
    {
        m_pOwner->collectiveForwardEnd();
    }

private:
    float       m_xPos;
};

#endif