// 111Dlg.h : header file
//

#if !defined(AFX_111DLG_H__58039FFA_2F06_46E4_A907_FAA51C689542__INCLUDED_)
#define AFX_111DLG_H__58039FFA_2F06_46E4_A907_FAA51C689542__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy111Dlg dialog

class CMy111Dlg : public CDialog
{
// Construction
public:
	CMy111Dlg(CWnd* pParent = NULL);	// standard constructor
	HMODULE				manager;
	HMODULE				applic;
	long				NTHandle[8];
	long				nKeyNum;
	PROCESS_INFORMATION pi;
	CFile				DestFile;
// Dialog Data
	//{{AFX_DATA(CMy111Dlg)
	enum { IDD = IDD_MY111_DIALOG };
	CString	m_out;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy111Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	typedef long (WINAPI *NTFINDALL)(long*,long*); 
	typedef long (WINAPI *NTGETDEVCAPS)(long,long*,long*,long*,long*,long*);
	typedef long (WINAPI *NTFINDFIRST)(char*);
	typedef long (WINAPI *NTGETHARDWAREID)(char*);
	typedef long (WINAPI *NTLOGIN)(char*);
	typedef long (WINAPI *NTLOGOUT)();
	typedef long (WINAPI *NTREAD)(long,long,unsigned char*);
	
	NTFINDALL		NTFindAll;
	NTGETDEVCAPS	NTGetDevCaps;
	NTGETHARDWAREID NTGetHardwareID;
	NTLOGIN			NTLogin;
	NTLOGOUT		NTLogout;
	NTFINDFIRST		NTFindFirst;
	NTREAD			NTRead;

	HICON m_hIcon;

	void FindDevice();
	// Generated message map functions
	//{{AFX_MSG(CMy111Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnExec();
	afx_msg void OnLogout();
	afx_msg void OnFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_111DLG_H__58039FFA_2F06_46E4_A907_FAA51C689542__INCLUDED_)
