#include "page2.h"
#include "ListEx.h"

CPageUI2::CPageUI2()
{
    paint_manager_ = NULL;
}

CPageUI2::~CPageUI2()
{

}

LRESULT CPageUI2::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
     return 0;
}

BOOL CPageUI2::Handler(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK) {
        return OnClick(msg);
    } else if (msg.sType == DUI_MSGTYPE_WINDOWINIT) {
        return OnInitWindow();
    }

    return FALSE;
}

void CPageUI2::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
    paint_manager_ = pPaintMgr;
    paint_manager_->AddMessageFilter(this);
}

BOOL CPageUI2::OnClick(TNotifyUI& msg)
{
    CDuiString ControlName = msg.pSender->GetName();
    if (ControlName == ADDITEM_LISTEX_IN_PAGE2) {
        AddItemByCode(_T("这是动态添加的编辑框"), _T("这是动态添加的数据"));
        return TRUE;
    } else if (msg.pSender->GetName() == BTN_ADDITEM_IN_LISTEX) {
        OnClickListItemBtn(msg);  //添加按钮
        return TRUE;
    } else if (msg.pSender->GetName() == ADDITEM_BYXML_LISTEX_IN_PAGE2) {
        AddItemByXML();
        return TRUE;
    } else if (msg.pSender->GetName() == BTN_ADDITEMEX_IN_LISTEX) {
        OnClickListItemBtnEx(msg);  //按钮1
        return TRUE;
    } else if (msg.pSender->GetName() == BTN_DELETEITEMEX_IN_LISTEX) {
        OnDeleteListItemBtnEx(msg);  //删除
        return TRUE;
    } else if (msg.pSender->GetName() == BTN_EXPANDITEMEX_IN_LISTEX) {
        OnExpandListItemBtnEx(msg);  //详情
        return TRUE;
    }
    return FALSE;
}

BOOL CPageUI2::OnInitWindow()
{
    CListUI* pList = static_cast<CListUI*>(paint_manager_->FindControl(LISTVIEW_IN_PAGE2));
    if (pList) {
        for (int i = 0; i < 10; i++) {
            CListTextElementUI* pListElement = new CListTextElementUI;
            pListElement->SetTag(i);
            pList->Add(pListElement);
            pListElement->SetText(0, _T("NAME"));
            pListElement->SetText(1, _T("程序设计"));
            pListElement->SetText(2, _T("100"));
        }        
    }

    //Slider事件
    CSliderUI* pSilder = static_cast<CSliderUI*>(paint_manager_->FindControl(_T("alpha_controlor")));
    if (pSilder) {
        pSilder->OnNotify += MakeDelegate(this, &CPageUI2::OnAlphaChanged);
    }
    return FALSE;
}

bool CPageUI2::OnAlphaChanged(void* param) {
    TNotifyUI* pMsg = (TNotifyUI*)param;
    if( pMsg->sType == _T("valuechanged") ) {
        paint_manager_->SetTransparent((static_cast<CSliderUI*>(pMsg->pSender))->GetValue());
        /*paint_manager_->SetBackgroundTransparent(false);*/
    }
    return true;
}

void CPageUI2::AddItemByCode(LPCTSTR EditData, LPCTSTR TextData)
{
    CListUIEx *pList = static_cast<CListUIEx*>(paint_manager_->FindControl(_T("listex")));
    int nIndex = pList->GetCount();
    pList->InsertItem(nIndex);
    CEditUI *pControl = new CEditUI; 
    pControl->SetText(EditData);
    TCHAR index[20] = {0};
    _itow(nIndex, index, 20);
    TCHAR Edit[MAX_PATH] = _T("edit");
    wcscat_s(Edit, 10, index);
    pControl->SetName(Edit);
    pControl->SetBorderColor(RGB(255, 0, 0));
    pControl->SetAttribute(_T("bordersize"), _T("1"));
    pControl->SetAttribute(_T("bordercolor"), _T("#FF4775CC"));
    //pControl->SetAttribute(_T("width"), _T("190"));
    pList->SetItemData(nIndex, 0, pControl);

    CButtonUI *pBtnUI = new CButtonUI;
    pBtnUI->SetName(_T("MyAddBtn"));
    pBtnUI->SetText(_T("添加"));
    pBtnUI->SetFixedWidth(60);
    pBtnUI->SetAttribute(_T("pushedimage"), 
        _T("file='Res/page1/button_pushed.png' corner='4,4,4,4'"));
    pBtnUI->SetAttribute(_T("hotimage"), 
        _T("file='Res/page1/button_hover.png' corner='4,4,4,4'"));
    pBtnUI->SetAttribute(_T("normalimage"), 
        _T("file='Res/page1/button_normal.png' corner='4,4,4,4'"));		
    pList->SetItemData(nIndex, 1, pBtnUI);

    pList->SetItemData(nIndex, 2, TextData, _T("testid"));
}

void CPageUI2::OnClickListItemBtn(TNotifyUI& msg)
{
    CDuiString elementname1 = msg.pSender->GetClass(); //ButtonUI
    CDuiString elementname2 = msg.pSender->GetParent()->GetClass(); //HorizontalLayoutUI
    CDuiString elementname3 = 
        msg.pSender->GetParent()->GetParent()->GetClass(); //HorizontalLayoutUI
    CDuiString elementname4 = 
        msg.pSender->GetParent()->GetParent()->GetParent()->GetClass(); //ListContainerElementUI
    CListContainerElementUI* pl = static_cast<CListContainerElementUI*>(
        msg.pSender->GetParent()->GetParent()->GetParent());
    int nIndex = pl->GetIndex();
    TCHAR index[20] = {0};
    _itow(nIndex, index, 10);
    TCHAR Edit[MAX_PATH] = _T("edit");
    wcscat_s(Edit, 10, index);
    CControlUI* pcon = paint_manager_->FindControl(Edit);
    MessageBox(NULL,  pcon->GetText(), index, MB_OK);
}

void CPageUI2::AddItemByXML()
{
    CDialogBuilder builder;
    CListContainerElementUI* pLine = (CListContainerElementUI*)(
        builder.Create(_T("listex.xml"), (UINT)0));
    if (pLine != NULL) {
        CListUIEx *pList = static_cast<CListUIEx*>(paint_manager_->FindControl(_T("listex")));
        pList->InsertItem(pList->GetCount(), 80, pLine);
    }
}

//扩展列表中的按钮1
void CPageUI2::OnClickListItemBtnEx(TNotifyUI& msg)
{
//     CDuiString elementname4 = 
//         msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()->GetClass(); 
    CListContainerElementUI* pl = static_cast<CListContainerElementUI*>(
        msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()->GetParent());

    int nIndex = pl->GetIndex();

    TCHAR index[20] = {0};
    _itow(nIndex, index, 10);
    MessageBox(NULL, _T("点击了!"), index, MB_OK);
}

//扩展列表中的删除按钮
void CPageUI2::OnDeleteListItemBtnEx(TNotifyUI& msg)
{
    CListContainerElementUI* pl = static_cast<CListContainerElementUI*>(
        msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()->GetParent());
    int nIndex = pl->GetIndex();
    CListUIEx *pList = static_cast<CListUIEx*>(paint_manager_->FindControl(_T("listex")));

    pList->RemoveAt(nIndex);
}

//扩展列表中的收缩按钮
void CPageUI2::OnExpandListItemBtnEx(TNotifyUI& msg)
{
     CVerticalLayoutUI* pVertical = static_cast<CVerticalLayoutUI*>(
         msg.pSender->GetParent()->GetParent());
     CListContainerElementUI* pl = static_cast<CListContainerElementUI*>(
         msg.pSender->GetParent()->GetParent()->GetParent());
     //CDuiString str = pVertical->GetItemAt(1)->GetClass();

     if (msg.pSender->GetText() == _T("收起")) {        
         pVertical->GetItemAt(1)->SetVisible(false);        
         pl->SetFixedHeight(20);
         msg.pSender->SetText(_T("详情"));
     } else {
         pVertical->GetItemAt(1)->SetVisible(true);        
         pl->SetFixedHeight(80);
         msg.pSender->SetText(_T("收起"));
     }   
}