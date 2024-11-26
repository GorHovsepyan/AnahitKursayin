#include "stdafx.h"
#include "Protoblast.h"
#include "ProtoblastEffect.h"

CProtoblast::CProtoblast()	// Կոնստրուկտոր 
{
	m_frame = CSize(24, 24);	// դաշտի չափերը
	m_area = m_frame - CSize(2, 2);	// դաշտի ներքին տարածքի չափերը
	m_effect = NULL;	// Արտաքին տեսքը

	SetStatus(STATUS_DISABLE);	// դաշտը ոչ ակտիվ է
}

CProtoblast::~CProtoblast()	// Դեստրուկտոր
{
	if (m_effect)	// Եթե դաշտը նկարել են
		delete m_effect;	// Այն դեպքում այլևս նկարել պետք չէ
}

void CProtoblast::Render(CMemoryDC& dc, CPoint position)	// Կտորի նկարելու մեթոդ
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));	// Նկարելու համար մատիտ
	CPen* pLastPen = dc.SelectObject(&pen);	// Ավելացնում ենք մատիտը

	dc.Rectangle(position.x, position.y, position.x + m_frame.cx, position.y + m_frame.cy);	// Նկարում ենք ուղղանկյուն
	dc.SelectObject(pLastPen);	// Վերադարձնում ենք նախորդ մատիտը
	m_effect->Render(dc, position + CPoint(1, 1));	// Նկարում ենք ներքին տարածքը
}

void CProtoblast::Tick()	// Տվյալների թարմացման մեթոդ
{
	m_effect->Tick();	// Փոխանցում ենք կառավարումը նկարչական օբյեկտին
}

void CProtoblast::Click(bool isLeftButton)	// Մկնիկի կոճակի կտակի մեթոդ
{
	if (isLeftButton)	// Եթե սա ձախ մկնիկի կոճակն է
		SetStatus(STATUS_ACTIVE);	// Այն դեպքում դաշտը կենդանի է
	else	// Հակառակ դեպքում
		SetStatus(STATUS_DISABLE);	// Մեռնում ենք :(
}

void CProtoblast::Hover()	// դաշտը ընդգծելու մեթոդ
{
	SetStatus(STATUS_HOVER);	// Ընդգծում ենք կտորը
}

void CProtoblast::Unhover()	// դաշտը չընդգծելու մեթոդ
{
	SetStatus(m_effect->GetLastStatus());	// դաշտը ստանում է նախորդ վիճակը
}

void CProtoblast::SetStatus(EStatus status)	// դաշտը վիճակը կարգավորելու մեթոդ
{
	if (status == STATUS_NONE)	// Եթե կարգավորելու ոչինչ չկա
		return;	// Այդ դեպքում ոչինչ չպետք է անել

	EStatus currStatus = m_effect ? m_effect->GetStatus() : STATUS_NONE;	// Ստանում ենք դաշտի ընթացիկ վիճակը

	if (status == currStatus)	// Եթե ընթացիկ և նոր վիճակները համընկնում են
		return;	// Ավելի շատ բան անել պետք չէ

	if (status == STATUS_HOVER && currStatus != STATUS_DISABLE)	// Եթե ուզում ենք ընդգծել դաշտը, և այն չի համարվում մեռած
		return;	// Այդ դեպքում այնպես չէ

	CProtoblastEffect* temp = m_effect;	// Ընթացիկ նկարելու ազդեցությունը

	switch (status)	// Վիճակից կախված
	{
	case STATUS_ACTIVE:	// Կտորը կենդանանում է
		m_effect = new CProtoblastEffectActive(m_area, temp);	// Կենդանու կտորի ազդեցությունը
		break;

	case STATUS_HOVER:	// Ընդգծում ենք
		m_effect = new CProtoblastEffectHover(m_area, temp);	// Ընդգծված
		break;

	default:	// Այլապես, ամենայն հավանականությամբ, այն մեռած է
		m_effect = new CProtoblastEffectDisable(m_area, temp);	// Մեռած կտոր
	}

	delete temp;	// Ապահովում ենք հին նկարչական ազդեցությունը
}

int CProtoblast::GetWidth()	// Ստանում ենք կտորի լայնությունը
{
	return m_frame.cx;	// Լայնությունը
}

int CProtoblast::GetHeight()	// Ստանում ենք կտորի բարձրությունը
{
	return m_frame.cy;	// Բարձրությունը
}

CSize CProtoblast::GetSize()	// Ստանում ենք դաշտի չափը
{
	return m_frame;	// Չափը!
}

bool CProtoblast::IsLive()	// դաշտը կենդանի՞ է?
{
	return (m_effect->GetStatus() == STATUS_ACTIVE);	
}
