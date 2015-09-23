#ifndef __TIME_TOOL_H__
#define __TIME_TOOL_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* 主要就是一些时间工具
* @_@ 主要是发现关于时间的获取在不同平台会不同，而且时间部分不能够和游戏的节奏
*     一起，所以这里采用的是根据帧数间隔累加时间，以后在帧变化的时间做点手脚可
*     以影响我自己的逻辑
*/
class TimeTool
{
public:
    static void update(float dm)
    {
        m_timeCount +=  dm;
    }

    static float getSecondTime()
    {
        return m_timeCount;
    }

private:
    static float m_timeCount;
};

#endif