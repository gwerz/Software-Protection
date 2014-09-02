// u¶ÜÐ´ÈëDlg.h : header file
//

#if !defined(AFX_UDLG_H__53E0D4CA_CB91_4D92_8810_17D566AE54E9__INCLUDED_)
#define AFX_UDLG_H__53E0D4CA_CB91_4D92_8810_17D566AE54E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUDlg dialog

class CUDlg : public CDialog
{
// Construction
public:
	CUDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL Logged;
// Dialog Data
	//{{AFX_DATA(CUDlg)
	enum { IDD = IDD_U_DIALOG };
	CListBox	m_list;
	CString	m_hex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRead();
	afx_msg void OnWrite();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDLG_H__53E0D4CA_CB91_4D92_8810_17D566AE54E9__INCLUDED_)
