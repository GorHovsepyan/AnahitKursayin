#pragma once

#include "ChildView.h"

/* Բուն պատուհանի կլաս, որը ժառանգում է հիմնական պատուհանի կլասից */
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();	// Դեֆոլտ կոնստրուկտոր
	~CMainFrame();	// Դեստրուկտոր

	BOOL PreCreateWindow(CREATESTRUCT&);	// Պատուհանի ստեղծման նախապատրաստման մեթոդ
	BOOL OnCmdMsg(UINT, int, void*, AFX_CMDHANDLERINFO*);	// Հաղորդագրությունների ստացման մեթոդ

private:
	CStatusBar m_wndStatusBar;	// Ստատուս-բար
	CChildView m_wndView;		// Տեսք
	void OnShowDb(); // Method to handle showing database data

	afx_msg void OnTimer(UINT);				// Զետեղված հաղորդագրության ժամանակացույցի տիկի մեթոդ
	afx_msg int OnCreate(LPCREATESTRUCT);	// Զետեղված հաղորդագրության ստեղծման մեթոդ
	afx_msg void OnSetFocus(CWnd*);		// Զետեղված հաղորդագրության ֆոկուսի ստացման մեթոդ

	DECLARE_MESSAGE_MAP()			// Մակրո, որը վերջացնում է հաղորդագրությունների զետեղման հայտարարումը
		DECLARE_DYNAMIC(CMainFrame)		// Մակրո, որը թույլ է տալիս ստանալ ինֆորմացիա կլասի մասին ծրագրի աշխատանքի ընթացքում
};
