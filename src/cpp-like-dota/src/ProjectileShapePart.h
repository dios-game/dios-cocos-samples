#ifndef __PROJECTILE_SHAPE_PART_H__
#define __PROJECTILE_SHAPE_PART_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
*	飞行道具的外形的部分，并且在不同的时候可以拥有
*   不同的样子
*/
class ProjectileShapePart : public Node
{
public:
    ProjectileShapePart()
    {

    }

    /**
    *	当子弹刚开始飞行的时候
    */
    virtual void onLaunchStart() = 0;

    /**
    *	 在冲击的时候
    */
    virtual void onImpact() = 0;

    /**
    *	是否可以被清除掉，@_@这个和动画还是有点关系的
    */
    virtual bool canBeDestroy() = 0;
};

#endif