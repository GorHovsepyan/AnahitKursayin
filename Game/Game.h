#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "stdafx.h"
#include "resource.h"
#include "Protoblast.h"
#include "Clock.h"
#include <vector>
#include <afxdb.h>

/* Խաղի տրամաբանության կլաս, որը ժառանգում է Windows հավելվածի կլասից */
class CGameApp : public CWinApp
{
public:
	CGameApp();		// Կոնստրուկտոր
	~CGameApp();	// Դեստրուկտոր

	BOOL InitInstance();	// Մեթոդ, որը սկսում է պատուհանի իнициалիզացիան
	int ExitInstance();		// Մեթոդ, որը դուրս է գալիս
	void OnSaveToDb();
	void OnOpenFromDb();
	CSize GetFieldSize();	// Մեթոդ, որը վերադարձնում է խաղային դաշտի չափերը
	void LeftButtonDoubleClick(UINT, CPoint);	// Մեթոդ, որը պատասխանատու է ձախ մկնիկի կրկնակի սեղմման համար
	void LeftButtonDown(UINT, CPoint);	// Մեթոդ, որը պատասխանատու է ձախ մկնիկի սեղմման համար
	void RightButtonUp(UINT, CPoint);	// Մեթոդ, որը պատասխանատու է աջ մկնիկի ազատման համար
	void CreateNewGame();				// Մեթոդ, որը ստեղծում է նոր խաղ
	void RenderField(CMemoryDC&, CRect);	// Մեթոդ, որը նկարում է խաղային դաշտը
	void NcMouseMove();				// Մեթոդ, որը պատասխանատու է մկնիկի շարժման համար խաղային դաշտից դուրս
	void MouseMove(UINT, CPoint);	// Մեթոդ, որը պատասխանատու է մկնիկի շարժման համար խաղային դաշտում
	void KeyDown(UINT, UINT, UINT);	// Մեթոդ, որը պատասխանատու է կոճակի սեղմման համար
	void Tick();					// Մեթոդ, որը ցույց է տալիս ժամանակի անցումը
	int GetProtoblastCount();		// Մեթոդ, որը վերադարձնում է կենդանի կետերի քանակը
	int GetFPS();					// Մեթոդ, որը վերադարձնում է վայրկյանում նկարահանման հաճախությունը

	afx_msg void OnEvolve(UINT);	// Մեթոդ, որը պատասխանատու է զարգացման արագության ընտրության համար, որտեղ-то վերին մենյուում
	afx_msg void OnAppAbout();		// Մեթոդ, որը պատասխանատու է "Մասին" ընտրության համար վերին մենյուում
	afx_msg void OnOpenGame();		// Մեթոդ, որը պատասխանատու է "Բացել խաղը" ընտրության համար վերին մենյուում
	afx_msg void OnSaveGame();		// Մեթոդ, որը պատասխանատու է "Պահպանել խաղը որպես" ընտրության համար վերին մենյուում
	afx_msg void OnNewGame();		// Մեթոդ, որը պատասխանատու է "Նոր խաղ" ընտրության համար վերին մենյուում

	DECLARE_MESSAGE_MAP() // Կլասի վերջի մակրո, որը հայտարարում է զետեղված հաղորդագրությունները

private:
	bool ConnectToDatabase(CDatabase& database);
	void CGameApp::DeserializeGameData(const CString& gameData);
	static const int m_fieldHeight = 69;	// Խաղային դաշտի բարձրությունը
	static const int m_fieldWidth = 56;		// Խաղային դաշտի լայնությունը
	static const int m_fps = 25;			// Վայրկյանում նկարահանման հաճախությունը
	void SaveGameToDatabase(const CString& gameID, const CString& gameData);
	CString LoadGameFromDatabase(const CString& gameID);
	CString SerializeGameData();
	std::vector < std::vector < CProtoblast* > > m_field;	// Խաղային դաշտի վրա գտնվող կետերի երկու չափանիշների զանգված
	CPoint m_oldMousePosition;	// Մկնիկի նախկին դիրքը
	CPoint m_hoverCell;		// Ընդգծված բջիջ
	CPoint m_offset;		// Դաշտի տեղափոխում մանևրում
	CClock m_clock;			// Զարգացման ռեժիմի ինդիկատորը
	int m_evolveTime;		// Զարգացումների միջակայքի ժամանակը
	int m_tickCount;		// Վերջին զարգացման պահից անցած ժամանակը
	bool m_pause;			// Խաղը pausա՞ է, թե ոչ

	bool MousePositionToXY(CPoint, CPoint&);	// Մեթոդ, որը փոխում է մկնիկի կոորդինատները դաշտի բջիջների կոորդինատներին
	void FreeField();		// Մեթոդ, որը ազատում է խաղային դաշտը
	void Evolve();			// Զարգացման/հեղափոխության մեթոդ
};

extern CGameApp theApp; 	// Հայտարարում ենք դասի օբյեկտը ամենուրեք!
