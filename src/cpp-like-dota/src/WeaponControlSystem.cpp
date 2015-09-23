#include "WeaponControlSystem.h"
#include "NormalCloseRangeWeapon.h"
#include "GameCharacter.h"
#include "GameTeam.h"
#include "EntityManager.h"
#include "WeaponChoiceAI.h"
#include "TimeTool.h"

WeaponControlSystem::WeaponControlSystem( GameCharacter* owner ):m_minAttackInterval(0)
{
    m_pOwner            =   owner;
    m_currentWeapon     =   nullptr;
    m_targetId          =   INVALID_GAME_ENTITY_ID;
    m_lastAttackTime    =   0;
    m_weaponChoiceAI    =   nullptr;
    m_readyToUseWeapon  =   nullptr;
    m_nextAttackTime    =   0;
}

WeaponControlSystem::~WeaponControlSystem()
{
    for (auto tmpIterator = m_allWeapons.begin(); tmpIterator != m_allWeapons.end(); tmpIterator++)
    {
        delete tmpIterator->second;
    }

    m_allWeapons.clear();

    // 武器选择AI部分
    CC_SAFE_DELETE(m_weaponChoiceAI);
}

void WeaponControlSystem::addWeapon(Weapon* aWeapon)
{
    // 添加到m_allWeapons中
    m_allWeapons.insert(WeaponMap::value_type(aWeapon->getWeaponType(), aWeapon));

    // @_@ 当前先这样写
    if (m_currentWeapon == nullptr)
    {
        m_currentWeapon     =   aWeapon;
    }
}

void WeaponControlSystem::takeWeaponAndAttack( GameCharacter* target )
{
    // 使用当前的武器攻击敌人
    if (satisfySysAttack() && m_currentWeapon->isInAttackRange(target) && m_currentWeapon->isReadyForNextAttack())
    {
        // 面向敌人
        if (m_pOwner->getMovingEntity().getPosition().x > target->getMovingEntity().getPosition().x)
        {
            m_pOwner->getShape()->faceToLeft();
        }
        else
        {
            m_pOwner->getShape()->faceToRight();
        }

        m_currentWeapon->attack(target);
        m_targetId  =   target->getId();

        m_weaponChoiceAI->attack();

        // 记录当前时间
        m_lastAttackTime    =   TimeTool::getSecondTime();
        // 允许下次攻击的时间
        m_nextAttackTime    =   m_lastAttackTime + m_minAttackInterval;
    }
}

bool WeaponControlSystem::isInAttackRange( GameCharacter* target )
{
    return m_currentWeapon->isInAttackRange(target);
}

bool WeaponControlSystem::canCharacterMove()
{
    // 只有当前武器不在攻击或者当前目标存在并且在攻击范围内
    auto tmpTarget  =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpTarget == nullptr || !isInAttackRange(tmpTarget) || !m_currentWeapon->isAttacking();
}

void WeaponControlSystem::update()
{
    // 现在把这部分更新当前选择武器的逻辑交给外部对象
    m_weaponChoiceAI->update();
}

bool WeaponControlSystem::changeWeapon( WeaponTypeEnum type, bool force )
{
    if (m_currentWeapon != nullptr && m_currentWeapon->getWeaponType() == type)
    {
        return false;
    }

    auto tmpIterator    =   m_allWeapons.find(type);
    if (tmpIterator == m_allWeapons.end())
    {
        return false;
    }
    else
    {
        if (force || !m_currentWeapon->isAttacking())
        {
            m_currentWeapon =   tmpIterator->second;
        }
        else if (m_currentWeapon->isAttacking())
        {
            m_readyToUseWeapon  =   tmpIterator->second;
        }
        return true;
    }
}

bool WeaponControlSystem::satisfySysAttack()
{
    return m_nextAttackTime < TimeTool::getSecondTime();
}

void WeaponControlSystem::setAttackTarget( int targetId )
{
    m_weaponChoiceAI->changeTarget();
}

Weapon* WeaponControlSystem::getWeaponByType( WeaponTypeEnum aType )
{
    auto tmpIterator    =   m_allWeapons.find(aType);
    if (tmpIterator != m_allWeapons.end())
    {
        return tmpIterator->second;
    }
    return nullptr;
}

void WeaponControlSystem::regularUpdate( float dm )
{
    m_weaponChoiceAI->regularUpdate(dm);

    // 如果有等待更换的武器，就更换掉
    if (m_readyToUseWeapon != nullptr && !m_currentWeapon->isAttacking())
    {
        m_currentWeapon     =   m_readyToUseWeapon;
        m_readyToUseWeapon  =   nullptr;
    }

    // 调用所有的武器的update
    for (auto tmpIterator = m_allWeapons.begin(); tmpIterator != m_allWeapons.end(); tmpIterator++)
    {
        tmpIterator->second->update(dm);
    }
}

void WeaponControlSystem::setWeaponChoiceAI( WeaponChoiceAI* aAI )
{
    if (m_weaponChoiceAI != nullptr)
    {
        CC_SAFE_DELETE(m_weaponChoiceAI);
    }
    m_weaponChoiceAI = aAI;
}
