#ifndef __TELEGRAM_H__
#define __TELEGRAM_H__

#include "cocos2d.h"
#include "GameCharacterAttribute.h"

using namespace cocos2d;

/**
	 ��Ϣ����
*/
enum TelegramEnum
{
    /**
    	 ��ҵ�ָʾ��ָ�����������������Լ�����ָ��
    */
    TELEGRAM_ENUM_USER_MOVE_RIGHT,
    TELEGRAM_ENUM_USER_MOVE_LEFT,
    TELEGRAM_ENUM_USER_IDLE,
    TELEGRAM_ENUM_USER_CHANGE_TARGET,

    /**
    	 ��Ϸ��ɫ֮�����Ϣ
    */
    TELEGRAM_ENUM_NORMAL_ATTACK,                     // ��ͨ����
    TELEGRAM_ENUM_BE_KILLED,                         // ��ɱ�����򹥻��߷�����Ϣ��֪ͨ���Լ�����

    /**
    	 ����������еĽ�ɫ֮�����Ϣ
    */
    TELEGRAM_ENUM_TEAM_COLLECTIVE_FORWARD,          // ���鼯��ǰ��
    TELEGRAM_ENUM_TEAM_CANCEL_COLLECTIVE_FORWARD,   // ȡ�����鼯��ǰ��
    TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET,     // ����ָ����ɫ����ĳ��ָ���Ľ�ɫ
};

/**
	 ��Ϣ�ṹ�������ϵͳ���û���ʵ�塢ʵ����ʵ��Ľ�������ͨ����Ϣ��������ֱ�ӵĺ������ã�����Ϣ��
     ��һ��ͨ�õ���Ϣ����Ȼ�����Զ�����Ϣ�ṹ�����Ǳ��������̳�
*/
class Telegram : public Ref
{
protected:
    Telegram() 
    {
        senderId        =   0;
        receiverId      =   0;
        dispatchTime    =   0;
    };
    virtual ~Telegram() {};

public:
    int             senderId;               // ������id
    int             receiverId;             // ������id
    TelegramEnum    type;                   // ��Ϣ����
    float           dispatchTime;           // ����ʱ��
    void*           extraInfo;              // �������Ϣ

    static Telegram *create(int senderId, int receiverId, TelegramEnum type, float dispatchTime = 0, void* extraInfo = nullptr)
    {
        Telegram *pRet  =   new Telegram();
        if (pRet != nullptr)
        {
            pRet->senderId      =   senderId;
            pRet->receiverId    =   receiverId;
            pRet->type          =   type;
            pRet->dispatchTime  =   dispatchTime;
            pRet->extraInfo     =   extraInfo;

            pRet->autorelease();
        }

        return pRet;
    }
};

/**
	 ��ͨ����
*/
class TelegramNormalAttack : public Telegram
{
public:
    GameCharacterAttribute  senderAtt;          // �����ߵ����ԣ���������Ŀ���˺���

    static TelegramNormalAttack* create(int senderId, int receiverId, GameCharacterAttribute& senderAtt)
    {
        TelegramNormalAttack* pRet = new TelegramNormalAttack();
        if (pRet)
        {
            pRet->senderId      =   senderId;
            pRet->receiverId    =   receiverId;
            pRet->senderAtt     =   senderAtt;
            pRet->autorelease();
        }

        return pRet;
    }

protected:
    TelegramNormalAttack()
    {
        type    =   TELEGRAM_ENUM_NORMAL_ATTACK;
    }

};

/**
*	 �������ɫָ������Ŀ��
*/
class TelegramAttackSpecifiedTarget : public Telegram
{
public:
    int             targetTeamId;             // Ŀ����������id
    int             targetId;                 // Ŀ��id

    static TelegramAttackSpecifiedTarget* create(int aReceiveId, int aTargetId, int aTargetTeamId)
    {
        TelegramAttackSpecifiedTarget* pRet =   new TelegramAttackSpecifiedTarget();
        if (pRet != nullptr)
        {
            pRet->receiverId    =   aReceiveId;
            pRet->targetId      =   aTargetId;
            pRet->targetTeamId  =   aTargetTeamId;
        }
        return pRet;
    }

protected:
    TelegramAttackSpecifiedTarget()
    {
        type    =   TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET;
    }
};

#endif