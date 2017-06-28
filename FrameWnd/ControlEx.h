#ifndef CONTROLEX_H
#define CONTROLEX_H
#include "stdafx.h"
#include "MyList.h"
#include "controls_ex.h"

class CDialogBuilderCallbackEx :
    public IDialogBuilderCallback
{
public:
    CDialogBuilderCallbackEx(CPaintManagerUI* ppm = NULL){m_pm = ppm;}
   
    ~CDialogBuilderCallbackEx(void){}

    virtual CControlUI* CreateControl(LPCTSTR pstrClass)
    {
        if (_tcsicmp (pstrClass, _T ("MyList")) == 0) {
            return new CMyList (m_pm);
        } else if (_tcscmp(pstrClass, _T("ButtonGif")) == 0) {
            return new CButtonGifUI;
        } else if (_tcscmp(pstrClass, _T("wkeWebkit")) == 0) {
            return new CWkeWebkitUI;
        }
        return NULL;
    }

private:
    // 加一个PAINTMANAGER是为了加载　Default 项
    CPaintManagerUI* m_pm;
};

class HomeUI : public CContainerUI
{
public:
    HomeUI(CPaintManagerUI* m_pm)
    {
        CDialogBuilder builder;
        CDialogBuilderCallbackEx cb (m_pm);
        CContainerUI* pHome = static_cast<CContainerUI*>(
            builder.Create(_T("home.xml"), 0, &cb, m_pm));
        //CContainerUI* pHome = static_cast<CContainerUI*>(builder.Create(_T("home.xml"), (UINT)0));
        if (pHome) {
            this->Add(pHome);
        } else {
            this->RemoveAll();
            return;
        }
    }
};

class PageUI2 : public CContainerUI
{
public:
    PageUI2()
    {
        CDialogBuilder builder;
        CContainerUI* pCon = static_cast<CContainerUI*>(builder.Create(_T("PageUI2.xml"), (UINT)0));
        if (pCon) {
            this->Add(pCon);
        } else {
            this->RemoveAll();
            return;
        }
    }
};

class PageUI3 : public CContainerUI
{
public:
    PageUI3()
    {
        CDialogBuilder builder;
        CContainerUI* pCon = static_cast<CContainerUI*>(builder.Create(_T("PageUI3.xml"), (UINT)0));
        if (pCon) {
            this->Add(pCon);
        } else {
            this->RemoveAll();
            return;
        }
    }
};

class PageUI5 : public CContainerUI
{
public:
    PageUI5(CPaintManagerUI* m_pm)
    {
        CDialogBuilder builder;
        CDialogBuilderCallbackEx cb (m_pm);
        CContainerUI* pCon = static_cast<CContainerUI*>(
            builder.Create(_T("PageUI5.xml"), 0, &cb, m_pm));
 //CContainerUI* pCon = static_cast<CContainerUI*>(builder.Create(_T("PageUI5.xml"),(UINT)0));
        if (pCon) {
            this->Add(pCon);
        } else {
            this->RemoveAll();
            return;
        }
    }
};

class PageUI6 : public CContainerUI
{
public:
    PageUI6(CPaintManagerUI* m_pm)
    {
        CDialogBuilder builder;
        CDialogBuilderCallbackEx cb (m_pm);
        CContainerUI* pCon = static_cast<CContainerUI*>(
            builder.Create(_T("PageUI6.xml"), 0, &cb, m_pm));
        if (pCon) {
            this->Add(pCon);
        } else {
            this->RemoveAll();
            return;
        }
    }
};

#endif