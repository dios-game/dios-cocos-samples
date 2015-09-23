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
    // @_@ ����͸�һ���򵥵ļ��㹫ʽ
    m_hp    -=  otherAttr.getAttack();
    m_hp    =   m_hp < 0 ? 0 : m_hp;

    // @_@ ÿ������Ҳ������120����
    addEnergy(120);

    return *this;
}

void GameCharacterAttribute::addEnergy( int aEnergy )
{
    m_energy    +=  aEnergy;
    m_energy    =   m_energy > m_maxEnergy ? m_maxEnergy : m_energy;
}
