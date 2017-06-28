#ifndef PAGE3_H
#define PAGE3_H
#include "stdafx.h"
#include "datadefine.h"

class CPageUI3 : public IHandlerMsg, public CWebBrowserEventHandler{
public:
    CPageUI3();
    ~CPageUI3();

public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    virtual BOOL Handler(TNotifyUI& msg);
    BOOL OnWindowInit();
    void SetPaintMagager(CPaintManagerUI* pPaintMgr);
    BOOL OnClick(TNotifyUI& msg);
    BOOL OnSelectChanged(TNotifyUI& msg);
    void OpenWebBrowser();
private:
    CPaintManagerUI* paint_manager_;
    CWebBrowserUI* pBrowser;
};
#endif