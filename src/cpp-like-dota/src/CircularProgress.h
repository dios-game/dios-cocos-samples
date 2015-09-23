#ifndef __CIRCULAR_PROGRESS_H__
#define __CIRCULAR_PROGRESS_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

/**
*	 圆形黑色进度条，就是那种进度为0的时候是0.5透明度的黑色圆形，进度为1的时候
*    是完全的透明圆。这里的思路就是将圆的多个三角形的拼接
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
    *	设置比例0~100，并进行绘制
    */
    void setRatio(int ratio)
    {
        m_ratio =   ratio;
        float tmpDegree         =   3.6 * ratio;
        int   tmpEndPointIndex  =   tmpDegree / m_resolution;

        // 这里所谓做一下优化，只有确实需要重绘的时候才重绘
        if (tmpEndPointIndex == m_lastSetRatioEndIndex)
        {
            return;
        }
        m_lastSetRatioEndIndex  =   tmpEndPointIndex;

        m_circule->clear();

        // 绘制很多个三角形
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

        // 计算m_pointNum个顶点坐标
        for (int tmpNum = 0; tmpNum < m_pointNum; tmpNum++)
        {
            m_polyPoints[tmpNum].setPoint(radius * sin(tmpNum * m_resolution * 3.14 / 180), 
                radius * cos(tmpNum * m_resolution * 3.14 / 180));
        }

        // 初始是100
        // setRatio(100);
    }

    DrawNode*       m_circule;              // 绘制的

    Vec2*           m_polyPoints;           // 多边形边界上的点
    int             m_ratio;                // 比例0~100
    int             m_lastSetRatioEndIndex; // 最近一次设置Ratio的时候绘制的顶点最后的下标

    const int       m_resolution;           // 分辨率
    const int       m_pointNum;             // 圆上的定点数量
    const Color4F   m_fileColor;            // 未完成的填充颜色
};

#endif