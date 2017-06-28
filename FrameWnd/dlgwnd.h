#ifndef DLG_WND_HPP
#define DLG_WND_HPP
#include "dataDefine.h"

class CDlgWnd : public WindowImplBase
{
public:

    CDlgWnd();
    ~CDlgWnd();

public:

    LPCTSTR GetWindowClassName() const { return _T("UIFindPswWnd"); };
    virtual void OnFinalMessage(HWND hWnd);
    virtual void InitWindow();
    virtual UILIB_RESOURCETYPE GetResourceType() const;
    virtual CDuiString GetSkinFile();
    virtual CDuiString GetSkinFolder();
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {return 0;}
    virtual LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);

public:
    void AnimateWnd();
    void OnTimer(UINT_PTR nIDEvent);
    void SetExamImage(CDuiString imgPath, int nLeftPos, int nTop, int nWidthint, int nHeight);

    DUI_DECLARE_MESSAGE_MAP()
    virtual void OnClick(TNotifyUI& msg);
    virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) { return 0;}

protected:	
    void OnPrepare(TNotifyUI& msg);
};

#endif