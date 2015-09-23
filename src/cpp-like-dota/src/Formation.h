#ifndef __FORMATION_H__
#define __FORMATION_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* С�ӵ��ƶ����ͣ��ڲ��Ӽ����ƶ���ʱ��Ҫ����������ͣ������������
* ������ߵ�
* 6      3     0 
* 7      4     1
* 8      5     2
* �����ұߵ�
* 0      3     6
* 1      4     7
* 2      5     8
*/
class Formation
{
public:
    /**
    * ������ʽ 
    */
    enum FormationTypeEnum
    {
        FORMATION_TYPE_RIGHT,               // �����ұߵ�����
        FORMATION_TYPE_LEFT,                // ������ߵ�����
    };

    Formation(FormationTypeEnum type = FORMATION_TYPE_RIGHT):m_xPosInterval(150), m_yPosInterval(115)
    {
        m_formationType =   type;
    }

    /**
    * �������е�ÿ��һ����ɫ����һ����ţ����ݱ�ţ��������ƶ���ʱ��ᾡ������ָ����λ����
    * ������Ǹ��������еı�ŷ��ض�Ӧ������
    */
    Vec2 getPositionByPosId(int posId)
    {
        float   tmpxInterval    =   0;
        switch (m_formationType)
        {
        case FORMATION_TYPE_LEFT:
            tmpxInterval    =   m_xPosInterval;
            break;

        case FORMATION_TYPE_RIGHT:
            tmpxInterval    =   -m_xPosInterval;
            break;
        }

        return m_formationAnchor + Vec2(posId / 3 * tmpxInterval, - posId % 3 * m_yPosInterval);
    }

    CC_SYNTHESIZE(Vec2, m_formationAnchor, FormationAnchor);                // ���͵�ê�㣬��ʵ����0��λ
    CC_SYNTHESIZE(FormationTypeEnum, m_formationType, FormationType);       // ������ʽ

private:
    /**
    * �����е�һЩ���� 
    */
    const float             m_xPosInterval;                 // x�����ϵ�ƫ��
    const float             m_yPosInterval;                 // y�����ϵ�ƫ��
};

#endif