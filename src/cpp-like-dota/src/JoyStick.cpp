#include "JoyStick.h"

JoyStick::JoyStick( Sprite* pedestal, Sprite* ctrlPoint )
{
    m_pedestal  =   pedestal;
    m_ctrlPoint =   ctrlPoint;

    // ��Ҫ������Ϊê��
    this->setAnchorPoint(Vec2(0.5, 0.5));
    pedestal->setAnchorPoint(Vec2(0.5, 0.5));
    m_pedestalCenter    =   Vec2(m_pedestal->getContentSize().width / 2, m_pedestal->getContentSize().height / 2);
    ctrlPoint->setAnchorPoint(Vec2(0.5, 0.5));
    ctrlPoint->setPosition(m_pedestalCenter);
    pedestal->addChild(ctrlPoint);
    m_ctrlDirection.setPoint(0, 0);

    // ���Ӽ��������ͨ���϶����Ƶ����ı���Ʒ���
    auto tmpListener = EventListenerTouchOneByOne::create();
    tmpListener->onTouchBegan   =   CC_CALLBACK_2(JoyStick::onTouchBegan, this);
    tmpListener->onTouchMoved   =   CC_CALLBACK_2(JoyStick::onTouchMoved, this);
    tmpListener->onTouchEnded   =   CC_CALLBACK_2(JoyStick::onTouchEnded, this);
    ctrlPoint->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tmpListener, ctrlPoint);

    // ���Ƶ���������İ뾶
    m_pedestalRadius    =   pedestal->getContentSize().width / 2;
}

bool JoyStick::onTouchBegan( Touch* pTouch, Event* pEvent )
{
    // ���û��������ת����������ϵ��
    auto tmpTarget          =   static_cast<Sprite*>(pEvent->getCurrentTarget());
    Point tmpLocationInNode =   tmpTarget->convertToNodeSpace(pTouch->getLocation());
    
    Size tmpSize    =   tmpTarget->getContentSize();
    Rect rect       =   Rect(0, 0, tmpSize.width, tmpSize.height);

    if (rect.containsPoint(tmpLocationInNode))
    {
        // ��������Ƶ㣬��ʱӦ�ø�������
        followTouchPoint(pTouch);
        return true;
    }

    return false;
}

void JoyStick::onTouchMoved( Touch* pTouch, Event* pEvent )
{
    followTouchPoint(pTouch);
}

void JoyStick::onTouchEnded( Touch* pTouch, Event* pEvent )
{
    // �ָ�
    m_ctrlPoint->setPosition(m_pedestalCenter);
    m_ctrlDirection.setPoint(0, 0);
}

void JoyStick::followTouchPoint( Touch* pTouch )
{
    // ���ش������ڵ����ϵ�����
    Point tmpPoint  =   pTouch->getLocation();
    tmpPoint        =   m_pedestal->convertToNodeSpace(tmpPoint);
    
    // �������޶��ڵ����뾶��
    m_ctrlDirection =   tmpPoint - m_pedestalCenter;
    if (m_ctrlDirection.length() > m_pedestalRadius)
    {
        m_ctrlDirection.normalize();
        m_ctrlDirection *=  m_pedestalRadius;
    }

    // �����Ƶ��ƶ���ȥ
    m_ctrlPoint->setPosition(m_pedestalCenter + m_ctrlDirection);
}

JoyStick* JoyStick::create( Sprite* pedestal, Sprite* ctrlPoint )
{
    auto pRet   =   new JoyStick(pedestal, ctrlPoint);
    if (pRet != nullptr)
    {
        if (!pRet->init())
        {
            CC_SAFE_DELETE(pRet);
            pRet    =   nullptr;
        }
        else
        {
            pRet->autorelease();
        }
    }

    return pRet;
}

bool JoyStick::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    this->addChild(m_pedestal);
    return true;
}
