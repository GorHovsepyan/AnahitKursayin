#pragma once

#include "stdafx.h"
#include "afxdialogex.h"
#include "Game.h"

//կլասս <<About the game>> դիալոգի մասին 

class CAboutDlg : public CDialogEx
{
public:
	enum {IDD = IDD_ABOUTBOX};	// դիալոգի այդին

	CAboutDlg();	// դիֆոլթ կանստրուկտոր

private:
	DECLARE_MESSAGE_MAP() // մակրոս
};