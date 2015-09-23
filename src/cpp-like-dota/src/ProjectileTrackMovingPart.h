#ifndef __PROJECTILE_TRACK_MOVING_PART_H__
#define __PROJECTILE_TRACK_MOVING_PART_H__

#include "GameCharacter.h"
#include "ProjectileMovingPart.h"
#include "EntityManager.h"

/**
*	����Ŀ����ƶ���ʽ���趨Ŀ���᲻ͣ���޸�������ǰ�� 
*/
class ProjectileTrackMovingPart : public ProjectileMovingPart
{
public:
    ProjectileTrackMovingPart(int targetId)
    {
        m_targetId  =   targetId;
        GameCharacter* tmpTarget    =   
            dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
        m_targetPos =   tmpTarget->getShape()->getCenterPos();
    }

    virtual void updateMovement(float dm)
    {
        GameCharacter* tmpTarget    =   
            dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
        if (tmpTarget != nullptr)
        {
            m_targetPos =   tmpTarget->getShape()->getCenterPos();
            Vec2 tmpToTarget    =   m_targetPos - m_position;
            tmpToTarget.normalize();
            m_velocity          =   tmpToTarget * m_rate;
        }

        // �޸�λ��
        m_position          +=  m_velocity * dm;
    }

private:
    int                 m_targetId;             // ����Ŀ��
};

#endif