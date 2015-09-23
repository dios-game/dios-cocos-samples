#ifndef __STATE_H__
#define __STATE_H__

#include "cocos2d.h"
#include "Telegram.h"

/**
	 ʵ��״̬
*/
template <class entity_type>
class State : public cocos2d::Ref
{
public:
    virtual ~State(){};

    /**
    	 �ս����״̬��ʱ��
    */
    virtual void onEnter(entity_type *owner)            =   0;

    /**
    	 ÿһ֡�ĸ���
    */
    virtual void update(entity_type *owner, float dm)   =   0;
    
    /**
    	 �뿪��״̬��ʱ��Ļص�
    */
    virtual void onExit(entity_type *owner)             =   0;
    
    /**
    	 ����������Ϣ�ģ�Ĭ�ϲ�������Ϣ
    */
    virtual bool onMessage(entity_type *owner, Telegram& msg) { return false; }
    
    virtual bool init(){return true;}
};

#endif