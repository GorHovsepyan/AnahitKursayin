#include "stdafx.h"
#include "ProtoblastEffect.h"
#include <algorithm>

CProtoblastEffect::CProtoblastEffect(CSize area) : 	// Կոնստրուկտոր
	m_area(area)	// Այլ ոչ մի պարամետր
{
}

CProtoblastEffect::~CProtoblastEffect()	// Դեստրուկտոր
{
}

COLORREF CProtoblastEffect::GetCurrColor()	// Այս մեթոդը վերադարձնում է ներկա գույնը
{
	return m_currColor;	// Վերադարձնում ենք ներկա գույնը
}

void CProtoblastEffect::ChangeColor(COLORREF endColor, int stepR, int stepG, int stepB)	// Այս մեթոդը փոփոխում է ներկա գույնը՝ մոտեցնելով նրան վերջնական գույնին
{
	if (m_currColor == endColor)	// Եթե հասել ենք վերջնական գույնին
		return;	// Դրանով ավարտվում է

	// Մոտեցնում ենք յուրաքանչյուր գունային բաղադրիչը
	int r = MakeChangeColorStep(GetRValue(m_currColor), GetRValue(endColor), stepR);
	int g = MakeChangeColorStep(GetGValue(m_currColor), GetGValue(endColor), stepG);
	int b = MakeChangeColorStep(GetBValue(m_currColor), GetBValue(endColor), stepB);

	m_currColor = RGB(r, g, b);	// Այժմ ստանում ենք ներկա գույնը
}

byte CProtoblastEffect::MakeChangeColorStep(int chCurr, int chEnd, int step)	// Այս մեթոդը փոփոխում է գույնի բաղադրիչը՝ տրամադրելով փուլային փոփոխություն
{
	if (step < 0)	// Եթե փուլը բացասական է
		step *= -1;	// Այն դառնում է դրական

	if (chCurr == chEnd)	// Եթե բաղադրիչները համեմատելի են
		return chCurr;	// Այն դեպքում վերադարձնում ենք ընթացիկ արժեքը

	if (chCurr > chEnd)	// Եթե պետք է նվազեցնել բաղադրիչը
		chCurr = max(chCurr - step, chEnd);	// Այն դեպքում այնպես էլ անում ենք
	else
		chCurr = min(chCurr + step, chEnd);	// Ուղղորդվում ենք առաջ

	return chCurr;	// Վերադարձնում ենք ստացված արժեքը
}

void CProtoblastEffect::Render(CMemoryDC& dc, CPoint position)	// Այս մեթոդը ներկում է մոլեկուլայի ներկառուցված հատվածը
{
	dc.FillSolidRect(position.x, position.y, m_area.cx, m_area.cy, m_currColor);	// Զարդարում ենք ներկառուցված հատվածը ներկայի գույնով
}

EStatus CProtoblastEffect::GetLastStatus()	// Վերադարձնում է վերջին կարգավիճակը
{
	return STATUS_NONE;	// Այստեղ վերջինը անհրաժեշտ չէ
}

CProtoblastEffectDisable::CProtoblastEffectDisable(CSize area, CProtoblastEffect* last) :	// Կոնստրուկտոր
	CProtoblastEffect(area)	// Ռոդնային դասի կոնստրուկտոր
{
	m_currColor = last ? last->GetCurrColor() : m_endColor;	// Եթե նախկինում էր ներկա գույնը, ապա վերցնում ենք
}

CProtoblastEffectDisable::~CProtoblastEffectDisable()	// Դեստրուկտոր
{
}

void CProtoblastEffectDisable::Tick()	// Թերթելու մեթոդ
{
	ChangeColor(m_endColor, 20, 20, 20);	// Պարբերաբար մոտեցնում ենք ներկա գույնը վերջնական գույնին
}

EStatus CProtoblastEffectDisable::GetStatus()	// Վերադարձնում է կարգավիճակը
{
	return STATUS_DISABLE;	// Մոլեկուլայի մեռած կարգավիճակը
}

CProtoblastEffectActive::CProtoblastEffectActive(CSize area, CProtoblastEffect* last) :	// Կոնստրուկտոր
	CProtoblastEffect(area)	// Ռոդնային դասի կոնստրուկտոր
{
	m_currColor = last ? last->GetCurrColor() : m_endColor;	// Եթե նախկինում էր ներկա գույնը, ապա վերցնում ենք
}

CProtoblastEffectActive::~CProtoblastEffectActive()	// Դեստրուկտոր
{
}

EStatus CProtoblastEffectActive::GetStatus()	// Վերադարձնում է կարգավիճակը
{
	return STATUS_ACTIVE;	// Մոլեկուլայի կենդանի կարգավիճակը
}

void CProtoblastEffectActive::Tick()	// Թերթելու մեթոդ
{
	ChangeColor(m_endColor, 20, 20, 20);	// Պարբերաբար մոտեցնում ենք ներկա գույնը վերջնական գույնին
}

CProtoblastEffectHover::CProtoblastEffectHover(CSize area, CProtoblastEffect* last) :	// Կոնստրուկտոր
	CProtoblastEffect(area)	// Ռոդնային դասի կոնստրուկտոր
{
	m_lastStatus = last->GetStatus();	// Վերադարձնում ենք նախկին կարգավիճակը
	m_color = 0;	// Այժմ ընթացիկ գույնի ինդեքս
	m_colors[0] = RGB(255, 255, 153);	//  դեղին
	m_colors[1] = RGB(255, 255, 102);	// Դեղին
	m_colors[2] = RGB(255, 255, 51);	// դեղին
	m_colors[3] = m_colors[1];	// Դեղին
	m_currColor = last->GetCurrColor();	// Վերադարձնում ենք ներկա գույնը, որպեսզի հետ վերադարձնենք հաջորդին
}

CProtoblastEffectHover::~CProtoblastEffectHover()	// Դեստրուկտոր
{
}

void CProtoblastEffectHover::Tick()	// Թերթելու մեթոդ
{
	++m_tickCount;	// Տարրերի քանակը

	if (m_tickCount % 10 == 0)	// Եթե ժամանակն է գույնը փոխելու
	{
		m_tickCount = 0;	// Այն դեպքում նորից տարրերի քանակը
		m_color = (m_color + 1) % 4; 	// Փոխում ենք գույնը հաջորդի
	}
}

void CProtoblastEffectHover::Render(CMemoryDC& dc, CPoint position)	// Գծելու մեթոդ
{
	dc.FillSolidRect(position.x, position.y, m_area.cx, m_area.cy, m_colors[m_color]);	// Նկարելու գույնը համապատասխանում է ներկա ինդեքսին
}

EStatus CProtoblastEffectHover::GetStatus()	// Վերադարձնում է կարգավիճակը
{
	return STATUS_HOVER;	// Ընդգծված մոլեկուլայի կարգավիճակը
}

EStatus CProtoblastEffectHover::GetLastStatus()	// Վերադարձնում է նախորդ կարգավիճակը
{
	return m_lastStatus;	// Նախորդ կարգավիճակը
}
