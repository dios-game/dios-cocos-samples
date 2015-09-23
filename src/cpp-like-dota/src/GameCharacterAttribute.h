#ifndef __GAME_CHARACTER_ATTRIBUTE_H__
#define __GAME_CHARACTER_ATTRIBUTE_H__

#include "cocos2d.h"

/**
	 ��װ�˹��ڽ�ɫ�����Լ���������صĸ��ּ��㣬��Ҫ�ǿ��ǵ��Ժ���㷽ʽ���ܻᾭ���仯�����о���
     ��Щ���ܿ��ܻ�ͬʱ�޸Ķ������
*/
class GameCharacterAttribute
{
public:
    /**
    	 ��ǰ��ʱһ������ֻ��Ѫ��������ֵ������ֵ�Լ��ƶ��ٶ�
    */
    GameCharacterAttribute(float hp = 100, float attack = 10, float defense = 20);

    /**
    	 ���ܱ��˵���ͨ����������֮���԰ѶԷ����������Զ����룬����Ϊ���ǵ�������ͨ������ɱ�˼���
         ���ܻ����������߰���������йأ����ظý�ɫ��������ĵ�ǰ����
    */
    GameCharacterAttribute& sufferNormalAttack(GameCharacterAttribute& otherAttr);

    /**
    *	 �����������и�������ޣ�
    */
    void addEnergy(int aEnergy);

    CC_SYNTHESIZE(float, m_fullHp, FullHp);                             // ��Ѫ��
    CC_SYNTHESIZE(float, m_hp, Hp);                                     // Ѫ��
    CC_SYNTHESIZE(float, m_energy, Energy);                             // �������������ƹ����߼���
    CC_SYNTHESIZE(float, m_attack, Attack);                             // ����ֵ
    CC_SYNTHESIZE(float, m_defense, Defense);                           // ����ֵ

    int   m_maxEnergy;                                                  // �������
};

#endif