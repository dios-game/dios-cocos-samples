#ifndef __CIRCULAR_PROGRESS_H__
#define __CIRCULAR_PROGRESS_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

/**
*	 Բ�κ�ɫ���������������ֽ���Ϊ0��ʱ����0.5͸���ȵĺ�ɫԲ�Σ�����Ϊ1��ʱ��
*    ����ȫ��͸��Բ�������˼·���ǽ�Բ�Ķ�������ε�ƴ��
*/
class CircularProgress : public Node
{
public:
    static CircularProgress* create(int radius)
    {
        auto pRet   =   new CircularProgress(radius);
        if (pRet != nullptr)
        {
            pRet->autorelease();
        }
        return pRet;
    }

    /**
    *	���ñ���0~100�������л���
    */
    void setRatio(int ratio)
    {
        m_ratio =   ratio;
        float tmpDegree         =   3.6 * ratio;
        int   tmpEndPointIndex  =   tmpDegree / m_resolution;

        // ������ν��һ���Ż���ֻ��ȷʵ��Ҫ�ػ��ʱ����ػ�
        if (tmpEndPointIndex == m_lastSetRatioEndIndex)
        {
            return;
        }
        m_lastSetRatioEndIndex  =   tmpEndPointIndex;

        m_circule->clear();

        // ���ƺܶ��������
        for (; tmpEndPointIndex < m_pointNum - 1; tmpEndPointIndex++)
        {
            m_circule->drawTriangle(Vec2::ZERO, m_polyPoints[tmpEndPointIndex], 
                m_polyPoints[tmpEndPointIndex + 1], m_fileColor);
        }
    }

    ~CircularProgress()
    {
        delete[] m_polyPoints;
    }

protected:
    CircularProgress(int radius):m_resolution(10), m_pointNum(360 / m_resolution)
        , m_fileColor(0.0f, 0.0f, 0.0f, 0.5f)
    {
        m_circule       =   DrawNode::create();
        this->addChild(m_circule);

        m_polyPoints            =   new Vec2[m_pointNum];
        m_lastSetRatioEndIndex  =   0;

        // ����m_pointNum����������
        for (int tmpNum = 0; tmpNum < m_pointNum; tmpNum++)
        {
            m_polyPoints[tmpNum].setPoint(radius * sin(tmpNum * m_resolution * 3.14 / 180), 
                radius * cos(tmpNum * m_resolution * 3.14 / 180));
        }

        // ��ʼ��100
        // setRatio(100);
    }

    DrawNode*       m_circule;              // ���Ƶ�

    Vec2*           m_polyPoints;           // ����α߽��ϵĵ�
    int             m_ratio;                // ����0~100
    int             m_lastSetRatioEndIndex; // ���һ������Ratio��ʱ����ƵĶ��������±�

    const int       m_resolution;           // �ֱ���
    const int       m_pointNum;             // Բ�ϵĶ�������
    const Color4F   m_fileColor;            // δ��ɵ������ɫ
};

#endif