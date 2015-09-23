#ifndef __PROJECTILE_MOVING_PART_H__
#define __PROJECTILE_MOVING_PART_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
*	 ���е��ߵ��ƶ����ֵĻ��࣬�൱���Ƿ��е��ߵ��ƽ��������Ʒ��е��ߵ��ƶ�
*/
class ProjectileMovingPart
{
public:
    ProjectileMovingPart()
    {
        m_rate  =   1000;
    }

    virtual ~ProjectileMovingPart()
    {

    }

    void setOrientation(Vec2 orientation)
    {
        m_velocity  =   orientation * m_rate;
    }

    /**
    *	 ÿһ֡�и��µ�ǰ������
    */
   virtual void updateMovement(float dm) = 0;

protected:
    CC_SYNTHESIZE(Vec2, m_position, Position);                  // ��������ǰ����
    CC_SYNTHESIZE(float, m_rate, Rate);                         // �ٶȱ���
    CC_SYNTHESIZE(Vec2, m_targetPos, TargetPos);                // Ŀ������
    CC_SYNTHESIZE_READONLY(Vec2, m_velocity, Velocity);         // �ٶ�ʸ��
};

#endif