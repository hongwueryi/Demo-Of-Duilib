#ifndef PAGE2_H
#define PAGE2_H
#include "stdafx.h"
#include "datadefine.h"

class CPageUI2 : public IHandlerMsg, IMessageFilterUI{
public:
    CPageUI2();
    ~CPageUI2();

public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    virtual BOOL Handler(TNotifyUI& msg);
    void SetPaintMagager(CPaintManagerUI* pPaintMgr);
    BOOL OnClick(TNotifyUI& msg);
    BOOL OnInitWindow();
    bool OnAlphaChanged(void* param);
    void OnClickListItemBtn(TNotifyUI& msg);
    void OnClickListItemBtnEx(TNotifyUI& msg);
    void OnDeleteListItemBtnEx(TNotifyUI& msg);
    void OnExpandListItemBtnEx(TNotifyUI& msg);
    void AddItemByXML();
    void AddItemByCode(LPCTSTR EditData, LPCTSTR TextData);
private:
    CPaintManagerUI* paint_manager_;
};
#endif