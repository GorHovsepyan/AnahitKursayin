#pragma once

#include "stdafx.h"
#include "afxdialogex.h"
#include "Game.h"

class CMyDialog : public CDialogEx
{
private:
    CString strValue;

public:
    CMyDialog(CWnd* pParent = nullptr);   // Standard constructor
    virtual ~CMyDialog();  // Destructor

    int GetGameIdText() ;  // Getter for the text from the edit control

protected:
    enum { IDD = IDD_DIALOG_ENTER_ID };  // Dialog resource ID

    virtual void DoDataExchange(CDataExchange* pDX);

    // Member variable for the CEdit control
    CEdit m_editGameId;

    // Message map declaration
    DECLARE_MESSAGE_MAP()
public:
    CString m_GameID;
    afx_msg void OnEnChangeEditGameId();
};

