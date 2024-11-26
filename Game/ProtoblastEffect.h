#pragma once

#include "stdafx.h"
#include "MemoryDC.h"

// Բջիջի վիճակների enumeration
enum EStatus { STATUS_NONE, STATUS_DISABLE, STATUS_ACTIVE, STATUS_HOVER };

/* Բջիջների նկարահանման էֆեկտների աբստրակտ դաս */
class CProtoblastEffect
{
public:
	CProtoblastEffect(CSize area);	// Կոնստրուկտոր
	virtual ~CProtoblastEffect();	// Վիրտուալ դեստրուկտոր

	COLORREF GetCurrColor();	// Ներկա գույնի ստացման մեթոդ

	virtual void Tick() = 0;	// Թերթելու մեթոդ (մշտական)
	virtual void Render(CMemoryDC&, CPoint);	// Նկարելու մեթոդ
	virtual EStatus GetStatus() = 0;	// Վիճակի ստացման մեթոդ
	virtual EStatus GetLastStatus();	// Վերջին վիճակի ստացման մեթոդ

protected:
	COLORREF m_currColor;	// Ներկա գույնը
	CSize m_area;			// դաշտի չափսը

	void ChangeColor(COLORREF, int, int, int);	// Ներկա գույնի փոփոխության մեթոդ
	byte MakeChangeColorStep(int, int, int);	// Գույնի բաղադրիչի փոփոխության մեթոդ
};

/* Մեռած բջիջի էֆեկտի դաս, որը ժառանգում է նկարահանման էֆեկտների դասից */
class CProtoblastEffectDisable : public CProtoblastEffect
{
public:
	CProtoblastEffectDisable(CSize, CProtoblastEffect*);	// Կոնստրուկտոր
	~CProtoblastEffectDisable();	// Դեստրուկտոր

	void Tick();			// Թերթելու մեթոդ
	EStatus GetStatus();	// Վիճակի ստացման մեթոդ

protected:
	static const COLORREF m_endColor = RGB(255, 255, 255);	// Վերջնական գույն (սպիտակ)
};

/* կենդանի բջիջի էֆեկտի դաս, որը ժառանգում է նկարահանման էֆեկտների դասից */
class CProtoblastEffectActive : public CProtoblastEffect
{
public:
	CProtoblastEffectActive(CSize, CProtoblastEffect*);	// Կոնստրուկտոր
	~CProtoblastEffectActive();	// Դեստրուկտոր

	void Tick();			// Թերթելու մեթոդ
	EStatus GetStatus();	// Վիճակի ստացման մեթոդ

protected:
	static const COLORREF m_endColor = RGB(87, 141, 249);	// Վերջնական գույն (երկնագույն)
};

/* Ընդգծված բջիջի էֆեկտի դաս, որը ժառանգում է նկարահանման էֆեկտների դասից */
class CProtoblastEffectHover : public CProtoblastEffect
{
public:
	CProtoblastEffectHover(CSize, CProtoblastEffect* last);	// Կոնստրուկտոր
	~CProtoblastEffectHover();	// Դեստրուկտոր

	void Tick();	// Թերթելու մեթոդ
	void Render(CMemoryDC&, CPoint);	// Նկարելու մեթոդ
	EStatus GetStatus();		// Վիճակի ստացման մեթոդ
	EStatus GetLastStatus();	// Վերջին վիճակի ստացման մեթոդ

protected:
	COLORREF m_colors[4];	// Կյանքի ընթացքում փոփոխվող գույներ
	int m_color;			// Ներկա ընտրված գույնի ինդեքս
	int m_tickCount;		// Անիմացիայի սկիզբը
	EStatus m_lastStatus;	// Վերջին վիճակը
};
