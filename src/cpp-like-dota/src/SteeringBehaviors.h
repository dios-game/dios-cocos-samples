#ifndef __STEERING_BEHAVIORS_H__
#define __STEERING_BEHAVIORS_H__

#include "cocos2d.h"
#include "Formation.h"

using namespace cocos2d;

class GameCharacter;

/**
* ����������Ϊ���������߼����֣�ʩ����һ����ɫ���ϵĺ����ڴ˴����������
* 2014-10-9     ������ǣ����������ǣ�������ڲ���ı��ɫ�ƶ�����ģ����ǻ�Ӱ��λ
                �Ƶģ������һ�����뿪���Ǳ�ĳ���������߲���������
*/
class SteeringBehaviors
{
public:
    SteeringBehaviors(GameCharacter* owner);
    ~SteeringBehaviors();

    /**
    * �ⲿ��ȡ��ǰ���������Ľӿڣ��ýӿڻ�ȡ���ǲ������ⲿǣ������
    */
    Vec2 calculate();

    /**
    *	�ýӿڻ�ȡ�����������ⲿǣ����
    */
    Vec2 calculateWithTraction();

    void setTarget(Vec2 t) { m_vTarget = t; }
    
    void setTargetId(int id) { m_targetId = id; }

    /**
    *	 ����ǣ������
    */
    void setTraction(Vec2 aTraction) { m_traction = aTraction; }

    /**
    * �����������Ŀ����͹ر� 
    */
    void seekOn() { m_behaviorsFlag |= SEEK; }
    void seekOff() { if (On(SEEK)) m_behaviorsFlag ^= SEEK;}
    void arriveOn() { m_behaviorsFlag |= ARRIVE; }
    void arriveOff() { if (On(ARRIVE)) m_behaviorsFlag ^= ARRIVE; }
    void separationOn() { m_behaviorsFlag |= SEPARATION; }
    void separationOff() { if (On(SEPARATION)) m_behaviorsFlag ^= SEPARATION; }
    void wallAvoidanceOn() { m_behaviorsFlag |= WALL_AVOIDANCE; }
    void wallAvoidanceOff() { if (On(WALL_AVOIDANCE)) m_behaviorsFlag ^= WALL_AVOIDANCE; }
    void pursuitOn() { m_behaviorsFlag |= PURSUIT; }
    void pursuitOff() { if(On(PURSUIT)) m_behaviorsFlag ^= PURSUIT; }
    void keepFormationOn() { m_behaviorsFlag |= KEEP_FORMATION; }
    void keepFormationOff() { if(On(KEEP_FORMATION)) m_behaviorsFlag ^= KEEP_FORMATION; }

private:
    /**
    *	���ﻹ�ǲ����ⲿ���ã��ⲿ����ʹ��ǣ������ʱ��ǣ��������Ϊ(0, 0)��OK�� 
    */
    void tractionOn() { m_behaviorsFlag |= TRACTION; }
    void tractionOff() { if (On(TRACTION)) m_behaviorsFlag ^= TRACTION; }

private:
    /**
    *  ����������Ϊ
    */
    Vec2 seek(const Vec2& target);
    
    Vec2 arrive(const Vec2& target);

    // ������������ƶ���
    Vec2 separation();

    // �������ƶ��岻ײ�����ܵ�ǽ��
    Vec2 wallAvoidance();

    // ����������ɫ׷��ָ����ɫ��
    Vec2 pursuit(int targetId);

    // �����������͵�������
    Vec2 keepFormation(Formation& aFormation, int posId);

private:
    // �ж��Ƿ����ھӣ�������ھӣ��ý�ɫ�ͻ��ܵ��ھӵ�Ӱ��
    bool isNeighbor(GameCharacter* other);

    /**
    *   ��m_vSteeringForce������force��ͬʱ�ж��Ƿ񵽴���������������
    *   ������������ˣ��ͷ���false
    */
    bool accumulateForce(Vec2& steeringForce, Vec2 force);

private:
    /**
    * ��ǰʹ�õ���Ϊ�����ı�� 
    */
    enum BehaviorTypeEnum
    {
        NONE                =   0,                      // ��ʼ����
        SEEK                =   1,                      // �嵽ָ����λ��
        ARRIVE              =   1 << 1,                 // ����ָ��λ��
        SEPARATION          =   1 << 2,                 // �������밤��һ��Ľ�ɫ
        WALL_AVOIDANCE      =   1 << 3,                 // �����ܿ�ǽ�ڵ�
        PURSUIT             =   1 << 4,                 // ׷��ָ����ɫ
        KEEP_FORMATION      =   1 << 5,                 // ��������
        TRACTION            =   1 << 6,                 // ǣ����
    };

    // ���ĳ�����͵��������Ƿ���
    bool On(BehaviorTypeEnum bt){return (m_behaviorsFlag & bt) == bt;}

    GameCharacter*  m_pOwner;

    int             m_behaviorsFlag;                    // ������¼��ǰ��������Щ����
    Vec2            m_vSteeringForce;                   // ��ǰ���������������

    /**
    * ��seek��arrive��Ϊ�йص����� 
    */
    Vec2            m_vTarget;                          // Ŀ������
    const float     m_arrivePrecision;                  // �ӽ���ʱ���ж��ǵ���ľ���

    /**
    * ��separation��Ϊ��ص�����
    */
    const float     m_separationMagnify;                // ������ı���

    /**
    * ��wallavoidance��Ϊ��ص����� 
    */
    const float     m_wallAvoidanceMagnify;             // ������ı���

    /**
    * ��pursue��Ϊ�йص����� 
    */
    int             m_targetId;                         // ����׷���Ķ���id

    /**
    *	�й��ⲿǣ����������
    */
    CC_SYNTHESIZE_READONLY(Vec2, m_traction, Traction);
};

#endif