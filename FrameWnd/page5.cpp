#include "page5.h"

CPageUI5::CPageUI5()
{
    paint_manager_ = NULL;
}

CPageUI5::~CPageUI5()
{

}

LRESULT CPageUI5::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    return 0;
}

BOOL CPageUI5::Handler(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK) {
        return OnClick(msg);
    } else if (msg.sType == DUI_MSGTYPE_WINDOWINIT) {
        return OnInitWindow();
    }

    return FALSE;
}

void CPageUI5::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
    paint_manager_ = pPaintMgr;
    paint_manager_->AddMessageFilter(this);
}

BOOL CPageUI5::OnClick(TNotifyUI& msg)
{
    CDuiString ControlName = msg.pSender->GetName();
    if (ControlName == _T("addlistiteminpage5")) {
        mylist_.AddItemList();
    }
    return FALSE;
}

BOOL CPageUI5::OnInitWindow()
{
    
    return FALSE;
}
