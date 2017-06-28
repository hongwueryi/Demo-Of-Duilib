#include "mainframe.h"
#include "resource.h"
#include "datadefine.h"
#include "ControlEx.h"
#include "changeskin.h"
#include "UIMenu.h"

#define TIMER_ID1   WM_USER+1000
#define TIMER_ID2   WM_USER+1001

namespace ATL {
#include <atltypes.h> 
}
#include <atlimage.h> 





//#include "controls_ex.h"

DUI_BEGIN_MESSAGE_MAP(MainFrameWnd, WindowImplBase)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_WINDOWINIT, OnPrepare)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_SHOWACTIVEX, ShowFlashCtrol)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_MENU, OnMenu)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_VALUECHANGED, OnValueChanged)
DUI_END_MESSAGE_MAP()

BEGIN_WND_NOTIFY_MAP(MainFrameWnd)
    CHAIN_NOTIFY_MAP_MEMBER(TheFirstPage_)
    CHAIN_NOTIFY_MAP_MEMBER(TheSecondPage_)
    CHAIN_NOTIFY_MAP_MEMBER(TheThirdPage_)
    CHAIN_NOTIFY_MAP_MEMBER(TheFifthPage_)
    CHAIN_NOTIFY_MAP_MEMBER(TheSixthpage_)
END_WND_NOTIFY_MAP()
#if 0
void mainframe::Notify(TNotifyUI& msg) 
{ 
    while(1) {
        if(page1.Handler(msg))  break;
        if(page2.Handler(msg))  break;
        if(page3.Handler(msg))  break;
        break;
    }
    return CNotifyPump::NotifyPump(msg); 
}
#endif

MainFrameWnd:: MainFrameWnd()
{
    ATL::CImage img;
    img.Load(_T("G:\\test.gif"));
    int width = img.GetWidth();
}

MainFrameWnd:: ~MainFrameWnd()
{
    Shell_NotifyIcon(NIM_DELETE, &trayid);
}
  
void MainFrameWnd::OnFinalMessage(HWND hWnd)
{

}

void MainFrameWnd::InitWindow()
{
    TheFirstPage_.SetPaintMagager(&m_PaintManager);
    TheSecondPage_.SetPaintMagager(&m_PaintManager);
    TheThirdPage_.SetPaintMagager(&m_PaintManager);
    TheFifthPage_.SetPaintMagager(&m_PaintManager);
    TheSixthpage_.SetPaintMagager(&m_PaintManager);
    SetTray();
    SetWndShadow();
    InitBrowser();
    m_PaintManager.FindControl(_T("EditChange"))->SetFocus();
    
//     long style = GetWindowLong(m_hWnd, GWL_STYLE);
//     SetWindowLong(m_hWnd,GWL_EXSTYLE, style | WS_EX_LAYERED);
//     SetLayeredWindowAttributes(m_hWnd, 0, 255*70/100, LWA_ALPHA);

//     COptionUI* pOpt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("option2")));
//     if (pOpt) {
//         pOpt->Selected(true);
//     }
}

//设置阴影窗口
void  MainFrameWnd::SetWndShadow()
{
    CWndShadow::Initialize(m_PaintManager.GetInstance());
    m_WndShadow.Create(m_hWnd);
    m_WndShadow.SetSize(4);
    m_WndShadow.SetPosition(0, 0);
}

/*********************************基于IE内核浏览器控件****************************************/
void MainFrameWnd::InitBrowser()
{
    CActiveXUI* pActiveXUI = static_cast<CActiveXUI*>(
        m_PaintManager.FindControl(_T("ActiveXDemo1")));
    if (pActiveXUI) {
        IWebBrowser2* pWebBrowser = NULL;
//         pActiveXUI->SetDelayCreate(false);
//         pActiveXUI->CreateControl(CLSID_WebBrowser);    
        pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);
        if (pWebBrowser != NULL ) {
            pWebBrowser->Navigate(L"http://help.bjca.org.cn", NULL, NULL, NULL, NULL); 
            pWebBrowser->Release();
        }
    }
}
/*********************************************************************************************/

void MainFrameWnd::OnPrepare(TNotifyUI& msg)
{
    //禁用窗口最大化效果
#if 0
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    styleValue &= ~WS_MAXIMIZEBOX;
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
#endif
}

/*********************************flash控件***********************************************/
void MainFrameWnd::ShowFlashCtrol(TNotifyUI& msg)
{
    if (msg.pSender->GetName() != _T("flash") ) {
        return;
    }
    IShockwaveFlash* pFlash = NULL;
    CActiveXUI* pActiveX = static_cast<CActiveXUI*>(msg.pSender);
    pActiveX->GetControl(IID_IUnknown, (void**)&pFlash);
    if (pFlash != NULL) {
        //pFlash->put_WMode( _bstr_t(_T("Transparent") ) );
        //CDuiString ST = m_PaintManager.GetInstancePath();
        //BSTR BS = _bstr_t(m_PaintManager.GetInstancePath() + _T("\\skin\\test.swf"));
        BSTR FlashPath = _bstr_t(_T("G:\\practice\\Duilib\\FrameWnd\\bin\\skin\\test.swf"));
        HRESULT hr = pFlash->put_Movie(FlashPath);
        if (hr != S_OK) {
            return;
        }
        pFlash->DisableLocalSecurity();
        pFlash->put_AllowScriptAccess(_T("always"));
        BSTR response;
        pFlash->CallFunction(_T("<invoke name=\"setButtonText\" returntype=\"xml\"><arguments>                   <string>Click me!</string></arguments></invoke>"), &response);
        pFlash->Release();
    }  
}
/********************************************************************************************/

CDuiString MainFrameWnd::GetSkinFolder()
{
    return _T("skin");
}

CDuiString MainFrameWnd::GetSkinFile()
{
    return _T("mainframe.xml");
}

LPCTSTR MainFrameWnd::GetWindowClassName() const
{
    return _T("UIFrameWndOfDuilib");
}

UILIB_RESOURCETYPE MainFrameWnd::GetResourceType() const
{
#ifdef _DEBUG
    return UILIB_FILE;
    //return UILIB_ZIP;
#else
    return UILIB_ZIP;
#endif
}

CDuiString MainFrameWnd::GetZIPFileName() const
{
    return _T("skin.zip");
}

void MainFrameWnd::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == TIMER_ID1) {
        KillTimer(m_hWnd, TIMER_ID1);
        MessageBox(NULL, 0, _T("1"), MB_OK);
    } else if (nIDEvent == TIMER_ID2) {
        KillTimer(m_hWnd, TIMER_ID2);
        MessageBox(NULL, 0, _T("2"), MB_OK);
    }
}

LRESULT MainFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//    switch(uMsg) {
//         case WM_LBUTTONDOWN:
//                 
//         break;
   if (uMsg == WM_CHANGESKIN_MESSAGE) {
       switch (lParam) {
           case GREEN:
//                m_PaintManager.FindControl(BKGROUND_CONTROL_IN_FRAME)->
//                    SetBkImage(BKGROUND_IMAGE1_IN_FRAME);
               m_PaintManager.SetResourceZip(_T("skin.zip"));
               m_PaintManager.ReloadSkin();
               break;
           case BLUE:
//                 m_PaintManager.FindControl(BKGROUND_CONTROL_IN_FRAME)->
//                     SetBkImage(BKGROUND_IMAGE2_IN_FRAME);
               m_PaintManager.SetResourceZip(_T("skin2.zip")); 
               m_PaintManager.ReloadSkin();
             
                break;
           case PINK:
               m_PaintManager.SetResourceZip(_T("skin3.zip"));
               m_PaintManager.ReloadSkin();
               break;
       }
   }

   if (uMsg == WM_TRAY_MESSAGE) {       
       if (lParam == WM_RBUTTONDOWN) {		
           POINT pt;		
           GetCursorPos(&pt);
           SetForegroundWindow(m_hWnd); //在任何一处点击，右键菜单就能消失
           TrackPopupMenu(hTrayMenu_, TPM_BOTTOMALIGN|TPM_RIGHTBUTTON, 
               pt.x, pt.y, NULL, m_hWnd, NULL);	
       } else if (lParam == WM_LBUTTONDOWN) {
           ShowWindow(true);
       }	
   }

   if (uMsg == WM_COMMAND) {
       switch (wParam) {
       case IDR_EXIT:
            PostQuitMessage(0);
       }
   }
       
   if(uMsg == WM_MENUSELECTMSG)  //菜单消息
   {
       LPTSTR menusel = (LPTSTR)wParam;
       ::MessageBox(this->m_hWnd, menusel, _T("message"), 0);
   }

   if (uMsg == WM_TIMER) {
       OnTimer(wParam);
   }
   
//    if (uMsg == WM_RBUTTONDOWN) { 右键消息
//         ::MessageBox(this->m_hWnd, 0, _T("message"), 0);
//    }
//    if (uMsg == WM_CLOSE) {  //系统关闭消息
//        ShowWindow(false);
//        return 0;
//    }
   return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MainFrameWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
    if (wParam == SC_ZOOM) {    //禁用最大化按钮消息
        return 0;
    }
#endif
    
    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MainFrameWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

//     if (uMsg == WM_DESTROY) {
//         ShowWindow(false);
//         bHandled = FALSE;
//     }
    return 0;
}

void MainFrameWnd::OnMenu(TNotifyUI& msg)
{
    //MessageBox(NULL, 0, 0, MB_OK);
    CMenuWnd* pMenu = new CMenuWnd(m_hWnd);
    DuiLib::CPoint point = msg.ptMouse;
    ClientToScreen(m_hWnd, &point);
    pMenu->Init(NULL, _T("menutest.xml"), _T("xml"), point);   
}

void MainFrameWnd::OnClick(TNotifyUI& msg)
{
    
    CString controlName = msg.pSender->GetName();
    if (controlName.Compare(BTN_CLOSE_IN_MAINFRAME) == 0) {
        //::AnimateWindow(m_hWnd, 1000, AW_HOR_POSITIVE|AW_HIDE);
        PostQuitMessage(0);
        //CloseWindow(m_hWnd);
        //ShowWindow(SW_HIDE);
    } else if (controlName.Compare(BTN_MIN_IN_MAINFRAME) == 0) {
        SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
    } else if (controlName.Compare(BTN_MAX_IN_MAINFRAME) == 0) {
        SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    } else if (controlName.Compare(BTN_SKIN_IN_MAINFRAME) == 0) {
        ChangeSkin();
    } else if (controlName.Compare(BTN_OPEN_BROWSER) == 0) {
        OpenBrowser();
    } else if (controlName.Compare(_T("hidebottompage")) == 0) {
        //m_PaintManager.FindControl(_T("bottompage"))->SetVisible(false);
        //m_PaintManager.SetMinInfo(910,118);
        //m_PaintManager.SetMaxInfo(910,0);
        //::SetWindowPos(m_hWnd, NULL, 0, 0, 910, 118, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
        m_PaintManager.FindControl(_T("BigWnd"))->SetVisible(false);
        m_PaintManager.FindControl(_T("scalewnd"))->SetVisible(true);
        MoveWindow(m_hWnd, 500, 50, 300, 500, false);
    } else if (controlName.Compare(_T("menuTest")) == 0) {
       //MessageBox(NULL, 0, 0, MB_OK);
        CMenuWnd* pMenu = new CMenuWnd(m_hWnd);
        DuiLib::CPoint point = msg.ptMouse;
        ClientToScreen(m_hWnd, &point);
        pMenu->Init(NULL, _T("menutest.xml"), _T("xml"), point);
    } else if (controlName.Compare(_T("SetTimer")) == 0) {
        SetTimer(m_hWnd, TIMER_ID1, 2000, NULL);
        SetTimer(m_hWnd, TIMER_ID2, 2000, NULL);
    }
}

void MainFrameWnd::ChangeSkin()
{
    POINT point;
    GetCursorPos(&point);
    //ScreenToClient(m_hWnd, &point);
    int x = point.x;
    int y = point.y;
    
    SkinWnd* pSkinWnd = new SkinWnd();
    if (pSkinWnd == NULL) {
        return;
    }
    pSkinWnd->Create(NULL, _T("SkinWnd"),
            UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
    pSkinWnd->SetMyWindowPos(x,y);
    pSkinWnd->ShowModal(); 
}
void MainFrameWnd::OnValueChanged( TNotifyUI &msg )
{
    CString pEditCtrol = msg.pSender->GetName();
    if (pEditCtrol == _T("EditChange")) {
        int num = 0;
    }
}

void MainFrameWnd::OnSelectChanged( TNotifyUI &msg )
{
    CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(
        m_PaintManager.FindControl(TABCONTROL_IN_MAINFRAME));
    if (!pTabControl) {
       return;
    }
    CDuiString OptionName = msg.pSender->GetName();
    if (OptionName == OPTIONNAME1_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION0);
    } else if (OptionName == OPTIONNAME2_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION1);
    } else if (OptionName == OPTIONNAME3_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION2);
    } else if (OptionName == OPTIONNAME4_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION3);
    } else if (OptionName == OPTIONNAME5_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION4);
    } else if (OptionName == OPTIONNAME6_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION5);
    } else if (OptionName == OPTIONNAME7_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION6);
    } else if (OptionName == OPTIONNAME8_IN_MAINFRAME) {
        pTabControl->SelectItem(TAB_OPTION7);
    } 
}

CControlUI* MainFrameWnd::CreateControl(LPCTSTR pstrClass)
{
    if (_tcscmp(pstrClass, PAGE1_IN_MAINFRAME) == 0) {
        return new HomeUI(&m_PaintManager);
    } else if (_tcscmp(pstrClass, PAGE2_IN_MAINFRAME) == 0) {
        return new PageUI2;
    } else if (_tcscmp(pstrClass, PAGE3_IN_MAINFRAME) == 0) {
        return new PageUI3;
    } else if (_tcscmp(pstrClass, PAGE5_IN_MAINFRAME) == 0) {
        return new PageUI5(&m_PaintManager);
    } else if (_tcscmp(pstrClass, PAGE6_IN_MAINFRAME) == 0) {
        return new PageUI6(&m_PaintManager);
    } else if (_tcscmp(pstrClass, _T("ButtonGif")) == 0) {
        return new CButtonGifUI;
    }
    return NULL;
}

void MainFrameWnd::SetTray()
{
    //托盘
	UINT WM_TASKBARCREATED;
	// 不要修改TaskbarCreated，这是系统任务栏自定义的消息
	WM_TASKBARCREATED = RegisterWindowMessage(TEXT("TaskbarCreated"));
	memset(&trayid, 0, sizeof(NOTIFYICONDATA));
	trayid.cbSize = sizeof(trayid);
	trayid.hWnd = m_hWnd;
	trayid.uID = 1;
	trayid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	trayid.uCallbackMessage = WM_TRAY_MESSAGE;
	trayid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	lstrcpy(trayid.szTip, szAppName);

	hTrayMenu_ = CreatePopupMenu();    //生成菜单
	AppendMenu(hTrayMenu_, MF_STRING, IDR_EXIT, _T("退出"));
	Shell_NotifyIcon(NIM_ADD, &trayid);	
}

void MainFrameWnd::OpenBrowser()
{
    CControlUI* pEdit = static_cast<CControlUI*>(m_PaintManager.FindControl(EDIT_WEB_BROWSER));
    CString strWeb = pEdit->GetText();
    CActiveXUI* pActiveXUI = static_cast<CActiveXUI*>(
        m_PaintManager.FindControl(_T("ActiveXDemo1")));
    if (pActiveXUI) {
        IWebBrowser2* pWebBrowser = NULL;
        //pActiveXUI->SetDelayCreate(false);
        //pActiveXUI->CreateControl(CLSID_WebBrowser);    
        pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);
        if (pWebBrowser != NULL ) {
            pWebBrowser->Navigate(strWeb.AllocSysString(), NULL, NULL, NULL, NULL); 
            pWebBrowser->Release();
        }
    }
}

LRESULT MainFrameWnd::OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
    CControlUI* pNewHover = m_PaintManager.FindControl(pt);
    if (pNewHover && (pNewHover->GetName() == _T("skinbtn"))) {
        //MessageBox(NULL, 0, 0, MB_OK);
    }
    bHandled = FALSE;
    return 0;
}


#if 0
LRESULT MainFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //不响应窗口缩放。
    return 0;
}

//只保留窗口拖动效果，不响应鼠标缩放效果。
LRESULT MainFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);

    RECT rcClient;
    ::GetClientRect(*this, &rcClient);

    RECT rcCaption = m_PaintManager.GetCaptionRect();
    if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
        && pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
            CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
            if (pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
                _tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
                _tcsicmp(pControl->GetClass(), _T("TextUI")) != 0 ) {
                    return HTCAPTION;
            }               
    }
    return HTCLIENT;
}
#endif
