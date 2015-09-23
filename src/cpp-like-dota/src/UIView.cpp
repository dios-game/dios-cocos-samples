#include "UIView.h"
#include "UIViewManager.h"

UIView::UIView( UIViewIdEnum id )
{
    m_viewId    =   id;
}

void UIView::setWeeList()
{

}

vector<RefreshUIEventEnum>& UIView::getWeeList()
{
    return m_weeList;
}

UIViewIdEnum UIView::getViewId()
{
    return m_viewId;
}

void UIView::onEnter()
{
    setWeeList();
    Layer::onEnter();

    // ��Ҫ�ڹ�����ע��
    UIViewMgr->registerUIView(this);
}

void UIView::onExit()
{
    Layer::onExit();

    // ��Ҫ�ڹ������Ƴ�
    UIViewMgr->removeUIView(this);
}

void UIView::onWee( RefreshUIMsg& msg )
{

}