#include "stdafx.h"
#include "Clock.h"
#include "MemoryDC.h"
#include "resource.h"
#include <cmath>
#define M_PI 3.14159265358979323846

CClock::CClock()	// Ստանդարտ կոնստրուկտոր
{
	m_time = 0;	// Վճռական ռեժիմը էվոլյուցիաների կոչի
}

CClock::~CClock()	// Դեստրուկտոր
{
}

void CClock::Render(CMemoryDC& dc, CPoint position)	// Ցուցադրման մեթոդ էկրանին ցուցիչի
{
	CBitmap bmp;	// Ցուցիչի պատկեր
	CDC dcMemory;	// Հիշողության մեջ նկարելու կոնտեքստ

	//bmp.LoadBitmap(m_time ? IDB_CLOCK : IDB_HAND);	// Էվոլյուցիաների կոչի ռեժիմից կախված, բեռնում ենք կամ ժամացույց, կամ ձեռքը
	dcMemory.CreateCompatibleDC(dc);	// Ստեղծում ենք համապատասխան նկարելու կոնտեքստ ներկա նկարչի հետ
	dcMemory.SelectObject(&bmp);	// Նկար-ցուցիչի տեղադրում

	dc->TransparentBlt(position.x, position.y, m_width, m_height, &dcMemory, 0, 0, m_width, m_height, RGB(0, 0, 0)); // Պատկերի նկարում վերածում ընդհանուր կոնտեքստում, հաշվի առնելով թափանցիկ գույնը

	if (m_time)	// Եթե էվոլյուցիաների կոչի ռեժիմը ավտոմատ է
	{
		CPen pen(PS_SOLID, 3, RGB(255, 255, 255));	// Ժամացույցի սլաքը նկարելու համար մատիտ

		dc->SelectObject(&pen);	// Ընտրում ենք մատիտ
		dc->MoveTo(position + CPoint(22, 24));	// Ափսեի կենտրոն տեղափոխվում ենք

		double x = (double)position.x + 22.0 + 6.0 * sin((double)m_tick * M_PI / (double)m_time * 2.0);	// Ստանում ենք սլաքի վերջի դիրքը պարբերականը
		double y = (double)position.y + 24.0 - 6.0 * cos((double)m_tick * M_PI / (double)m_time * 2.0);	// Ստանում ենք սլաքի վերջի դիրքը ուղղահայաց

		dc->LineTo((int)x, (int)y);	// Նկարեք սլաքը ժամացույցի կենտրոնից
	}
}

void CClock::Tick()	// Պատրաստման մեթոդ
{
	++m_tick;	// Սպասեցնողի թվի ավելացում վերջին էվոլյուցիայի
}

void CClock::SetTime(int time)	// Էվոլյուցիաների կոչի միջև միջակայքի սահմանման մեթոդ
{
	m_time = time;	
	m_tick = 0;		
}

int CClock::GetHeight()	// Ցուցիչի նկարի բարձրության ստանալու մեթոդ
{
	return m_height;	// Վերադարձնում ենք բարձրությունը
}

int CClock::GetWidth()	// Ցուցիչի նկարի լայնության ստանալու մեթոդ
{
	return m_width;		// Վերադարձնում ենք լայնությունը
}
