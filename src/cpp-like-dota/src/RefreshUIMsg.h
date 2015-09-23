#ifndef __REFRESH_UI_MSG_H__
#define __REFRESH_UI_MSG_H__

#include "RefreshUIEventEnum.h"

/**
* ����ˢ����ͼ����Ϣ�ṹ 
*/
class RefreshUIMsg
{
public:
    RefreshUIMsg(RefreshUIEventEnum eventType, void* extraInfo = nullptr)
    {
        this->eventType =   eventType;
        this->extraInfo =   extraInfo;
    }

    RefreshUIEventEnum  eventType;                      // ��Ϣ���¼�����
    void*               extraInfo;                      // ������¼�����Ӧ��UIӦ��Ҫ֪����ν���������������
};

#endif