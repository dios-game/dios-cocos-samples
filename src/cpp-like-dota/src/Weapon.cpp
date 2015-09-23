#include "Weapon.h"
#include "GameCharacter.h"

Weapon::Weapon( GameCharacter* owner, WeaponTypeEnum type )
{
    m_pOwner        =   owner;
    m_weaponType    =   type;
}

Weapon::~Weapon()
{

}

WeaponTypeEnum Weapon::getWeaponType()
{
    return m_weaponType;
}

void Weapon::cancelCurrentAttack()
{
    m_pOwner->getShape()->freezeAnimation();
    m_pOwner->getShape()->unfreezeAnimation(false);
}
