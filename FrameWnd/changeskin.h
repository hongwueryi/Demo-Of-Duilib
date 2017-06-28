#ifndef CHANGESKIN_H
#define CHANGESKIN_H

class SkinWnd : public WindowImplBase
{
public:
	SkinWnd();
	~SkinWnd();

public:
    LPCTSTR GetWindowClassName() const { return _T("UISkinChangeWnd"); };
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)         {return 0;}
    void SetMyWindowPos(int x, int y);
    DUI_DECLARE_MESSAGE_MAP()
    virtual void OnClick(TNotifyUI& msg);

protected:	    
	void OnPrepare(TNotifyUI& msg);
};

#endif