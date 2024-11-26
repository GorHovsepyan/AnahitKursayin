#include "stdafx.h"
#include "Game.h"
#include "ChildView.h"

CChildView::CChildView()	// դիֆոլթ կանստրուկտոր
{
}

CChildView::~CChildView()	// Դեստրուկտոր
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)	// Վերադարձված հաղորդագրությունների հայտարարության սկիզբ
	ON_WM_PAINT()			// Միջավայրի նկարելու հաղորդագրություն
	ON_WM_ERASEBKGND()		// Նկարելուց առաջ ֆոնի մաքրման անհրաժեշտության հաղորդագրություն
	ON_WM_LBUTTONDBLCLK()	// Աջ կոճակի կրկնակի սեղմման հաղորդագրություն
	ON_WM_MOUSEMOVE()		// Մուտքի միջավայրի տարածքում մկնային շարժման հաղորդագրություն
	ON_WM_LBUTTONDOWN()		// Աջ կոճակի սեղմման հաղորդագրություն
	ON_WM_RBUTTONUP()		// Աջ կոճակի բաց թողնելու հաղորդագրություն
	ON_WM_NCMOUSEMOVE()		// Միջավայրի տարածքից դուրս մկնային շարժման հաղորդագրություն
	ON_WM_KEYDOWN()			// Սեղմված ստեղնի հաղորդագրություն
END_MESSAGE_MAP()			// Վերադարձված հաղորդագրությունների հայտարարության վերջ

void CChildView::OnNcMouseMove(UINT hitTest, CPoint point)	
{
	theApp.NcMouseMove();	// Հսկողությունը փոխանցվում է խաղի տրամաբանության օբյեկտին
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 	// Տեսարանի ստեղծման նախապատրաստման մեթոդը
{
	if (!CWnd::PreCreateWindow(cs))	// Եթե ծնող դասը չի կարող պատրաստել պատուհանը ստեղծման համար
		return FALSE;	// Այն դեպքում ոչինչ ստեղծելու չէ

	cs.dwExStyle |= WS_EX_CLIENTEDGE;	// Պատուհանը ունի ներքև թափվող եզրեր
	cs.style &= ~WS_BORDER;	// Պատուհանը ունի սահման
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL); // Մենք ուզում ենք սովորական մարդկային պատուհան

	return TRUE;	// Ամեն բան հաջողվեց, կարելի է ստեղծել պատուհանը
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)	// Տեսարանի ֆոնի մաքրելու անհրաժեշտության մեթոդը
{
	return FALSE;	// Ֆոնի մաքրում չի պահանջվում
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)	// Ստեղնի սեղմման մեթոդը
{
	theApp.KeyDown(nChar, nRepCnt, nFlags);	// Հսկողությունը փոխանցում ենք խաղի տրամաբանության օբյեկտին
}

void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)	// Աջ կոճակի կրկնակի սեղմման բռնում է մեթոդը
{
	theApp.LeftButtonDoubleClick(nFlags, point);	// Հսկողությունը փոխանցվում է խաղի տրամաբանության օբյեկտին
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)	// Տեսարանի տարածքում մկնային շարժման բռնում է մեթոդը
{
	theApp.MouseMove(nFlags, point);	 
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)	// Աջ կոճակի սեղմման բռնում է մեթոդը
{
	theApp.LeftButtonDown(nFlags, point);	
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)	// Աջ կոճակի բաց թողնելու բռնում է մեթոդը
{
	theApp.RightButtonUp(nFlags, point);	
}

void CChildView::OnPaint() 	// Տեսարանում նկարելու մեթոդը
{
	CPaintDC dc(this);	
	CMemoryDC pDC(&dc);	
	CRect rect;	// ուղղանկյուն

	GetClientRect(&rect);	// տեսքի չափսերն ենք ստանում
	theApp.RenderField(pDC, rect);	//Վերահսկողությունը փոխանցել խաղի տրամաբանական օբյեկտին
}
