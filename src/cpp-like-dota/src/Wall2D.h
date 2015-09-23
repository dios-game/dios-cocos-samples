#ifndef __WALL_2D_H__
#define __WALL_2D_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* �ڵ�ͼ�ϱ�ʾ���ܵ�ǽ����ֹ��ɫ�ܳ�ȥ�� 
*/
class Wall2D
{
public:
    Wall2D(Vec2 pointA, Vec2 pointB, Vec2 normal)
    {
        m_pointA    =   pointA;
        m_pointB    =   pointB;
        m_normal    =   normal.getNormalized();
    }

    CC_SYNTHESIZE_READONLY(Vec2, m_pointA, PointA);           // һ���ߵ�������
    CC_SYNTHESIZE_READONLY(Vec2, m_pointB, PointB);
    CC_SYNTHESIZE_READONLY(Vec2, m_normal, Normal);           // ���ߣ�ָ���ڲ�
};

#endif