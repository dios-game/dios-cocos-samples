#include "ProjectileManager.h"

ProjectileManager* ProjectileManager::m_instance = nullptr;

ProjectileManager* ProjectileManager::instance()
{
    if (m_instance == nullptr)
    {
        m_instance  =   new ProjectileManager();
    }

    return m_instance;
}

void ProjectileManager::addProjectile( Projectile* aProjectile )
{
    aProjectile->retain();
    m_projectilesMap.insert(
        ProjectileMap::value_type(aProjectile->getProjectileId(), aProjectile));
}

void ProjectileManager::update( float dm )
{
    removeAllCanRemoveProjectile();

    for (auto tmpIterator = m_projectilesMap.begin(); 
        tmpIterator != m_projectilesMap.end(); tmpIterator++)
    {
        auto tmpProjectile = tmpIterator->second;
        if (tmpProjectile->canUpdateMovement())
        {
            tmpProjectile->updateMovement(dm);
        }
        if (tmpProjectile->canUpdate())
        {
            tmpProjectile->update(dm);
        }
    }

    removeAllCanRemoveProjectile();
}

void ProjectileManager::removeAllCanRemoveProjectile()
{
    for (auto tmpIterator = m_projectilesMap.begin(); 
        tmpIterator != m_projectilesMap.end();)
    {
        // 移除被标记为可以移除的以及超出屏幕的
        if (tmpIterator->second->canRemove() || isOutWindow(tmpIterator->second))
        {
            CC_SAFE_RELEASE_NULL(tmpIterator->second);
            tmpIterator = m_projectilesMap.erase(tmpIterator);
        }
        else
        {
            tmpIterator++;
        }
    }
}

bool ProjectileManager::isOutWindow(Projectile* aPorjectile)
{
    // 先转换到世界坐标系中
    auto tmpParent  =   aPorjectile->getShapePart()->getParent();
    auto tmpPoint   =   tmpParent->convertToWorldSpace(aPorjectile->getMovingPart()->getPosition());
    return !Rect(0, 0, 1280, 800).containsPoint(tmpPoint);
}
