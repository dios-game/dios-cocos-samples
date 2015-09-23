#ifndef __UI_VIEW_H__
#define __UI_VIEW_H__

#include "cocos2d.h"
#include "RefreshUIMsg.h"
#include "UIViewIdEnum.h"

using namespace cocos2d;
using namespace std;

/**
* ��Ҫ���ǿ��ǵ��Ժ���������ݷ����仯��ʱ��֪ͨ��ͼ��һ�㣬��������Ҫ�����е���ͼ������̳����࣬����
* ������ν���¼��ķ�ʽ�������ݷ����仯ʱ�������Ҫˢ�½��棬�͵��÷�����Ϣ����Ϣ���ͻ��ƻ��Զ�����Ϣ����
* ��ǰ����ʹ�õ���ͼ
*/
class UIView : public Layer
{
public:
    /**
    * ������ʱ����Ҫ����Ψһ�ı�־
    */
    UIView(UIViewIdEnum id);

    /**
    * �����յ��¼��Ļص����� 
    */
    virtual void onWee(RefreshUIMsg& msg);

    /**
    * ���ظ���ͼ�������¼� 
    */
    vector<RefreshUIEventEnum>& getWeeList();

    /**
    * ���ظ���ͼ��Ψһ��ʶ�� 
    */
    UIViewIdEnum getViewId();

    void onEnter() override;

    void onExit() override;

protected:
    /**
    * ���������Ҫ����ĳ��ˢ���¼��Ļ�����Ҫ���Ǹú��� 
    */
    virtual void setWeeList();

    vector<RefreshUIEventEnum>      m_weeList;                      // ����ͼ�������¼�
    UIViewIdEnum                    m_viewId;                       // ����Ψһ��ʶ��
};

#endif