#include "page6.h"
HWND hwnd;
CPageUI6::CPageUI6()
{
    paint_manager_ = NULL;
}

CPageUI6::~CPageUI6()
{

}

LRESULT CPageUI6::OnTitleChanged(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    m_Title = (LPCTSTR)wParam;
    TCHAR szText[MAX_PATH] = {0};
    _stprintf(szText, _T("网站标题：%s     网站网址:%s"),m_Title.c_str(),m_URL.c_str());
    m_pLblStatusBar->SetText(szText);
    return 0 ;
}

LRESULT CPageUI6::OnURLChanged(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    m_URL = (LPCTSTR)wParam;
    TCHAR szText[MAX_PATH] = {0};
    _stprintf(szText, _T("网站标题：%s     网站网址:%s"),m_Title.c_str(),m_URL.c_str());
    m_pLblStatusBar->SetText(szText);
    return 0 ;
}

LRESULT CPageUI6::OnJsNotify(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    MessageBox(NULL, (LPCTSTR)wParam, (LPCTSTR)lParam, 0);
    return 0;
}

LRESULT CPageUI6::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    HWND m_hwnd = paint_manager_->GetPaintWindow();
    switch (uMsg)
    {
    case WM_USER_TITLE_CHANGE:
        {
            bHandled = TRUE;
            return OnTitleChanged(m_hwnd, wParam, lParam);
        }
    case WM_USER_URL_CHANGE:
        {
            bHandled = TRUE;
            return OnURLChanged(m_hwnd, wParam, lParam);
        }

    case WM_USER_JS_NOTIFY:
        {
            bHandled = TRUE;
            return OnJsNotify(m_hwnd, wParam, lParam);
        }     
    }
    return 0;
}

BOOL CPageUI6::Handler(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK) {
        return OnClick(msg);
    } else if (msg.sType == DUI_MSGTYPE_WINDOWINIT) {
        return OnInitWindow();
    } else if (msg.sType == _T("return")) {
        if (msg.pSender->GetName() == _T("urlEdit")) {
            if (m_pURLEdit)
                m_pWke->SetURL(m_pURLEdit->GetText().GetData());
        }
        return FALSE;
    }

    return FALSE;
}

void CPageUI6::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
    paint_manager_ = pPaintMgr;
    paint_manager_->AddMessageFilter(this);
}

BOOL CPageUI6::OnClick(TNotifyUI& msg)
{
    if( msg.pSender->GetName() == _T("btnBack") ) 
    {
        m_pWke->GoBack();
    }
    if( msg.pSender->GetName() == _T("btnforward") ) 
    {
        m_pWke->GoForward();
    }
    if( msg.pSender->GetName() == _T("btnGo") ) 
    {
        if (m_pURLEdit)
            m_pWke->SetURL(m_pURLEdit->GetText().GetData());
    }
    if( msg.pSender->GetName() == _T("btnRefresh") ) 
    {
        wstring strRet = m_pWke->RunJS(m_pURLEdit->GetText().GetData());
        MessageBox(NULL, strRet.c_str(), _T(""), 0);
    }

    return FALSE;
}

BOOL CPageUI6::OnInitWindow()
{
    hwnd = paint_manager_->GetPaintWindow();
    m_pURLEdit = static_cast<CEditUI*>(paint_manager_->FindControl(_T("urlEdit")));
    m_pLblStatusBar = static_cast<CLabelUI*>(paint_manager_->FindControl(_T("statusbar")));
    InitWkeBrowser();
    return FALSE;
}

jsValue JS_CALL js_msgBox(jsExecState es)
{
    const wchar_t* text = jsToStringW(es, jsArg(es, 0));
    const wchar_t* title = jsToStringW(es, jsArg(es, 1));

    //HWND hwnd = CFrameWnd::MainWnd()->GetHWND();
    if (::IsWindow(hwnd) )
    {
        ::PostMessage(hwnd, WM_USER_JS_NOTIFY, (WPARAM)text, (LPARAM)title);
    }
    //	MessageBox(hwnd, text, title, 0);

    return jsUndefined();
}

void onURLChanged(const struct _wkeClientHandler* clientHandler, const wkeString URL)
{
    //	MessageBox(hwnd, wkeToStringW(URL), _T(""), 0);
    //HWND hwnd = CFrameWnd::MainWnd()->GetHWND();
    if (::IsWindow(hwnd) )
    {
        ::PostMessage(hwnd, WM_USER_URL_CHANGE, (WPARAM)wkeToStringW(URL), (LPARAM)0);
    }
}

void onTitleChanged(const struct _wkeClientHandler* clientHandler, const wkeString title)
{
    //	MessageBox(hwnd, wkeToStringW(title), _T(""), 0);
    //HWND hwnd = CFrameWnd::MainWnd()->GetHWND();
    if (::IsWindow(hwnd) )
    {
        ::PostMessage(hwnd, WM_USER_TITLE_CHANGE, (WPARAM)wkeToStringW(title), (LPARAM)0);
    }
}

void CPageUI6::InitWkeBrowser()
{
    m_pWke = static_cast<CWkeWebkitUI*>(paint_manager_->FindControl(_T("wke")));
    if (m_pWke)
    {
        jsBindFunction("MyAlert", js_msgBox, 2);//这里绑定js函数，让js主动调用c++函数
        static wkeClientHandler hander;        //网页标题改变和URL改变的回调
        hander.onTitleChanged = onTitleChanged;
        hander.onURLChanged = onURLChanged;
        m_pWke->SetClientHandler(&hander);
        m_pWke->SetFile(_T("Html/index.html")/*msg.pSender->GetText().GetData()*/);
        //m_pWke->SetURL(L"http://www.baidu.com/"); 
    }
}