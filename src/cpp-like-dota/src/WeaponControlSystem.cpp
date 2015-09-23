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

    // ����ѡ��AI����
    CC_SAFE_DELETE(m_weaponChoiceAI);
}

void WeaponControlSystem::addWeapon(Weapon* aWeapon)
{
    // ��ӵ�m_allWeapons��
    m_allWeapons.insert(WeaponMap::value_type(aWeapon->getWeaponType(), aWeapon));

    // @_@ ��ǰ������д
    if (m_currentWeapon == nullptr)
    {
        m_currentWeapon     =   aWeapon;
    }
}

void WeaponControlSystem::takeWeaponAndAttack( GameCharacter* target )
{
    // ʹ�õ�ǰ��������������
    if (satisfySysAttack() && m_currentWeapon->isInAttackRange(target) && m_currentWeapon->isReadyForNextAttack())
    {
        // �������
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

        // ��¼��ǰʱ��
        m_lastAttackTime    =   TimeTool::getSecondTime();
        // �����´ι�����ʱ��
        m_nextAttackTime    =   m_lastAttackTime + m_minAttackInterval;
    }
}

bool WeaponControlSystem::isInAttackRange( GameCharacter* target )
{
    return m_currentWeapon->isInAttackRange(target);
}

bool WeaponControlSystem::canCharacterMove()
{
    // ֻ�е�ǰ�������ڹ������ߵ�ǰĿ����ڲ����ڹ�����Χ��
    auto tmpTarget  =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    return tmpTarget == nullptr || !isInAttackRange(tmpTarget) || !m_currentWeapon->isAttacking();
}

void WeaponControlSystem::update()
{
    // ���ڰ��ⲿ�ָ��µ�ǰѡ���������߼������ⲿ����
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

    // ����еȴ��������������͸�����
    if (m_readyToUseWeapon != nullptr && !m_currentWeapon->isAttacking())
    {
        m_currentWeapon     =   m_readyToUseWeapon;
        m_readyToUseWeapon  =   nullptr;
    }

    // �������е�������update
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
