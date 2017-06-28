#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "stdafx.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page5.h"
#include "page6.h"
#include "WndShadow.h"

class MainFrameWnd : public WindowImplBase
{
public:
    MainFrameWnd();
    ~MainFrameWnd();

public:    
    virtual void OnFinalMessage(HWND hWnd);
    virtual void InitWindow();

protected:
    virtual CDuiString GetSkinFolder();
    virtual CDuiString GetSkinFile();
    LPCTSTR GetWindowClassName() const;
    void OnPrepare(TNotifyUI& msg);
    void ChangeSkin();
    void SetTray();
    void InitBrowser();
    void OpenBrowser();
    void SetWndShadow();
   
    
public:
    virtual CControlUI* CreateControl(LPCTSTR pstrClass);
    virtual UILIB_RESOURCETYPE GetResourceType() const;
    virtual CDuiString GetZIPFileName() const;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    DUI_DECLARE_MESSAGE_MAP()
    BEGIN_WND_NOTIFY_MAP_DECLARE(MainFrameWnd)
    virtual void OnClick(TNotifyUI& msg);
    virtual void OnSelectChanged(TNotifyUI &msg);
    void OnMenu(TNotifyUI& msg);
    void ShowFlashCtrol(TNotifyUI& msg);
    void OnValueChanged( TNotifyUI &msg );
    void OnTimer(UINT_PTR nIDEvent);
private:
    CPageUI1 TheFirstPage_;
    CPageUI2 TheSecondPage_;
    CPageUI3 TheThirdPage_;
    CPageUI5 TheFifthPage_;
    CPageUI6 TheSixthpage_;
    NOTIFYICONDATA trayid;
    HMENU hTrayMenu_;
    CWndShadow m_WndShadow;

};
#endif