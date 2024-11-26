#include "stdafx.h"
#include "Game.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)	// Մակրո, որը թույլ է տալիս ստանալ ինֆորմացիա կլասի մասին ծրագրի աշխատանքի ընթացքում

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)	// Մակրո, որը սկսում է զետեղված հաղորդագրությունների հայտարարումը
	ON_WM_CREATE()		// Զետեղված հաղորդագրության թռուցիկի ստեղծումը
	ON_WM_SETFOCUS()	// Զետեղված հաղորդագրության ֆոկուսի ստացումը
	ON_WM_TIMER()		// Զետեղված հաղորդագրության ժամանակացույցի տիկը
END_MESSAGE_MAP()		// Մակրո, որը վերջացնում է հաղորդագրությունների զետեղման հայտարարումը

static UINT indicators[] = { ID_SEPARATOR };	// Ստատուս-բարի տարրերի զանգված

CMainFrame::CMainFrame()	// Դեֆոլտ կոնստրուկտոր
{
}

CMainFrame::~CMainFrame()	// Դեստրուկտոր
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)	// Զետեղված հաղորդագրության ստեղծման մեթոդ
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)	// Եթե պատուհանը ստեղծել չի հաջողվում
		return -1;	// Ամեն ինչ վատ է

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))	// Եթե տեսքը ստեղծել չի հաջողվում
		return -1;	// Ամեն ինչ վատ է

	if (!m_wndStatusBar.Create(this))	// Եթե ստատուս-բարը ստեղծել չի հաջողվում
		return -1;	// Ամեն ինչ վատ է

	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));	// Ստատուս-բարի ինդիկատորների սահմանում
	SetTimer(1, 1000 / theApp.GetFPS(), NULL);	// Ժամանակացույցի սահմանում

	return 0;	// Ամեն ինչ լավ է
}

void CMainFrame::OnTimer(UINT nIDEvent)	// Զետեղված հաղորդագրության ժամանակացույցի տիկի մեթոդ
{
	theApp.Tick();	// Տեսանելիության օբյեկտին փոխանցում
	m_wndView.RedrawWindow();	// Նշում տեսքը նորից նկարելու

	CString text;	// Տեքստ ստատուս-բարի համար

	text.Format(_T("Խաղային դաշտում կենդանի կետերի քանակը: %d"), theApp.GetProtoblastCount());	// Տեղեկատվությունը ձևավորում
	m_wndStatusBar.SetPaneText(0, text);	// Բավելում ստատուս-բարում
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)	// Պատուհանի ստեղծման նախապատրաստման մեթոդ
{
	if (!CFrameWnd::PreCreateWindow(cs))	// Եթե ծնողական կլասը չի կարողանում նախապատրաստվել
		return FALSE;	// Արժե դուրս գալ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	// Պատուհանի ներքևի եզր
	cs.lpszClass = AfxRegisterWndClass(0);	// Կլասը

	return TRUE;	// Ամեն ինչ լավ է, կարելի է ստեղծել պատուհանը
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)	// Զետեղված հաղորդագրության ֆոկուսի ստացման մեթոդ
{
	m_wndView.SetFocus();	// Տեսքի վրա կենտրոնացվում է
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)	// Հաղորդագրությունների ստացման մեթոդ
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))	// Եթե տեսքը վերցրել է հաղորդագրությունը
		return TRUE;	// Անկախությունը

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);	// Այլ դեպքում թող ծնողական կլասը զբաղվի հաղորդագրություններով
}
