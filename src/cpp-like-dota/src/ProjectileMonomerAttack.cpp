#include "ProjectileMonomerAttack.h"
#include "MathTool.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

ProjectileMonomerAttack::ProjectileMonomerAttack( GameCharacterAttribute& att, int targetId )
    :Projectile(att), m_collisionDisSq(900)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xuejingling-texiao.ExportJson");
    m_targetId  =   targetId;
    m_shapePart =   nullptr;
}

ProjectileMonomerAttack::~ProjectileMonomerAttack()
{
    
}

void ProjectileMonomerAttack::update( float dm )
{
    // 判断是否到达
    if (canUpdateMovement())
    {
        if (testCollision(m_lastPos, m_movingPart->getPosition(), m_movingPart->getTargetPos()))
        {
            // 禁止更新位移
            updateMovementOff();
            // 说明此事闪电球已经到位，开始继续播放动画
            m_shapePart->onImpact();

            // 发送消息给受击者，@_@发送者id没有必要
            auto tmpMsg = TelegramNormalAttack::create(m_ownerId, m_targetId, m_senderAtt);
            Dispatch->dispatchMessage(*tmpMsg);
        }
    }
    else
    {
        // 当动画播放完毕后就
        if (m_shapePart->canBeDestroy())
        {
            updateOff();
        }
    }
}

bool ProjectileMonomerAttack::testCollision( Vec2 aPos1, Vec2 aPos2, Vec2 aTargetPos )
{
    Vec2 tmpTargetToPos1    =   aPos1 - aTargetPos;
    float tmpDistance1      =   tmpTargetToPos1.getLengthSq();
    if (tmpDistance1 <= m_collisionDisSq)
    {
        return true;
    }

    Vec2 tmpTargetToPos2    =   aPos2 - aTargetPos;
    float tmpDistance2      =   tmpTargetToPos2.getLengthSq();
    if (tmpDistance2 <= m_collisionDisSq)
    {
        return true;
    }

    Vec2 tmpPos2ToPos1  =   aPos1 - aPos2;
    Vec2 tmpVertical    =   tmpTargetToPos1 - 
        tmpPos2ToPos1.dot(tmpTargetToPos1) * tmpPos2ToPos1 / tmpPos2ToPos1.getLengthSq();
    if (Vec2::angle(tmpTargetToPos1, tmpVertical) * Vec2::angle(tmpTargetToPos2, tmpVertical) <= 0)
    {
        return tmpVertical.getLengthSq() <= m_collisionDisSq;
    }

    return false;
}
