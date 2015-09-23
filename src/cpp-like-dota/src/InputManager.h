#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

#define INPUTMANAGER_SCHEDULE_KEY   "INPUTMANAGER_SCHEDULE_KEY"

/**
	 �������Ĵ�����Ϸ�߼������ǲ���Ҫ֪������������豸�ģ������κ����뷽ʽ��
     ֻ��Ҫʵ�����½ӿھͿ��Դ��ⲿ�����豸��ȡ�������Ϸ�߼�
*/
class InputManagerDelegate
{
public:
    /**
    	 �������������ƶ��Ĳ���
         @_@    ����ֻ��Ҫ�����������һ�������
    */
    virtual void moveToLeft()   =   0;      // ����
    virtual void moveToRight()  =   0;      // ����
    virtual void idle()         =   0;      // ʲô��������
    virtual void changeTarget() =   0;      // ѡ��Ŀ��

    /**
    *	����������ɫ�ͷż��ܵ� 
    */
    virtual void useSkill1()    =   0;      // ���ʹ�õ�һ������
    virtual void useSkill2()    =   0;      // ���ʹ�õڶ�������
};

/**
	 ������������豸�Ļ���
*/
class InputManager
{
public:
    virtual bool init() = 0;
    CC_SYNTHESIZE(InputManagerDelegate *, _delegate, Delegate);
};

#endif