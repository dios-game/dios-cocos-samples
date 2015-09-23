#include "SteeringBehaviors.h"
#include "GameCharacter.h"
#include "MathTool.h"
#include "EntityManager.h"
#include "GameTeam.h"
#include "GameMap.h"

SteeringBehaviors::SteeringBehaviors( GameCharacter* owner ):m_arrivePrecision(1),
    m_separationMagnify(1500), m_wallAvoidanceMagnify(800)
{
    m_pOwner        =   owner;
    m_behaviorsFlag =   NONE;
    m_targetId      =   INVALID_GAME_ENTITY_ID;
}

SteeringBehaviors::~SteeringBehaviors()
{

}

cocos2d::Vec2 SteeringBehaviors::calculate()
{
    m_vSteeringForce.setPoint(0, 0);

    /**
    * Ҫ֪��ÿһ�������������ȼ���ʵ�ǲ�ͬ�ģ�������Ҫ��Ҫ��֤����֮�䲻���ص���
    * ײǽ��Ȼ�����arrive��seek
    */
    if (On(WALL_AVOIDANCE) && !accumulateForce(m_vSteeringForce, wallAvoidance()))
    {
        return m_vSteeringForce;
    }

    if (On(SEPARATION) && !accumulateForce(m_vSteeringForce, separation()))
    {
        return m_vSteeringForce;
    }

    // @_@ ����������ⲿǣ������һ���ǲ����ŵ�
    if (On(TRACTION) && !accumulateForce(m_vSteeringForce, m_traction))
    {
        return m_vSteeringForce;
    }

    if (On(SEEK) && !accumulateForce(m_vSteeringForce, seek(m_vTarget)))
    {
        return m_vSteeringForce;
    }

    if (On(ARRIVE) && !accumulateForce(m_vSteeringForce, arrive(m_vTarget)))
    {
        return m_vSteeringForce;
    }

    if (On(PURSUIT) && !accumulateForce(m_vSteeringForce, pursuit(m_targetId)))
    {
        return m_vSteeringForce;
    }

    auto tmpFormation       =   m_pOwner->getTeam()->getTeamFormation();
    auto tmpFormationPosId  =   m_pOwner->getMovingEntity().getFormationPosId();
    if (On(KEEP_FORMATION) && !accumulateForce(m_vSteeringForce, keepFormation(tmpFormation, tmpFormationPosId)))
    {
        return m_vSteeringForce;
    }

    return m_vSteeringForce;
}

cocos2d::Vec2 SteeringBehaviors::calculateWithTraction()
{
    tractionOn();
    calculate();
    tractionOff();
    return m_vSteeringForce;
}

cocos2d::Vec2 SteeringBehaviors::seek( const Vec2 &target )
{
    auto tmpMovingEntity    =   m_pOwner->getMovingEntity();
    Vec2 tmpDesiredVelocity = 
        (target - tmpMovingEntity.getPosition()).getNormalized()
        * tmpMovingEntity.getMaxSpeed();
    return tmpDesiredVelocity - tmpMovingEntity.getVelocity();
}

cocos2d::Vec2 SteeringBehaviors::arrive( const Vec2& target )
{
    auto tmpMovingEntity    =   m_pOwner->getMovingEntity();
    Vec2 tmpToTarget        =   target - tmpMovingEntity.getPosition();

    float dist  =   tmpToTarget.length();
    dist        =   dist < m_arrivePrecision ? 0 : dist;
    if (dist > 0)
    {
        // �������ٶȣ����������Ŀ϶��������ķ�ʽ�ӽ���ȥ
        float tmpSpeed  =   dist * 10;
        tmpSpeed = tmpSpeed > tmpMovingEntity.getMaxSpeed() ? tmpMovingEntity.getMaxSpeed() : tmpSpeed;
        Vec2 tmpDesiredVelocity =   tmpToTarget * tmpSpeed / dist;
        return tmpDesiredVelocity - tmpMovingEntity.getVelocity();
    }

    return Vec2(0,0);
}

cocos2d::Vec2 SteeringBehaviors::separation()
{
    Vec2 tmpForce;
    auto tmpIterator    =   EntityMgr->getEntityMap()->begin();
    for (; tmpIterator != EntityMgr->getEntityMap()->end(); tmpIterator++)
    {
        auto tmpCharacter   =   dynamic_cast<GameCharacter*>(tmpIterator->second);
        if (tmpCharacter == m_pOwner || !isNeighbor(tmpCharacter))
        {
            continue;
        }

        auto tmpToOwner =   m_pOwner->getMovingEntity().getPosition() - tmpCharacter->getMovingEntity().getPosition();
        // �����������ý�ɫ��owner�ľ���ɷ��ȣ�ע������ľ����Ǽ�ȥ�������뾶��
        auto tmpLen     =   tmpToOwner.getLength() - (m_pOwner->getMovingEntity().getRadius() + tmpCharacter->getMovingEntity().getRadius());
        if (tmpLen <= 0)
        {
            tmpLen  =   1;
        }
        tmpForce        +=  m_separationMagnify * tmpToOwner.getNormalized() / tmpLen;
    }

    return tmpForce;
}

cocos2d::Vec2 SteeringBehaviors::wallAvoidance()
{
    auto tmpMovingEntity    =   m_pOwner->getMovingEntity();
    Vec2 tmpForce;
    auto tmpAllWalls    =   GamepMapSingleton->getWalls();
    for (auto tmpIterator = tmpAllWalls.begin(); tmpIterator != tmpAllWalls.end(); tmpIterator++)
    {
        // �ֱ�������ÿ���ߵľ���
        auto tmpWallToOwner =   tmpMovingEntity.getPosition() - tmpIterator->getPointA();
        auto tmpDot         =   tmpWallToOwner.dot(tmpIterator->getNormal());
        if (tmpDot >= tmpMovingEntity.getRadius())
        {
            continue;
        }
        // @_@ ��������ȥ�ˣ�����ͻ����൱�ھ����൱��
        if (tmpDot <= 0)
        {
            tmpDot  =   1;
        }
        tmpForce    +=  m_wallAvoidanceMagnify * tmpIterator->getNormal() / tmpDot;
    }
    return tmpForce;
}

cocos2d::Vec2 SteeringBehaviors::pursuit( int targetId )
{
    Vec2 tmpForce;
    auto tmpCharacter           =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(targetId));
    if (tmpCharacter != nullptr)
    {
        auto tmpOwnerMovingEntity   =   m_pOwner->getMovingEntity();
        auto tmpTargetMovingEntity  =   tmpCharacter->getMovingEntity();
        // ������ݶ����������������Լ��ٶȷ������ж�seek��ƫ����ƫ��
        Vec2 tmpOffset              =   (tmpTargetMovingEntity.getRadius() + tmpOwnerMovingEntity.getRadius()) * Vec2(1, 0);
        if (tmpOwnerMovingEntity.getPosition().x < tmpTargetMovingEntity.getPosition().x)
        {
            // ��ǰ��ɫ��Ŀ����࣬��Ŀ�������ƶ��У�seekĿ�����
            tmpOffset   *=  -1;
        }

        return seek(tmpTargetMovingEntity.getPosition() + tmpOffset);
    }

    return tmpForce;
}

bool SteeringBehaviors::isNeighbor( GameCharacter* other )
{
    auto tmpOwnerMovingEntity   =   m_pOwner->getMovingEntity();
    auto tmpOtherMovingEntity   =   other->getMovingEntity();
    return (tmpOwnerMovingEntity.getPosition() - tmpOtherMovingEntity.getPosition()).getLengthSq() 
        <= tmpOwnerMovingEntity.getNeighborRadius() * tmpOwnerMovingEntity.getNeighborRadius();
}

bool SteeringBehaviors::accumulateForce( Vec2& steeringForce, Vec2 force )
{
    auto tmpOwnerMovingEntity   =   m_pOwner->getMovingEntity();
    auto tmpLeftForce           =   tmpOwnerMovingEntity.getMaxForce() - steeringForce.getLength();
    
    // �����ǰ���������Ѿ�������������������
    if (tmpLeftForce <= 0)
    {
        return false;
    }

    if (tmpLeftForce >= force.getLength())
    {
        steeringForce   +=  force;
    }
    else
    {
        steeringForce   +=  force.getNormalized() * tmpLeftForce;
    }
    return true;
}

cocos2d::Vec2 SteeringBehaviors::keepFormation( Formation& aFormation, int posId )
{
    return arrive(aFormation.getPositionByPosId(posId));
}
