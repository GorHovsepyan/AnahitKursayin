#pragma once

#define _USE_MATH_DEFINES

#include "stdafx.h"
#include "MemoryDC.h"

/* Կլասը, որը ցույց է տալիս կետերի զարգացման ռեժիմը */
class CClock
{
public:
	CClock();	// Դեֆոլտ կոնստրուկտոր
	~CClock();	// Դեստրուկտոր

	void SetTime(int);		// Մեթոդ, որը սահմանում է ժամանակի միջակայքը կետերի զարգացման կանչերի միջև
	void Render(CMemoryDC&, CPoint);	// Մեթոդ, որը ցույց է տալիս ինդիկատորը էկրանին
	void Tick();			// Մեթոդ, որը թարմացնում է վիճակը
	int GetHeight();		// Մեթոդ, որը վերադարձնում է ինդիկատորի նկարի բարձրությունը
	int GetWidth();			// Մեթոդ, որը վերադարձնում է ինդիկատորի նկարի լայնությունը

protected:
	static const int m_height = 49;	// Ինդիկատորի նկարի բարձրությունը
	static const int m_width = 49;	// Ինդիկատորի նկարի լայնությունը

	int m_tick;		// Տիկերի քանակի հաշվողը վերջին զարգացման պահից
	int m_time;		// Կետերի զարգացման կանչերի միջև ժամանակի միջակայքը
};
