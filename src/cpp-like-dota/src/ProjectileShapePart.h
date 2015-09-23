#ifndef __PROJECTILE_SHAPE_PART_H__
#define __PROJECTILE_SHAPE_PART_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
*	���е��ߵ����εĲ��֣������ڲ�ͬ��ʱ�����ӵ��
*   ��ͬ������
*/
class ProjectileShapePart : public Node
{
public:
    ProjectileShapePart()
    {

    }

    /**
    *	���ӵ��տ�ʼ���е�ʱ��
    */
    virtual void onLaunchStart() = 0;

    /**
    *	 �ڳ����ʱ��
    */
    virtual void onImpact() = 0;

    /**
    *	�Ƿ���Ա��������@_@����Ͷ��������е��ϵ��
    */
    virtual bool canBeDestroy() = 0;
};

#endif