#include "stdafx.h"
#include "changeskin.h"

DUI_BEGIN_MESSAGE_MAP(SkinWnd, WindowImplBase)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_WINDOWINIT,OnPrepare)
DUI_END_MESSAGE_MAP()

SkinWnd::SkinWnd()
{
   
}

SkinWnd::~SkinWnd()
{
   
}


void SkinWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString SkinWnd::GetSkinFile()
{
	return _T("changeskin.xml");
}

CDuiString SkinWnd::GetSkinFolder()
{
	return  _T("skin\\");
}

UILIB_RESOURCETYPE SkinWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LRESULT SkinWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == SC_ZOOM) return 0; 
    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT SkinWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
     return __super::HandleMessage(uMsg, wParam, lParam);
}

void SkinWnd::InitWindow()
{
    SetWindowLong(*this, GWL_EXSTYLE, GetWindowLong(*this, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
}

void SkinWnd::OnPrepare(TNotifyUI& msg)
{
    //禁用窗口最大化效果
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    styleValue &= ~WS_MAXIMIZEBOX;
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    DWORD dwExStyle = GetWindowLong(*this, GWL_EXSTYLE);
    dwExStyle |= WS_EX_TOOLWINDOW;
    ::SetWindowLong(*this, GWL_EXSTYLE, dwExStyle);
}

void SkinWnd::OnClick( TNotifyUI &msg )
{
   CDuiString ControlName = msg.pSender->GetName();
   HWND hWnd = FindWindow(NULL, _T("Duilib界面框架"));
   if (hWnd == NULL) {
       return;
   }
   if (ControlName == BTN_BGGREEN_IN_SKINWND) {
       ::PostMessage(hWnd, WM_CHANGESKIN_MESSAGE, 0, GREEN);
   } else if (ControlName == BTN_BGBLUE_IN_SKINWND) {      
       ::PostMessage(hWnd, WM_CHANGESKIN_MESSAGE, 0, BLUE);
   }else if (ControlName == BTN_BGPINK_IN_SKINWND) {      
       ::PostMessage(hWnd, WM_CHANGESKIN_MESSAGE, 0, PINK);
   }
   //Close();
}

void SkinWnd::SetMyWindowPos(int x, int y)
{
    ::SetWindowPos(m_hWnd, NULL, x-50, y+30, -1, -1, SWP_NOSIZE | SWP_NOACTIVATE);
}
