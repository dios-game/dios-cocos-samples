#include "GameCharacterAttribute.h"

GameCharacterAttribute::GameCharacterAttribute(float hp, float attack, float defense)
{
    m_fullHp        =   hp;
    m_hp            =   hp;
    m_attack        =   attack;
    m_defense       =   defense;
    m_energy        =   0;
    m_maxEnergy     =   600;
}

GameCharacterAttribute& GameCharacterAttribute::sufferNormalAttack(GameCharacterAttribute& otherAttr)
{
    // @_@ 这里就给一个简单的计算公式
    m_hp    -=  otherAttr.getAttack();
    m_hp    =   m_hp < 0 ? 0 : m_hp;

    // @_@ 每次受伤也会增加120能量
    addEnergy(120);

    return *this;
}

void GameCharacterAttribute::addEnergy( int aEnergy )
{
    m_energy    +=  aEnergy;
    m_energy    =   m_energy > m_maxEnergy ? m_maxEnergy : m_energy;
}
