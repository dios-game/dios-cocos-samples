#include "MessageDispatcher.h"
#include "EntityManager.h"

MessageDispatcher* MessageDispatcher::_instance = nullptr;

/**
	��ĳ���˷���һ����Ϣ
*/
void MessageDispatcher::disCharge(BaseGameEntity* pReceiver, Telegram& msg)
{
    if (pReceiver == nullptr)
    {
        // ��ʱ�������Ѿ���������
        return;
    }

    pReceiver->handleMessage(msg);
}

MessageDispatcher* MessageDispatcher::instance()
{
    if (_instance == nullptr)
    {
        _instance   =   new MessageDispatcher();
    }

    return _instance;
}

void MessageDispatcher::dispatchMessage(Telegram& msg)
{
    // TODO �Ժ���ܻ�����ʱ�����
    BaseGameEntity* tmpReceiver =   EntityMgr->getEntityFromID(msg.receiverId);
    disCharge(tmpReceiver, msg);
}