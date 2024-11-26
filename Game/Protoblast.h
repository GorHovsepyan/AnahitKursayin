#pragma once

#include "stdafx.h"
#include "ProtoblastEffect.h"

/* Խաղային դաշտի մոլեկուլայի դաս */
class CProtoblast
{
public:
	CProtoblast();	// Կոնստրուկտոր ըստ օրինակի
	~CProtoblast();	// Դեստրուկտոր

	CSize GetSize();	// Մոլեկուլայի չափը ստանալու մեթոդ
	void Render(CMemoryDC&, CPoint);	// ֆրեյմը նկարելու մեթոդ
	void Tick();		// Ստատուսը թարմացնելու մեթոդ
	void Click(bool isLeftButton = true);	// ֆրեյմի վրա մկնիկի  կատարելու մեթոդ
	void Hover();		// ֆրեյմը ընդգծելու մեթոդ
	void Unhover();		// ֆրեյմը չընդգծելու մեթոդ
	bool IsLive();		// ֆրեյմը կենդանի՞ է որոշելու մեթոդ
	int GetWidth();		// ֆրեյմի լայնությունը ստանալու մեթոդ
	int GetHeight();	// ֆրեյմի բարձրությունը ստանալու մեթոդ

private:
	CProtoblastEffect* m_effect;	// ֆրեյմի նկարչությունը
	CSize m_frame;					// ֆրեյմի չափը
	CSize m_area;					// Ներքին տարածքի չափը

	void SetStatus(EStatus);	// ֆրեյմի վիճակը կարգավորելու մեթոդ
};
