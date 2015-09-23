#ifndef __JOY_STICK_H__
#define __JOY_STICK_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* ��Ϸ�ֱ�����ʵ��������Sprite��һ����Ϊ������һ����Ϊ����ĸ�������ָ�ƶ��ģ��ⲿ����ͨ���ӿڻ�ȡ��ǰ�ĽǶ�
*/
class JoyStick : public Sprite
{
public:
    /**
    * �ֱ�����Ϊ�����Ϳ��Ƶ� 
    */
    JoyStick(Sprite* pedestal, Sprite* ctrlPoint);

    bool init() override;

    CC_SYNTHESIZE_READONLY(Vec2, m_ctrlDirection, CtrlDirection);                   // ��ǰ���Ʒ���

    static JoyStick* create(Sprite* pedestal, Sprite* ctrlPoint);

protected:
    /**
    * �������ڿ��Ƶ�����Ĳ���
    */
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void onTouchMoved(Touch* pTouch, Event* pEvent);
    void onTouchEnded(Touch* pTouch, Event* pEvent);

    /**
    * ���Ƶ�������� 
    */
    void followTouchPoint(Touch* pTouch);

    float   m_pedestalRadius;                       // �����İ뾶�����Ƶ��������Χ��
    Vec2    m_pedestalCenter;                       // ����������
    
    Sprite* m_pedestal;
    Sprite* m_ctrlPoint;
};

#endif