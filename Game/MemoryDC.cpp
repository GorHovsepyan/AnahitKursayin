#include "stdafx.h"
#include "MemoryDC.h"

CMemoryDC::CMemoryDC(CDC* pDC, const CRect* pRect) : 	// Կոնստրուկտոր
	CDC()	// Աղբյուրային կլասի կոնստրուկտոր
{
	m_pDC = pDC;	// Ներդնում ենք նկարելու կոնտեքստի ցուցիչը
	m_oldBitmap = NULL;	// Նկարելու տարածքի հին պատկեր
	m_bMemDC = !pDC->IsPrinting();	// Կոնտեքստը օգտագործվել է նկարելու համար, թե ոչ

	if (pRect == NULL)	// Եթե նկարելու տարածքը նշված չէ
		pDC->GetClipBox(&m_rect);	// Այն դեպքում նկարելու ենք ամենուր
	else
		m_rect = *pRect;	// Այլ դեպքում՝ միայն այնտեղ, որտեղ անհրաժեշտ է

	if (m_bMemDC)	// Եթե արդեն նկարել ենք էկրանին
	{
		CreateCompatibleDC(pDC);	// Ստեղծում ենք համատեղելի նկարելու կոնտեքստ
		pDC->LPtoDP(&m_rect);	// Ստանում ենք չափերը
		m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());	// Ստեղծում ենք էկրանին պատկերի պատճեն
		m_oldBitmap = SelectObject(&m_bitmap);	// Գնում ենք հին պատկերը և հիշում, թե ինչ էր
		SetMapMode(pDC->GetMapMode());	// Նկարելու կարգավորումները տեղափոխում ենք
		SetWindowExt(pDC->GetWindowExt());	// Ստացվում են նկարելու կարգավորումները
		SetViewportExt(pDC->GetViewportExt());	// Նկարելու կարգավորումները տեղափոխում ենք
		pDC->DPtoLP(&m_rect);	// Ստանում ենք չափը
		SetWindowOrg(m_rect.left, m_rect.top);	// Պատուհանի տեղաշարժ
	}
	else	// Եթե էկրանին չենք նկարել
	{
		m_bPrinting = pDC->m_bPrinting;	// Նախկինում նկարել ենք, թե ոչ?
		m_hDC = pDC->m_hDC;	// Նկարելու կոնտեքստի պատճեն
		m_hAttribDC = pDC->m_hAttribDC;	// Նկարելու հատկանիշների պատճեն
	}

	FillSolidRect(m_rect, pDC->GetBkColor());	// Զնգում ենք ամբողջ ֆոնի գույնով
}

CMemoryDC::~CMemoryDC()	// Դեստրուկտոր
{
	if (m_bMemDC)	// Եթե մինչ այս նկարել ենք ինչ-որ բան
	{
		m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), this, m_rect.left, m_rect.top, SRCCOPY);	// Արդյունքները փոխանցում ենք նկարչական կոնտեքստ
		SelectObject(m_oldBitmap);	// Վերադարձնում ենք հին պատկերը
	}
	else	// Եթե մինչ այս չենք նկարել
		m_hDC = m_hAttribDC = NULL;	// Ի՞նչն է դուրս բերելու
}

CMemoryDC* CMemoryDC::operator->() 	// Մեթոդների կանչ
{
	return this;
}

CMemoryDC::operator CMemoryDC* ()	// Ցուցիչի հակակառուցման օպերատոր
{
	return this;
}
