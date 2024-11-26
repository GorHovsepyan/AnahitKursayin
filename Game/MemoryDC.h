#pragma once

/* Դուբլ-բուֆերացման իրականացման համար նախատեսված կլաս, որը ժառանգում է նկարչական կոնտեքստի կլասից */
class CMemoryDC : public CDC
{
public:
	CMemoryDC(CDC*, const CRect* pRect = NULL);	// Կոնստրուկտոր
	~CMemoryDC();				// Դեստրուկտոր
	CMemoryDC* operator->();	// Օպերատոր, որը թույլ է տալիս հասնել կլասի մեթոդներին
	operator CMemoryDC* ();		// Օպերատոր, որը հակակառուցում է

private:
	CBitmap m_bitmap;		// Այժմյան էկրան
	CBitmap* m_oldBitmap;	// Հին էկրան
	CDC* m_pDC;				// Նկարելու սկզբնական կոնտեքստ
	CRect m_rect;			// Նկարելու տարածքը
	BOOL m_bMemDC;			
};
