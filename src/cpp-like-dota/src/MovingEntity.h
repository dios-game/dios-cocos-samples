#ifndef __MOVING_ENTITY_H__
#define __MOVING_ENTITY_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* ������¼һ����ɫ��Ϊ���ƶ����������Ϣ�������ƶ��ٶȡ����ٶȡ���������Ϣ
*/
class MovingEntity
{
public:
    MovingEntity(float maxSpeed = 100, float maxForce = 130, float mass = 1, float radius = 45, float neighborRadius = 65)
    {
        m_maxSpeed          =   maxSpeed;
        m_maxForce          =   maxForce;
        m_mass              =   mass;
        m_radius            =   radius;
        m_neighborRadius    =   neighborRadius;
        m_position.setPoint(0, 0);
        m_velocity.setPoint(0, 0);
    }

    ~MovingEntity(){}

    CC_SYNTHESIZE(Vec2, m_position, Position);              // ��ǰ������
    CC_SYNTHESIZE_READONLY(Vec2, m_velocity, Velocity);     // �ٶȣ���ɫ����Ϊ���ٶȣ�
    CC_SYNTHESIZE(Vec2, m_realVelocity, RealVelocity);      // ʵ���ٶȣ�������������Ӱ�죩
    CC_SYNTHESIZE(float, m_mass, Mass);                     // ����
    CC_SYNTHESIZE(float, m_maxSpeed, MaxSpeed);             // ����ٶ�
    CC_SYNTHESIZE(float, m_maxForce, MaxForce);             // ���������
    CC_SYNTHESIZE(float, m_radius, Radius);                 // ��ɫ��ռ�뾶
    CC_SYNTHESIZE(float, m_neighborRadius, NeighborRadius); // �ھӰ뾶���ڴ˰뾶�ڵ�������ɫ����Ϊ�ھӣ�
    CC_SYNTHESIZE(int, m_formatioPosId, FormationPosId);    // �������ж�Ӧ��λ��id

    void setVelocity(Vec2 aVelocity)
    {
        // ������Ҫ���ٶȿ���������ٶ���
        if (aVelocity.lengthSquared() > m_maxSpeed * m_maxSpeed)
        {
            aVelocity.normalize();
            aVelocity  *=  m_maxSpeed;
        }

        m_velocity  =   aVelocity;
    }

    /**
    * ����ǰ���ķ��򣨵�λ������ 
    */
    Vec2 getHead()
    {
        return m_velocity.getNormalized();
    }

    float getSpeed()
    {
        return m_velocity.getLength();
    }
};

#endif