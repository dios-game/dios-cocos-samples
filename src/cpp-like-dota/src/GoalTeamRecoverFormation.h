#ifndef __GOAL_TEAM_RECOVER_FORMATION_H__
#define __GOAL_TEAM_RECOVER_FORMATION_H__

#include "Goal.h"
#include "GameTeam.h"
#include "Telegram.h"
#include "GameCharacter.h"
#include "TimeTool.h"

/**
* ����ָ���ǰ���͵�Ŀ�� 
*/
class GoalTeamRecoverFormation : public Goal<GameTeam>
{
public:
    GoalTeamRecoverFormation(GameTeam* owner):Goal<GameTeam>(owner)
    {
        
    }

protected:
    virtual void activate() override
    {
        // ֱ�ӰѶ�Ա��������ȷ��λ����
        auto tmpFormation   =   m_pOwner->getTeamFormation();
        auto tmpMemebers    =   m_pOwner->getMembers();
        for (auto tmpIterator = tmpMemebers.begin(); tmpIterator != tmpMemebers.end(); tmpIterator++)
        {
            GameCharacter* tmpCharacter        =   *tmpIterator;
            MovingEntity& tmpMovingEntity      =   tmpCharacter->getMovingEntity();
            tmpMovingEntity.setPosition(tmpFormation.getPositionByPosId(tmpMovingEntity.getFormationPosId()));
        }
    }

    virtual GoalStateEnum process() override
    {
        activateIfInactive();
        return completed;
    }

private:
    double          m_activeTime;
};

#endif