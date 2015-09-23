#ifndef __UI_VIEW_MANAGER_H__
#define __UI_VIEW_MANAGER_H__

#include <map>
#include "UIViewIdEnum.h"
#include "RefreshUIMsg.h"

using namespace std;

class UIView;

/**
* ���ڹ�������ȫ�ֵ���
*/
class UIViewManager
{
public:
    typedef map<UIViewIdEnum, UIView*> UIViewMap;

    static UIViewManager* instance();

    /**
    * ע�� 
    */
    void registerUIView(UIView* view);

    /**
    *  �Ƴ�
    */
    void removeUIView(UIView* view);

    /**
    *  ����һ����Ϣ��ˢ����ص���ͼ
    */
    void refreshView(RefreshUIMsg& msg);

private:
    UIViewManager();
    ~UIViewManager();

    UIViewMap  m_uiViewMap;                    // ���浱ǰ���ڵ����д���

    static UIViewManager*       m_instance;
};

#define UIViewMgr   UIViewManager::instance()

#endif