#ifndef PAGE1_H
#define PAGE1_H
#include "stdafx.h"
#include "datadefine.h"
class CPageUI1 : public IHandlerMsg, IMessageFilterUI{
public:
    CPageUI1();
    ~CPageUI1();

public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    virtual BOOL Handler(TNotifyUI& msg);
    void SetPaintMagager(CPaintManagerUI* pPaintMgr);
    BOOL OnClick(TNotifyUI& msg);
    BOOL OninitWindow();
    BOOL OnItemSelect();
    void OnTimer(UINT_PTR nID_Event);
    void OpenDlgWindow();
private:
    CPaintManagerUI* paint_manager_;
    CComboUI* pCombo_;
    CProgressUI* pProgress_;
    int progressbar_value_;
};
#endif