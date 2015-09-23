#include "Projectile.h"
#include "ProjectileMonomerAttack.h"
#include "GameMap.h"
#include "ProjectileManager.h"
#include "ProjectileTrackMovingPart.h"
#include "ProjectileTypeOneShapePart.h"

int Projectile::m_count =   -1;

Projectile* Projectile::create( GameCharacterAttribute& att, ProjectileTypeEnum type, void* extraInfo, int ownerId )
{
    Projectile* pRet    =   nullptr;

    /**
    *	这里是根据子弹类型通过“组装”的方式来，主要是发现采用继承的方式会出现
    *   各种蛋疼的事情
    */
    switch (type)
    {
    case PROJECTILE_TYPE_GALAXO_BALL:               // 闪电球
        {
            // 单体攻击型
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            // @_@ 装配移动引擎
            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1800);

            // @_@ 装配显示部分
            pRet->setShapePart(new ProjectileTypeOneShapePart("xuejingling-texiao", "atk"));

            break;
        }

    case PROJECTILE_TYPE_ZEUS_FLY_HAMMER:                // 飞锤
        {
            // 单体攻击
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1000);

            pRet->setShapePart(new ProjectileTypeOneShapePart("zhousi-wuqi", "atk3", true));

            break;
        }

    case PROJECTILE_TYPE_PIG_FLY_KNIFE:                 // 野猪飞刀
        {
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1000);

            pRet->setShapePart(new ProjectileTypeOneShapePart("Pig-wuqi", "atk2", true));

            break;
        }

    case PROJECTILE_TYPE_NIU_FLY_SHIELD:                // 牛的飞盾
        {
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            
            pRet->setShapePart(new ProjectileTypeOneShapePart("Niu-wuqi", "atk2", true));

            break;
        }

    case PROJECTILE_TYPE_THEIF_FLY_DAGGER:              // 刺客的飞匕首
        {
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));

            pRet->setShapePart(new ProjectileTypeOneShapePart("Theif-wuqi", "atk2", true));

            break;
        }

    default:
        break;
    }

    if (pRet != nullptr)
    {
        pRet->m_projectileType  =   type;
        pRet->m_ownerId         =   ownerId;
        pRet->autorelease();

        // 注册到管理器中
        ProjectileMgr->addProjectile(pRet);

        // 添加到地图上
        GameMap::instance()->addProjectile(pRet);

        // 开始发射的表现
        pRet->getShapePart()->onLaunchStart();
    }
    return pRet;
}

Projectile::Projectile( GameCharacterAttribute& att )
{
    m_senderAtt     =   att;
    m_state         =   PROJECTILE_STATE_UPDATE | PROJECTILE_STATE_UPDATEMOVEMENT;
    m_projectileId  =   ++m_count;
}

Projectile::~Projectile()
{
    CC_SAFE_DELETE(m_movingPart);
    if (m_shapePart->getParent() != nullptr)
    {
        m_shapePart->removeFromParent();
    }
    CC_SAFE_DELETE(m_shapePart);
}

void Projectile::updateMovement( float dm )
{
    // 需要记录一下最近一次的位置
    m_lastPos   =   m_movingPart->getPosition();

    // 使用推进器更新当前的坐标
    m_movingPart->updateMovement(dm);
    m_shapePart->setPosition(m_movingPart->getPosition());

    // 判断方向
    if (m_movingPart->getVelocity().x < 0)
    {
        m_shapePart->setScaleX(-1);
    }
}
