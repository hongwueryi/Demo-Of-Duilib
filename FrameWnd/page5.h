#ifndef PAGE5_H
#define PAGE5_H
#include "stdafx.h"
#include "datadefine.h"
#include "MyList.h"

class CPageUI5 : public IHandlerMsg, IMessageFilterUI{
public:
    CPageUI5();
    ~CPageUI5();

public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    virtual BOOL Handler(TNotifyUI& msg);
    void SetPaintMagager(CPaintManagerUI* pPaintMgr);
    BOOL OnClick(TNotifyUI& msg);
    BOOL OnInitWindow();
private:
    CPaintManagerUI* paint_manager_;
    CMyList mylist_;
};
#endif