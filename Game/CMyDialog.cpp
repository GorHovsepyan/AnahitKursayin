#include "StdAfx.h"
#include "CMyDialog.h"
#include "resource.h"


// Constructor
CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_ENTER_ID, pParent)
    , m_GameID(_T(""))
{
}

// Destructor
CMyDialog::~CMyDialog()
{
}

// Data exchange function (bind controls to member variables)
void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_GAME_ID, m_editGameId);
    DDX_Text(pDX, IDC_EDIT_GAME_ID, m_GameID);
}

// Getter for the text from the edit control
int CMyDialog::GetGameIdText() 
{
    
    
    int intValue = _ttoi(m_GameID); // Use _tto for Unicode/ANI compatibility

    return intValue;
}

// Message map implementation
BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
    // Add your message handler functions here
    ON_EN_CHANGE(IDC_EDIT_GAME_ID, &CMyDialog::OnEnChangeEditGameId)
END_MESSAGE_MAP()

void CMyDialog::OnEnChangeEditGameId()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}
