 #include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Game.h"
#include "MainFrm.h"
#include "Protoblast.h"
#include "AboutDialog.h"
#include <fstream>
BEGIN_MESSAGE_MAP(CGameApp, CWinApp)	// Ծրագրավորման հաղորդագրությունների արգելակման մակրո
	ON_COMMAND_RANGE(ID_EVOLVE_1_SECOND, ID_EVOLVE_HAND, &CGameApp::OnEvolve)	// Էվոլուցիայի արագության ընտրության հաղորդագրություններ
	ON_COMMAND(ID_APP_ABOUT, &CGameApp::OnAppAbout)		// Հաղորդագրություն "Ամբողջության մասին" բաժին դիտելու հետաքրքրության համար
	ON_COMMAND(ID_NEW_GAME, &CGameApp::OnNewGame)		// Ովքե՞ր ուզում են սկսել նոր խաղ - ահա հաղորդագրությունը
	ON_COMMAND(ID_OPEN_GAME, &CGameApp::OnOpenGame)		// "Բացել խաղ" հաղորդագրությունը
	ON_COMMAND(ID_SAVE_GAME, &CGameApp::OnSaveGame)		// "Հասարակություն պահպանել" հաղորդագրությունը
END_MESSAGE_MAP()	// Ծրագրավորման հաղորդագրությունների արգելակման մակրոյի ավարտ

CGameApp::CGameApp()	// Կոնստրուկտոր
{
	CreateNewGame();	// Ստեղծում ենք նոր խաղ

	m_pause = false;	// Հանում ենք խաղը կանգառից
	m_hoverCell = CPoint(-1, -1);	// Ոչ մի bjij չի նշված
	m_offset = CPoint(0, 0);	// Արտադրական գործը չպետք է տեղափոխվի
}

CGameApp::~CGameApp()	// Դեստրուկտոր
{
	FreeField();	// Հեռացնում ենք խաղային դաշտը հիշողությունից
}

CGameApp theApp;	// Խաղային դասի օբյեկտ

void CGameApp::OnEvolve(UINT id)	// Մեթոդ, որը հրավիրվում է զարկերակների մեջից մեկի վրա սեղմելու ժամանակ, վերևի մենյուում
{
	CheckMenuRadioItem(GetMenu(*m_pMainWnd), ID_EVOLVE_1_SECOND, ID_EVOLVE_HAND, id, MF_BYCOMMAND);	// Նշում ենք, որ ընտրված կետը վերևի մենյուի ցուցակման մեջ

	switch (id)	// Ընտրության համաձայն
	{
	case ID_EVOLVE_1_SECOND:	// Ամեն վարկյան
		m_evolveTime = 1;	// Այս պահին մեկ վարկյան
		break;

	case ID_EVOLVE_3_SECONDS:	// Ամեն երեք վարկյան
		m_evolveTime = 3;	// Երեք վարկյան
		break;

	case ID_EVOLVE_10_SECONDS:	// Ամեն տասը վարկյան
		m_evolveTime = 10;	// Տասը վարկյան
		break;

	case ID_EVOLVE_42_MINUTES:	// Ամեն քառասուն երկու րոպե
		m_evolveTime = 42 * 60;	// Քառասուն երկու բազմապատկել վաթսուն վարկյանով
		break;

	default:
		m_evolveTime = 0;	// Ձեռնարկի ռեժիմ
	}

	m_evolveTime *= m_fps;	// Բազմապատկում ենք վարկյանների թվով
	m_tickCount = 0;	// Վերջին эволюции պահից ոչ մի ժամանակ չի անցել
	m_clock.SetTime(m_evolveTime);	// Բացատրություն ենք տալիս, որքան հաճախ է պտտվում
}

BOOL CGameApp::InitInstance()	
{
	INITCOMMONCONTROLSEX initCtrls;	// Կառավարման պատրաստություն

	initCtrls.dwSize = sizeof(initCtrls);	
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&initCtrls);	// Պատրաստ ենք
	CWinApp::InitInstance();	// Թողնում ենք ծնողին նույնպես պատրաստվել
	EnableTaskbarInteraction(FALSE);	// Աշխարհագրական ժամանակի կարգավորումներ
	//	SetRegistryKey(_T(""));
	//	AfxInitRichEdit2();
	CMainFrame* pFrame = new CMainFrame;	// Ստեղծում ենք պատուհան

	if (!pFrame)	// Եթե պատուհանը չի ստեղծվել
		return FALSE;	// Այն դեպքում խաղալու ոչինչ չկա

	m_pMainWnd = pFrame;	// Այլապես սա մեր գլխավոր պատուհան
	pFrame->LoadFrame(IDR_MAINFRAME);	// Բեռնարկում ենք վերին մենյուն
	pFrame->ShowWindow(SW_SHOW);	// Ցուցադրության ռեժիմ
	pFrame->UpdateWindow();	// Թարմացնում ենք պատուհանը

	OnEvolve(ID_EVOLVE_3_SECONDS);	// Պատրաստում ենք эволюций հաճախությունը

	return TRUE;	// Բոլոր դեպքերում, կարելի է խաղալ!
}

void CGameApp::CreateNewGame()	// Նոր խաղի ստեղծման մեթոդ
{
	FreeField();	// Եթե մինչև այժմ խաղացել ենք, ապա կարող ենք ինչ-որ բան հեռացնել

	for (size_t i = 0; i < m_fieldHeight; ++i)	// Սկսելով դաշտի բարձրությունից
	{
		m_field.push_back(std::vector < CProtoblast* >());	// Ստեղծում ենք դաշտի շարքի զանգված

		for (size_t j = 0; j < m_fieldWidth; j++)	// Եվ շարունակելով դաշտի լայնությամբ
			m_field[i].push_back(new CProtoblast());	// Ստեղծում ենք խցիկ
	}
}

void CGameApp::FreeField()	// Դաշտի հեռացման մեթոդ
{
	for (size_t i = 0; i < m_field.size(); ++i)	// Ստեղծված շարքերի քանակի վրա
	{
		for (size_t j = 0; j < m_field[i].size(); ++j)	// Շարքի ամբողջության վրա
			delete m_field[i][j];	// Եվ հեռացնում ենք յուրաքանչյուր խցիկ

		m_field[i].clear();	// Հեռացնում ենք դաշտի շարքը
	}

	m_field.clear();	// Հեռացնում ենք շարքերի զանգվածը
}

void CGameApp::LeftButtonDoubleClick(UINT nFlags, CPoint point)	// Ոչ կրծողից ձախ կոճակի կրկնակի սեղմման մեթոդ
{
	CPoint cell;	// Նշենք, որ այս կոորդինատում դաշտին սեղմել ենք

	if (MousePositionToXY(point, cell))	// Եթե ստացվել է դաշտին սեղմել
		m_field[cell.x][cell.y]->Click();	// Ապա ակտիվացնում ենք խցիկը
}

void CGameApp::LeftButtonDown(UINT nFlags, CPoint point)	// Ձախ կոճակի սեղմման մեթոդ
{
	m_oldMousePosition = CPoint(-1, -1);	// Վերացնում ենք վերջին կոճակի դիրքը
}

void CGameApp::RightButtonUp(UINT nFlags, CPoint point)	// Աջ կոճակի թողնելու մեթոդ
{
	CPoint cell;	// Նշենք, որ այստեղ սեղմել ենք

	if (MousePositionToXY(point, cell))	// Եթե ստացվել է դաշտի մեջ
		m_field[cell.x][cell.y]->Click(false);	// Րացի կենդանի խցիկ

	MouseMove(0, point);	// Հավանաբար, սպանված խցիկը պետք է ընդգծել
}

void CGameApp::NcMouseMove()	// Կուրսորի մեթոդ, երբ դուրս է եկել խաղային դաշտից
{
	if (m_hoverCell == CPoint(-1, -1))	// Եթե ոչ մի խցիկ չի ընտրված
		return;	// Այս դեպքում իրականում ոչինչ անել չի կարող

	m_field[m_hoverCell.x][m_hoverCell.y]->Unhover();	// Այլապես, չընդգծենք խցիկը
	m_hoverCell = CPoint(-1, -1);	// Եվ հիմա որոշակիորեն ոչինչ չընդգծենք
}

void CGameApp::MouseMove(UINT nFlags, CPoint point)	// Կուրսորի շարժման մեթոդ խաղային դաշտում
{
	if (m_pause)	// Եթե խաղը կանգնած է
		return;	// Այս դեպքում անել չի կարող

	if (nFlags == MK_LBUTTON)	// Եթե շարժվում ենք ձախ կոճակի հետ
	{
		if (m_oldMousePosition != CPoint(-1, -1))	// Եթե մկնիկը փոքր-ինչ շարժվել է, տարնելով դաշտը
			m_offset += point - m_oldMousePosition;	// Ապա տանում ենք դաշտը մկնիկի հետ

		m_oldMousePosition = point;	// Եվ հիմա սա մկնիկի արդիական դիրքը
	}

	CPoint cell;	// Հնարավոր է, խցիկը հարվածել ենք դաշտում

	if (MousePositionToXY(point, cell))	// Եթե խցիկին ենք հասցրել, երբ մկնիկի ցույցը շարժվել է
	{
		if (m_hoverCell != cell && m_hoverCell != CPoint(-1, -1))	// Եթե խցիկը չի ընտրված, բայց կա այլ ընտրված խցիկ
			m_field[m_hoverCell.x][m_hoverCell.y]->Unhover();	// Այժմ փակում ենք մյուս ընտրված խցիկը

		m_hoverCell = cell;	// Եվ սա ակտիվացնում ենք
		m_field[cell.x][cell.y]->Hover();	// Ակտիվացրու, ասում եմ. :)
	}
	else	// Եթե խցիկին չենք հասցրել
		if (m_hoverCell != CPoint(-1, -1))	// Եթե կան ընտրված խցիկներ
		{
			m_field[m_hoverCell.x][m_hoverCell.y]->Unhover();	// Չընդգծենք ընտրվածը
			m_hoverCell = CPoint(-1, -1);	// Եվ նշենք, որ ոչինչ չի ընտրված
		}
}
void CGameApp::Evolve()	// Էվոլյուցիայի-ռևոլյուցիայի մեթոդ
{
	int movX[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };	// Թեքության հարևանները X առանցքում
	int movY[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };	// Թեքության հարևանները Y առանցքում

	std::vector < std::vector < bool > > tempField(m_fieldHeight, std::vector < bool >(m_fieldWidth, false));	// Ստեղծում ենք դատարկ դաշտ

	for (int i = 0; i < m_fieldHeight; ++i)	// Շարքի միջոցով անցնում ենք բոլոր շարքերի վրա
		for (int j = 0; j < m_fieldWidth; ++j)	// Եվ առանձնացված յուրաքանչյուր շարքի վրա
		{
			tempField[i][j] = m_field[i][j]->IsLive();	// Թե՞ խցիկը կենդանի է

			int count = 0;	// Հարևանների քանակը

			for (int k = 0; k < 8; ++k)	// Հարևանների վրա անցնում ենք
			{
				int x = i + movX[k];	// Հարևանի կոորդինատները X առանցքում
				int y = j + movY[k];	// Հարևանի կոորդինատները Y առանցքում

				if (x < 0 || y < 0 || x >= m_fieldHeight || y >= m_fieldWidth)	// Եթե սա հարևան է զուգահեռ աշխարհից
					continue;	// Այդ դեպքում ավելի լավ է չկապվել

				if (m_field[x][y]->IsLive())	// Եթե հարևանը կենդանի է
					++count;	// Ապա ավելացնում ենք կենդանի հարևանների հաշվին
			}

			if (m_field[i][j]->IsLive())	// Եթե ընթացիկ խցիկը կենդանի է
			{
				if (count < 2 || count > 3)	// Եվ հարևանների քանակը չի նորմալ
					tempField[i][j] = false;	// Այս դեպքում մահանալ
			}
			else	// Այլապես ընթացիկ խցիկը կենդանի չէ
			{
				if (count == 3)	// Բայց հարևանների քանակը թույլ է տալիս
					tempField[i][j] = true;	// Խցիկը վերականգնվի
			}
		}

	for (int i = 0; i < m_fieldHeight; ++i)	// Շարքի միջոցով անցնում ենք բոլոր շարքերի վրա
		for (int j = 0; j < m_fieldWidth; ++j)	// Յուրաքանչյուր շարքում
			if (tempField[i][j] ^ m_field[i][j]->IsLive())	// Եթե վիճակների մեջ տարբերություն կա
			{
				if (tempField[i][j])	// Եթե խցիկը ապրելու որոշում ունի
					m_field[i][j]->Click();	// Այն կենդանի կլինի
				else	// Այլապես
					m_field[i][j]->Click(false);	// Այն մահանում է
			}
}

void CGameApp::Tick()	// Տիկի մեթոդ
{
	if (m_pause)	// Եթե դադար
		return;	// Այդ դեպքում ոչինչ անել չի կարող

	++m_tickCount;	// Թվիչը ավելացնում ենք վերջին էվոլյուցիայից

	for (int i = 0; i < m_fieldHeight; ++i)	// Շարքի միջոցով անցնում ենք բոլոր շարքերի վրա
		for (int j = 0; j < m_fieldWidth; ++j)	// Եվ յուրաքանչյուր շարքից առանձնացված
			m_field[i][j]->Tick();	// Տիկը փոխանցում ենք խցիկներին

	m_clock.Tick();	// Ժամերը նույնպես տիկ են անում

	if (m_evolveTime && m_tickCount % m_evolveTime == 0)	// Եթե եկել է էվոլյուցիայի ժամանակը
		Evolve();	// Այնպես որ, պետք է լինեն էվոլյուցիաներ
}

void CGameApp::RenderField(CMemoryDC& dc, CRect screen)	// Խաղային դաշտի գծագրի մեթոդ
{
	CSize protoblastSize(m_field[0][0]->GetSize());	// Ստանում ենք խցիկի չափերը

	for (int i = 0; i < m_fieldHeight; ++i)	// Շարքի միջոցով անցնում ենք բոլոր շարքերի վրա
		for (int j = 0; j < m_fieldWidth; ++j)	// Եվ յուրաքանչյուր շարքում
			m_field[i][j]->Render(dc, CPoint(j * protoblastSize.cx, i * protoblastSize.cy) + m_offset);	// Գծագրում ենք խցիկները

	int deltaLeft = m_offset.x;	// Ձախ կողմի ազատ տարածքը
	int deltaRight = screen.Width() - m_offset.x - protoblastSize.cx;	// Ցուցակի աջ կողմը
	int deltaTop = m_offset.y;	// Վերևում
	int deltaBottom = screen.Height() - m_offset.y - protoblastSize.cy;	// Եվ ներքևում
	CBitmap bmp;	// Դաշտի նկար (մանրամաս)
	CDC dcMemory;	// Մնացած տարածքի նկարելու կոնտեքստ

	bmp.LoadBitmap(IDB_GRASS);	// Բեռնման մարգագետին
	dcMemory.CreateCompatibleDC(dc);	// Ստեղծում ենք համատեղելի կոնտեքստ
	dcMemory.SelectObject(&bmp);	// Ընտրում ենք նկարը

	//if (deltaTop > 0)	// Եթե վերևում կանաչ տարածք չի բավականացնում, ապա լրացնում ենք
	//	for (int i = 1; i < deltaTop / protoblastSize.cy + 2; ++i)
	//		for (int j = -1; j < screen.Width() / protoblastSize.cx + 2; ++j)
	//		{
	//			int x = (m_offset.x % protoblastSize.cx) + protoblastSize.cx * j;	// Մարգագետնի կոորդինատները X առանցքում
	//			int y = m_offset.y - protoblastSize.cy * i;	// Մարգագետնի կոորդինատները Y առանցքում

	//			dc->BitBlt(x, y, protoblastSize.cx, protoblastSize.cy, &dcMemory, 0, 0, SRCCOPY);	// Նկարելու մարգագետինը
	//		}

	//if (deltaBottom > 0)	// Եթե ներքևում կանաչ տարածք չի բավականացնում, ապա կրկին լրացնում ենք
	//	for (int i = 0; i < deltaBottom / protoblastSize.cy; ++i)
	//		for (int j = -1; j < screen.Width() / protoblastSize.cx + 2; ++j)
	//		{
	//			int x = (m_offset.x % protoblastSize.cx) + protoblastSize.cx * j;
	//			int y = m_offset.y + protoblastSize.cy * (m_fieldHeight + i);

	//			dc->BitBlt(x, y, protoblastSize.cx, protoblastSize.cy, &dcMemory, 0, 0, SRCCOPY);
	//		}

	//if (deltaLeft > 0)	// Եթե ձախ կողմում ազատ տարածք կա, ապա նկարենք մարգագետին
	//	for (int i = 0; i < m_fieldHeight; ++i)
	//		for (int j = 1; j < deltaLeft / protoblastSize.cx + 2; ++j)
	//		{
	//			int x = m_offset.x - protoblastSize.cx * j;
	//			int y = m_offset.y + protoblastSize.cy * i;

	//			dc->BitBlt(x, y, protoblastSize.cx, protoblastSize.cy, &dcMemory, 0, 0, SRCCOPY);
	//		}

	//if (deltaRight > 0)	// Ցուցակի աջ կողմում ազատ տարածք կա? Նկարենք մարգագետին
	//	for (int i = 0; i < m_fieldHeight; ++i)
	//		for (int j = 0; j < deltaRight / protoblastSize.cx; ++j)
	//		{
	//			int x = m_offset.x + (m_fieldWidth + j) * protoblastSize.cx;
	//			int y = m_offset.y + protoblastSize.cy * i;

	//			dc->BitBlt(x, y, protoblastSize.cx, protoblastSize.cy, &dcMemory, 0, 0, SRCCOPY);
	//		}
	if (screen.Height() > 60 && screen.Width() > 60 && !m_pause)	// Если часы-индикатор влезают в окно
		m_clock.Render(dc, CPoint(screen.Width(), screen.Height()) - CPoint(10, 10) - CPoint(m_clock.GetWidth(), m_clock.GetHeight()));	// То и их рисуем
}
int CGameApp::GetProtoblastCount()	// Կենդանի խցիկների քանակը ստանալու մեթոդ
{
	int count = 0;	// Միայն ժամանակավոր հաշվող, թե ներկայում քանի կենդանի խցիկ կա դաշտում

	for (int i = 0; i < m_fieldHeight; ++i)	// Եվ մենք անցնում ենք բոլոր շարքերով
		for (int j = 0; j < m_fieldWidth; ++j)	// Յուրաքանչյուր շարքում անցնում ենք բոլոր խցիկներով
			if (m_field[i][j]->IsLive())	// Եվ եթե խցիկը կենդանի է
				++count;	// Այն դեպքում ավելացնում ենք հաշվում

	return count;	// Վերադարձնում ենք արդյունքը
}

CSize CGameApp::GetFieldSize()	// Դաշտի չափերը ստանալու մեթոդ
{
	return CSize(m_fieldWidth, m_fieldHeight);	// Ֆորմավորում ենք դաշտի չափը
}

int CGameApp::ExitInstance()	// Արտաքինում ելքի մեթոդ
{
	return CWinApp::ExitInstance();	// Հայրենի դասը նույնպես ուզում է դուրս գալ
}

int CGameApp::GetFPS()	// Կադրերի քանակը ստանալու մեթոդ
{
	return m_fps;	// Կադրերի քանակ
}

bool CGameApp::MousePositionToXY(CPoint position, CPoint& cell)	// Մկնիկի կուրսորի դիրքից խցիկի կոորդինատները ստանալու մեթոդ
{
	position -= m_offset;	// Հանում ենք սահմանը

	if (position.x < 0 || position.y < 0)	// Եթե մենք չենք դաշտում
		return false;	// Այն դեպքում անմիջապես ոչ է

	int y = position.x / m_field[0][0]->GetWidth();	// Այլապես Y առանցքի կոորդինատները
	int x = position.y / m_field[0][0]->GetHeight();	// Հետո X առանցքի

	if (x >= m_fieldHeight || y >= m_fieldWidth)	// Եթե դաշտը ավարտվեց
		return false;	// Այն դեպքում ևս ոչ է

	cell = CPoint(x, y);	// Այլապես ստանում ենք մկնիկի տակ գտնվող խցիկի կոորդինատները

	return true;	// Ամեն ինչ լավ է, տվյալները վավեր են
}

void CGameApp::OnAppAbout()	// "Ծրագրի մասին" մենյուի բացման մեթոդ
{
	m_pause = true;	// Վարում ենք paus 

	CAboutDlg aboutDlg;	// "Ծրագրի մասին" երկխոսություն

	aboutDlg.DoModal();	// Բացում ենք երկխոսությունը, վայելում ենք
	m_pause = false;	// Երկխոսությունը փակելուց հետո խաղը վերագործարկում ենք
}

void CGameApp::OnOpenGame()	// "Բացել խաղը" մենյուի բացման մեթոդ
{
	m_pause = true;	// Վարում ենք paus 

	CFileDialog dialog(TRUE, _T("*.life"), _T(""), 0, _T("games fil (*.life)|*.life|"));	// Ստեղծում ենք ֆայլի բացման երկխոսություն

	if (dialog.DoModal() == IDOK)	// Եթե OK ընտրել ենք
	{
		CreateNewGame();	// Այն դեպքում ստեղծում ենք նոր խաղ

		std::ifstream fin(dialog.GetPathName());	// Բացենք պահպանված խաղի ֆայլը
		int count;	// Ֆայլում կենդանի խցիկների քանակ

		fin >> count;	// Получаем из файла количество клеток

		for (int i = 0; i < count; ++i)	// 
		{
			int x, y;	// Խցիկի կոորդինատները դաշտում

			fin >> x >> y;	// Ընդունում ենք կոորդինատները

			if (x > 0 && y > 0 && x < m_fieldHeight && y < m_fieldWidth)	// Եթե խցիկը դաշտի ներսում է
				m_field[x][y]->Click();	// Այն կենդանի է դառնում
		}

		MessageBox(NULL, _T("game saved sucesfully!"), _T(""), MB_ICONINFORMATION);	// Խրախուսիչ հաղորդագրություն
		OnEvolve(ID_EVOLVE_HAND);	// Էվոլուցիայի ռեժիմ - ձեռքով
	}

	m_pause = false;	// Սպասումը ավարտվել է
}

void CGameApp::OnSaveGame()	// "Պահել խաղը որպես" մենյուի բացման մեթոդ
{
	if (GetProtoblastCount() == 0)	// Եթե կենդանի խցիկներ չկան
	{
		MessageBox(NULL, _T("is empty!"), _T(""), MB_ICONERROR);	// Անբարեհույս հաղորդագրություն

		return;	// Եվ կարող ենք ոչինչ չպահել
	}

	m_pause = true;	// Վարում ենք paus 

	CFileDialog dialog(FALSE, _T("*.life"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("games file (*.life)|*.life|"));	// Ստեղծում ենք պահելու երկխոսություն

	if (dialog.DoModal() == IDOK)	// Եթե օգտվողը ընտրել է, որտեղ պահել
	{
		std::ofstream fout(dialog.GetPathName());	// Բացենք այդ ֆայլը

		fout << GetProtoblastCount() << std::endl;	// Վերադարձնում ենք կենդանի խցիկների քանակը
		fout << std::endl;

		for (int i = 0; i < m_fieldHeight; ++i)	// Եվ հետո անցնում ենք բոլոր շարքերով
			for (int j = 0; j < m_fieldWidth; ++j)	// Յուրաքանչյուր շարքում
				if (m_field[i][j]->IsLive())	// Եվ եթե խցիկը կենդանի է
					fout << i << " " << j << std::endl;	// Այն ժամանակ պետք է գրանցվի ֆայլում

		MessageBox(NULL, _T("game saved sucessfuly!"), _T(""), MB_ICONINFORMATION);	// Խրախուսիչ հաղորդագրություն
	}

	m_pause = false;	// Պաուզան ավարտվել է
}

void CGameApp::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)	// Կլավիշի սեղմման մեթոդ
{
	if (!m_pause && nChar == 32 && m_evolveTime == 0)	// Եթե սեղմում ենք պարանոց և խաղը չի կանգնած, և էվոլուցիան ձեռքով
		Evolve();	// Այն ժամանակ ժամանակն է էվոլյուցիայի համար
}

void CGameApp::OnNewGame()	// "Նոր խաղ" մենյուի բացման մեթոդ
{
	if (GetProtoblastCount() == 0)	// Եթե և այնպես մաքուր
		return;	// Այն դեպքում բան չկա անելու

	m_pause = true;	// Այլ դեպքում՝ paus 

	if (MessageBox(NULL, _T("is start new game?"), _T("new game"), MB_YESNO | MB_ICONQUESTION) == IDYES)	// Հետաքրքիր հարց
		CreateNewGame();	// Եթե համաձայն են նոր խաղի, ապա այն ստեղծում ենք

	m_pause = false;	// Պաուզան ավարտվել է
}
