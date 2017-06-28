#include "page3.h"

CPageUI3::CPageUI3()
{
    paint_manager_ = NULL;
}

CPageUI3::~CPageUI3()
{
    
}

LRESULT CPageUI3::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    return 0;
}

BOOL CPageUI3::Handler(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK) {
        return OnClick(msg);
    } else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED) {
        return OnSelectChanged(msg);
    } else if (msg.sType == DUI_MSGTYPE_WINDOWINIT) {
        return OnWindowInit();
    }

    return FALSE;
}

void CPageUI3::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
    paint_manager_ = pPaintMgr;
}
BOOL CPageUI3::OnWindowInit() 
{
    pBrowser = static_cast<CWebBrowserUI*>(paint_manager_->FindControl(CTROL_WEBBROWSER_IN_PAGE3));
    return FALSE;
}
BOOL CPageUI3::OnClick(TNotifyUI& msg)
{
    CDuiString ControlName = msg.pSender->GetName();
    if (ControlName == BTN_OPEN_BROWSER_IN_PAGE3) {
        OpenWebBrowser();
        return TRUE;
    } else if (ControlName == BTN_GOBACK_IN_PAGE3) {
        pBrowser->GoBack();
        return TRUE;
    } else if (ControlName == BTN_GOFOWARD_IN_PAGE3) {
        pBrowser->GoForward();
        return TRUE;
    }
    return FALSE;
}

BOOL CPageUI3::OnSelectChanged(TNotifyUI& msg)
{
    CTabLayoutUI* pOption = static_cast<CTabLayoutUI*>(
        paint_manager_->FindControl(TABCONTROL_IN_PAGE3));
    if (!pOption) {
        return FALSE;
    }
    CDuiString OptionName = msg.pSender->GetName();
    if (OptionName == LEFTOPTION1_IN_PAGE3) {
        pOption->SelectItem(LEFTTAB_OPTION0);       
        return TRUE;
    } else if (OptionName == LEFTOPTION2_IN_PAGE3) {
        pOption->SelectItem(LEFTTAB_OPTION1);
        return TRUE;
    } else if (OptionName == LEFTOPTION3_IN_PAGE3) {
        pOption->SelectItem(LEFTTAB_OPTION2);
        return TRUE;
    } 
    return FALSE;
}

void CPageUI3::OpenWebBrowser()
{
    //pBrowser->SetHomePage(_T("http://www.hao123.com"));
    //pBrowser->NavigateHomePage();
    LPCTSTR Url = paint_manager_->FindControl(EDIT_WEB_BROWSER_IN_PAGE3)->GetText();
    USES_CONVERSION;
    pBrowser->NavigateUrl(Url);
    pBrowser->SetWebBrowserEventHandler(this);
    //pBrowser->Refresh();
    //pBrowser->Release();
}
