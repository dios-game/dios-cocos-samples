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
    *	�����Ǹ����ӵ�����ͨ������װ���ķ�ʽ������Ҫ�Ƿ��ֲ��ü̳еķ�ʽ�����
    *   ���ֵ��۵�����
    */
    switch (type)
    {
    case PROJECTILE_TYPE_GALAXO_BALL:               // ������
        {
            // ���幥����
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            // @_@ װ���ƶ�����
            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1800);

            // @_@ װ����ʾ����
            pRet->setShapePart(new ProjectileTypeOneShapePart("xuejingling-texiao", "atk"));

            break;
        }

    case PROJECTILE_TYPE_ZEUS_FLY_HAMMER:                // �ɴ�
        {
            // ���幥��
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1000);

            pRet->setShapePart(new ProjectileTypeOneShapePart("zhousi-wuqi", "atk3", true));

            break;
        }

    case PROJECTILE_TYPE_PIG_FLY_KNIFE:                 // Ұ��ɵ�
        {
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            pRet->getMovingPart()->setRate(1000);

            pRet->setShapePart(new ProjectileTypeOneShapePart("Pig-wuqi", "atk2", true));

            break;
        }

    case PROJECTILE_TYPE_NIU_FLY_SHIELD:                // ţ�ķɶ�
        {
            pRet    =   new ProjectileMonomerAttack(att, (int)extraInfo);

            pRet->setMovingPart(new ProjectileTrackMovingPart((int)extraInfo));
            
            pRet->setShapePart(new ProjectileTypeOneShapePart("Niu-wuqi", "atk2", true));

            break;
        }

    case PROJECTILE_TYPE_THEIF_FLY_DAGGER:              // �̿͵ķ�ذ��
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

        // ע�ᵽ��������
        ProjectileMgr->addProjectile(pRet);

        // ��ӵ���ͼ��
        GameMap::instance()->addProjectile(pRet);

        // ��ʼ����ı���
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
    // ��Ҫ��¼һ�����һ�ε�λ��
    m_lastPos   =   m_movingPart->getPosition();

    // ʹ���ƽ������µ�ǰ������
    m_movingPart->updateMovement(dm);
    m_shapePart->setPosition(m_movingPart->getPosition());

    // �жϷ���
    if (m_movingPart->getVelocity().x < 0)
    {
        m_shapePart->setScaleX(-1);
    }
}
