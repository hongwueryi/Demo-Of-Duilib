#ifndef PAGE6_H
#define PAGE6_H
#include "stdafx.h"
#include "datadefine.h"
#include "WkeWebkit.h"

#define WM_USER_TITLE_CHANGE         WM_USER + 289     // 浏览器标题改变
#define WM_USER_URL_CHANGE		     WM_USER + 290     // 浏览器URL改变
#define WM_USER_JS_NOTIFY		     WM_USER + 291     // js脚本函数调用c++函数

class CPageUI6 : public IHandlerMsg, IMessageFilterUI{
public:
    CPageUI6();
    ~CPageUI6();

public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    //virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual BOOL Handler(TNotifyUI& msg);
    void SetPaintMagager(CPaintManagerUI* pPaintMgr);
    BOOL OnClick(TNotifyUI& msg);
    BOOL OnInitWindow();
    void InitWkeBrowser();

    LRESULT OnTitleChanged(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT OnURLChanged(HWND hwnd, WPARAM wParam, LPARAM lParam);
    LRESULT OnJsNotify(HWND hwnd, WPARAM wParam, LPARAM lParam);

private:
    CPaintManagerUI* paint_manager_;
    CWkeWebkitUI* m_pWke;
    CEditUI	*m_pURLEdit;
    CLabelUI *m_pLblStatusBar;
    wstring	m_URL;
    wstring	m_Title;
};
#endif