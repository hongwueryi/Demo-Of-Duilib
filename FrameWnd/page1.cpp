#include "page1.h"
#include "dlgwnd.h"

CPageUI1::CPageUI1()
{
    paint_manager_ = NULL;
}

CPageUI1::~CPageUI1()
{

}

LRESULT CPageUI1::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    if (uMsg == WM_TIMER) {
        OnTimer(wParam);
    } else if (uMsg == WM_MOUSEHOVER) {
         int m = 0;
    }
    return 0;
}

BOOL CPageUI1::Handler(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK) {
        return OnClick(msg);
    } else if (msg.sType == DUI_MSGTYPE_WINDOWINIT) {
        return OninitWindow();
    } else if (msg.sType == DUI_MSGTYPE_ITEMSELECT) {
        return OnItemSelect();
    }

    return FALSE;
}

void CPageUI1::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
    paint_manager_ = pPaintMgr;
    paint_manager_->AddMessageFilter(this);
}

BOOL CPageUI1::OnClick(TNotifyUI& msg)
{
    CDuiString ControlName = msg.pSender->GetName();
    if (ControlName == BTN_COMMAND_IN_PAGE1) {
        //MessageBox(NULL, _T("你使用了快捷键按钮"), _T("提示"), MB_OK);
        SetTimer(paint_manager_->GetPaintWindow(), TIMER_PROCESSBARID_IN_PAGE1, 100, NULL);
        return TRUE;
    } else if (ControlName == BTN_DIALOG_IN_BTN) {
        OpenDlgWindow();
        return TRUE;
    }
    return FALSE;
}

BOOL CPageUI1::OninitWindow()
{

   /////////////////////////////////////////////////////////////////////////
   pCombo_ = static_cast<CComboUI*>(paint_manager_->FindControl(COMBO1_IN_PAGE1));
   if (pCombo_) {
       CListLabelElementUI* pElement = new CListLabelElementUI;
       pElement->SetText(_T("微软雅黑"));
       pCombo_->Add(pElement);
       CListLabelElementUI* pElement2 = new CListLabelElementUI;
       pElement2->SetText(_T("宋体"));
       pCombo_->Add(pElement2);
       pCombo_->SelectItem(0);
   }
   /////////////////////////////////////////////////////////////////////////
   pProgress_ = static_cast<CProgressUI*>(paint_manager_->FindControl(PRRGRESS_IN_PAGE1));
   progressbar_value_ = 8;
   pProgress_->SetValue(progressbar_value_);
   return FALSE;
}

void CPageUI1::OnTimer(UINT_PTR nID_Event)
{
    if (nID_Event == TIMER_PROCESSBARID_IN_PAGE1) {
        progressbar_value_ += 4;
        pProgress_->SetValue(progressbar_value_);
        if (progressbar_value_ >= 100) {
            KillTimer(paint_manager_->GetPaintWindow(), nID_Event);
        }
    }  
}

BOOL CPageUI1::OnItemSelect()
{
    if (pCombo_) {       
       CControlUI* pControl = static_cast<CControlUI*>(
           paint_manager_->FindControl(COMBO1_VALUE_IN_PAGE1));
       pControl->SetText(pCombo_->GetText());
    }
    return FALSE;
}

UINT WINAPI threadProc(LPVOID param)
{
    FILE* fp;
    SYSTEMTIME time;
    while(true) {
        fp = fopen("G:\\practice\\Duilib\\FrameWnd\\FrameWnd\\test.txt", "a+");
        if (fp == NULL) {
            break;
        }
        GetLocalTime(&time);
        fprintf(fp, "%d:%d:%d==", time.wMinute, time.wSecond, time.wMilliseconds);
        Sleep(1000);
        fprintf(fp, "%d:%d:%d\n", time.wMinute, time.wSecond, time.wMilliseconds);
        fclose(fp);
    }
    return 0;
}
void CPageUI1::OpenDlgWindow()
{
    CDlgWnd* pDlg = new CDlgWnd();
    if (pDlg == NULL) {
        return;
    }
    //Create(NULL, WINDOW_NAME_SIGNIMG, UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE, 0, 0, width, height, NULL);
    pDlg->Create(NULL, NULL, UI_WNDSTYLE_FRAME, 
        WS_EX_WINDOWEDGE, 0, 0, 0, 0, NULL);
//     pDlg->Create(NULL/*paint_manager_->GetPaintWindow()*/,
//         _T("123"), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
    pDlg->CenterWindow();
    //pDlg->AnimateWnd();
    //pDlg->ShowModal();
   pDlg->ShowWindow(true);

    //_beginthreadex(NULL, 0, threadProc, NULL, 0, NULL);
}