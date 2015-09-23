#ifndef __MESSAGE_DISPATCHER_H__
#define __MESSAGE_DISPATCHER_H__

#include "Telegram.h"
#include "BaseGameEntity.h"

/**
	������Ϣ���͵ģ�ȫ�ֵ���
*/
class MessageDispatcher
{
protected:
    MessageDispatcher(){}
    ~MessageDispatcher(){}

    void disCharge(BaseGameEntity* pReceiver, Telegram& msg);

    static MessageDispatcher* _instance;

public:
    static MessageDispatcher* instance();

    /**
    	������Ϣ
    */
    void dispatchMessage(Telegram& msg);
};

#define Dispatch MessageDispatcher::instance()

#endif