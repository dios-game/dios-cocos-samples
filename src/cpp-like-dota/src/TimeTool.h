#ifndef __TIME_TOOL_H__
#define __TIME_TOOL_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* ��Ҫ����һЩʱ�乤��
* @_@ ��Ҫ�Ƿ��ֹ���ʱ��Ļ�ȡ�ڲ�ͬƽ̨�᲻ͬ������ʱ�䲿�ֲ��ܹ�����Ϸ�Ľ���
*     һ������������õ��Ǹ���֡������ۼ�ʱ�䣬�Ժ���֡�仯��ʱ�������ֽſ�
*     ��Ӱ�����Լ����߼�
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