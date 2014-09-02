// 111.h : main header file for the 111 application
//

#if !defined(AFX_111_H__5F44DABD_A1F2_4CD4_9A08_73A5FDBC1D9B__INCLUDED_)
#define AFX_111_H__5F44DABD_A1F2_4CD4_9A08_73A5FDBC1D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy111App:
// See 111.cpp for the implementation of this class
//

class CMy111App : public CWinApp
{
public:
	CMy111App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy111App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy111App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_111_H__5F44DABD_A1F2_4CD4_9A08_73A5FDBC1D9B__INCLUDED_)
