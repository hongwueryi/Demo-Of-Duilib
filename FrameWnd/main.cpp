#include "stdafx.h"
#include "mainframe.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    CreateMutex(NULL, FALSE, _T("FrameWndOfDuilib"));
    if (ERROR_ALREADY_EXISTS == GetLastError()) {
        HWND hWnd = FindWindow(NULL, _T("Duilib界面框架"));
        if (hWnd != NULL) {
            ShowWindow(hWnd, SW_SHOW);
            SetForegroundWindow(hWnd);
        }
        return 0;
    }
    //CWkeWebkitUI::WkeWebkit_Init();
    CPaintManagerUI::SetInstance(hInstance);
    MainFrameWnd* pFrame = new MainFrameWnd();
    if( pFrame == NULL ) return 0;  
    pFrame->Create(NULL, _T("Duilib界面框架"), 
        UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 300, 500);
    pFrame->CenterWindow();
    ::ShowWindow(*pFrame, SW_SHOWNORMAL);
    ::SetForegroundWindow(pFrame->GetHWND());
    ::BringWindowToTop(pFrame->GetHWND());
    CPaintManagerUI::MessageLoop();
    //CWkeWebkitUI::WkeWebkit_Shutdown();
    ::CoUninitialize();
    return 0;
}