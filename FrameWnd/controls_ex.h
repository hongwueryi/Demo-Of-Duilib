#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

class CButtonGifUI : public CButtonUI
	{
	public:	
		CButtonGifUI();
		~CButtonGifUI();

		LPCTSTR GetClass() const
		{
			return _T("ButtonGifUI");
		}


		LPVOID GetInterface( LPCTSTR pstrName )
		{
			if( _tcscmp(pstrName, _T("ButtonGif")) == 0 ) 
				return static_cast<CButtonGifUI*>(this);

			return CControlUI::GetInterface(pstrName);
		}

		void SetNormalGifFile(LPCTSTR pstrName);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		virtual void DoEvent(TEventUI& event);
		virtual void SetVisible(bool bVisible = true);//设置控件可视性
		virtual void PaintStatusImage(HDC hDC);

	protected:
		enum
		{
			GIF_TIMER_ID = 15
		};

		bool m_isUpdateTime;
		CGifHandler* m_pGif;
		int m_nPreUpdateDelay;

	};
