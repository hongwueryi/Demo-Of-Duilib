#ifndef _UICRACK_H_
#define _UICRACK_H_


namespace DuiLib {

#define BEGIN_WND_NOTIFY_MAP(theClass) \
    void theClass::Notify(TNotifyUI& msg) \
    { \
    while(1)\
    {

#define CHAIN_NOTIFY_MAP_MEMBER(theChainMember) \
    if(theChainMember.Handler(msg))  break;
    
#define END_WND_NOTIFY_MAP() \
    break;\
    }\
    return CNotifyPump::NotifyPump(msg); \
}

#define BEGIN_WND_NOTIFY_MAP_DECLARE(theClass) \
public: \
    void Notify(TNotifyUI& msg); 



/////////////////////////////////////////////////////////////////////////////////////
class IHandlerMsg
{
public:
    virtual BOOL Handler(TNotifyUI& msg) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////
class ControlMger
{
public:

    static LPCTSTR GetControlText(CControlUI* ctlui)
    {
        if (ctlui){
            ctlui->GetText().GetData();
        }
    }

    static void SetControlText(CControlUI* ctlui, LPCTSTR text)
    {
        if (ctlui){
            ctlui->SetText(text);
        }
    }

    static void SetControlVisible(CControlUI* ctlui, bool visible)
    {
        if (ctlui){
            ctlui->SetVisible(visible);
        }
    }

    static void SetControlColor(CControlUI* ctlui, LPCTSTR textcolor)
    {
        if (ctlui){
            ctlui->SetAttribute(_T("textcolor"), textcolor);
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////
//
//
// constrol class name and interface name

// UIActiveX
extern const TCHAR* const kUIActiveXClassName;// = _T("ActiveXUI");
extern const TCHAR* const kUIActiveXInterfaceName;// = _T("ActiveX");

// ComboUI
extern const TCHAR* const kComboUIClassName;// = _T("ComboUI");
extern const TCHAR* const kComboUIInterfaceName;// = _T("Combo");

// LabelUI
extern const TCHAR* const kLabelUIClassName;// = _T("LabelUI");
extern const TCHAR* const kLabelUIInterfaceName;// = _T("Label");


// ButtonUI
extern const TCHAR* const kButtonUIClassName;// = _T("ButtonUI");
extern const TCHAR* const kButtonUIInterfaceName;// = _T("Button");

// OptionUI
extern const TCHAR* const kOptionUIClassName;// = _T("OptionUI");
extern const TCHAR* const kOptionUIInterfaceName;// = _T("Option");

// TextUI
extern const TCHAR* const kTextUIClassName;// = _T("TextUI");
extern const TCHAR* const kTextUIInterfaceName;// = _T("Text");

// ProgressUI
extern const TCHAR* const kProgressUIClassName;// = _T("ProgressUI");
extern const TCHAR* const kProgressUIInterfaceName;// = _T("Progress");

// SliderUI
extern const TCHAR* const kSliderUIClassName;// = _T("SliderUI");
extern const TCHAR* const kSliderUIInterfaceName;// = _T("Slider");

// EditUI
extern const TCHAR* const kEditUIClassName;// = _T("EditUI");
extern const TCHAR* const kEditUIInterfaceName;// = _T("Edit");

// IEditUI
extern const TCHAR* const kIEditUIInterfaceName;// = _T("Edit");

// ScrollBarUI
extern const TCHAR* const kScrollBarUIClassName;// = _T("ScrollBarUI");
extern const TCHAR* const kScrollBarUIInterfaceName;// = _T("ScrollBar");

// ContainerUI
extern const TCHAR* const kContainerUIClassName;// = _T("ContainerUI");
extern const TCHAR* const kContainerUIInterfaceName;// = _T("Container");

// IContainerUI
extern const TCHAR* const kIContainerUIInterfaceName;// = _T("IContainer");

// VerticalLayoutUI
extern const TCHAR* const kVerticalLayoutUIClassName;// = _T("VerticalLayoutUI");
extern const TCHAR* const kVerticalLayoutUIInterfaceName;// = _T("VerticalLayout");

// HorizontalLayoutUI
extern const TCHAR* const kHorizontalLayoutUIClassName;// = _T("HorizontalLayoutUI");
extern const TCHAR* const kHorizontalLayoutUIInterfaceName;// = _T("HorizontalLayout");

// TileLayoutUI
extern const TCHAR* const kTileLayoutUIClassName;// = _T("TileLayoutUI");
extern const TCHAR* const kTileLayoutUIInterfaceName;// = _T("TileLayout");

// DialogLayoutUI
extern const TCHAR* const kDialogLayoutUIClassName;// = _T("DialogLayoutUI");
extern const TCHAR* const kDialogLayoutUIInterfaceName;// = _T("DialogLayout");

// TabLayoutUI
extern const TCHAR* const kTabLayoutUIClassName;// = _T("TabLayoutUI");
extern const TCHAR* const kTabLayoutUIInterfaceName;// = _T("TabLayout");

// ControlUI
extern const TCHAR* const kControlUIClassName;// = _T("ControlUI");
extern const TCHAR* const kControlUIInterfaceName;// = _T("Control");

// ListUI
extern const TCHAR* const kListUIClassName;// = _T("ListUI");
extern const TCHAR* const kListUIInterfaceName;// = _T("List");

// IListUI
extern const TCHAR* const kIListUIInterfaceName;// = _T("IList");

// IListOwnerUI
extern const TCHAR* const kIListOwnerUIInterfaceName;// = _T("IListOwner");

// ListHeaderUI
extern const TCHAR* const kListHeaderUIClassName;// = _T("ListHeaderUI");
extern const TCHAR* const kListHeaderUIInterfaceName;// = _T("ListHeader");

// ListHeaderItemUI
extern const TCHAR* const kListHeaderItemUIClassName;// = _T("ListHeaderItemUI");
extern const TCHAR* const kListHeaderItemUIInterfaceName;// = _T("ListHeaderItem");

// ListElementUI
extern const TCHAR* const kListElementUIClassName;// = _T("ListElementUI");
extern const TCHAR* const kListElementUIInterfaceName;// = _T("ListElement");

// IListItemUI
extern const TCHAR* const kIListItemUIInterfaceName;// = _T("ListItem");

// ListLabelElementUI
extern const TCHAR* const kListLabelElementUIClassName;// = _T("ListLabelElementUI");
extern const TCHAR* const kListLabelElementUIInterfaceName;// = _T("ListLabelElement");

// ListTextElementUI
extern const TCHAR* const kListTextElementUIClassName;// = _T("ListTextElementUI");
extern const TCHAR* const kListTextElementUIInterfaceName;// = _T("ListTextElement");

// ListExpandElementUI
//extern const TCHAR* const kListExpandElementUIClassName;// = _T("ListExpandElementUI");
//extern const TCHAR* const kListExpandElementUIInterfaceName;// = _T("ListExpandElement");

// ListContainerElementUI
extern const TCHAR* const kListContainerElementUIClassName;// = _T("ListContainerElementUI");
extern const TCHAR* const kListContainerElementUIInterfaceName;// = _T("ListContainerElement");

// RichEditUI
extern const TCHAR* const kRichEditUIClassName;// = _T("RichEditUI");
extern const TCHAR* const kRichEditUIInterfaceName;// = _T("RichEdit");

/////////////////////////////////////////////////////////////////////////////////////

}; // namespace DuiLib

#endif // _UICRACK_H_