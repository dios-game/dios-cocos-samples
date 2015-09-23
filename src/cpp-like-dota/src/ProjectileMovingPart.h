#ifndef __PROJECTILE_MOVING_PART_H__
#define __PROJECTILE_MOVING_PART_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
*	 飞行道具的移动部分的基类，相当于是飞行道具的推进器，控制飞行道具的移动
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
    *	 每一帧中更新当前的坐标
    */
   virtual void updateMovement(float dm) = 0;

protected:
    CC_SYNTHESIZE(Vec2, m_position, Position);                  // 飞行器当前坐标
    CC_SYNTHESIZE(float, m_rate, Rate);                         // 速度标量
    CC_SYNTHESIZE(Vec2, m_targetPos, TargetPos);                // 目标坐标
    CC_SYNTHESIZE_READONLY(Vec2, m_velocity, Velocity);         // 速度矢量
};

#endif