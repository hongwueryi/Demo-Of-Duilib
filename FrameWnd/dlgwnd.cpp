#include "stdafx.h"
#include "dlgwnd.h"

#define  TIMER_WAITING_IMG          300
#define  WAITING_IMG_WIDTH          50
#define  WAITING_IMG_HEIGHT         50

DUI_BEGIN_MESSAGE_MAP(CDlgWnd, WindowImplBase)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_WINDOWINIT,OnPrepare)
DUI_END_MESSAGE_MAP()

CDlgWnd::CDlgWnd()
{

}

CDlgWnd::~CDlgWnd()
{

}


void CDlgWnd::OnFinalMessage(HWND hWnd)
{
    WindowImplBase::OnFinalMessage(hWnd);
    delete this;  //窗口关闭是删除自身的窗口指针(外部调用是创建窗口指针)
}

CDuiString CDlgWnd::GetSkinFile()
{
    return _T("dlgwnd.xml");
}

CDuiString CDlgWnd::GetSkinFolder()
{
    return  _T("skin\\");
}

UILIB_RESOURCETYPE CDlgWnd::GetResourceType() const
{
    return UILIB_FILE;
}

LRESULT CDlgWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == SC_ZOOM) return 0; 
    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CDlgWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_TIMER) 
        OnTimer(wParam);
    return __super::HandleMessage(uMsg, wParam, lParam);
}

void CDlgWnd::InitWindow()
{
   
    SetWindowLong(*this, GWL_EXSTYLE, GetWindowLong(*this, 
        GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

    //AnimateWnd();
}

void CDlgWnd::OnPrepare(TNotifyUI& msg)
{
    //禁用窗口最大化效果
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    styleValue &= ~WS_MAXIMIZEBOX;
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    LONG nRet = ::GetWindowLong(*this, GWL_EXSTYLE);
    nRet = nRet | WS_EX_LAYERED;
    ::SetWindowLong(*this, GWL_EXSTYLE, nRet);
    ::SetLayeredWindowAttributes(m_hWnd, 0, 255, LWA_ALPHA);    // 255设置不透明  0设置透明
    //::SetLayeredWindowAttributes(m_hWnd, RGB(0xFF,0xFF,0xFF), 0, LWA_COLORKEY);    //过滤白色

    SetTimer(m_hWnd, TIMER_WAITING_IMG, 100, NULL);
}

void CDlgWnd::OnClick( TNotifyUI &msg )
{
    if (_tcsicmp(msg.pSender->GetName(), _T("closebtn")) == 0) {
        //::AnimateWindow(m_hWnd, 1000, AW_BLEND);
        Close();
    } 
    
}

void CDlgWnd::OnTimer(UINT_PTR nIDEvent) 
{
    if (nIDEvent == TIMER_WAITING_IMG) {
        static int s_nAni = 0;
        //static_cast<CExamImage*>(exam_imageui_)->SetImagePosByIndex((s_nAni ++) % 12);
        int pos = s_nAni++;
        SetExamImage(_T("Res/waiting.png"), (pos % 8) * WAITING_IMG_WIDTH, 
            0, ((pos % 8) + 1) * WAITING_IMG_WIDTH, WAITING_IMG_HEIGHT);
    }
}


void CDlgWnd::SetExamImage(CDuiString imgPath, int nLeftPos, int nTop, int nWidthint, int nHeight)
{    
    CControlUI * waiting_imageui_ = m_PaintManager.FindControl(_T("pic_waiting"));
    if (waiting_imageui_) {
        CDuiString newSource = _T("");
        newSource.Format(_T("file=\'%s\' source=\'%d,%d,%d,%d\'"), imgPath.GetData(), nLeftPos, nTop, nWidthint, nHeight);
        waiting_imageui_->SetBkImage(newSource);
    }
}


void CDlgWnd::AnimateWnd()
{
    if (m_hWnd == NULL) {
        return;
    }
    bool a = ::AnimateWindow(m_hWnd, 1000, AW_SLIDE|AW_HOR_POSITIVE);
    int err = GetLastError();
}

LRESULT CDlgWnd::OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    //MessageBox(NULL, _T("killfocus"), 0, MB_OK);
    bHandled = TRUE;
    //PostQuitMessage(0);
    return 0;
}

//只保留窗口拖动效果，不响应鼠标缩放效果。
LRESULT CDlgWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);

    RECT rcClient;
    ::GetClientRect(*this, &rcClient);

    RECT rcCaption = m_PaintManager.GetCaptionRect();
    if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
        && pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
            CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
            if( pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
                _tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
                _tcsicmp(pControl->GetClass(), _T("TextUI")) != 0 )
                return HTCAPTION;
    }
    return HTCLIENT;
}

