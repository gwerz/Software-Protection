// u盾写入Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "u盾写入.h"
#include "u盾写入Dlg.h"
#include <accctrl.h>
#include <aclapi.h>
#include <winioctl.h>
#include <shlwapi.h>

#pragma comment(lib,"shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDlg dialog

CUDlg::CUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDlg)
	m_hex = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDlg)
	DDX_Control(pDX, IDC_DRIVELIST, m_list);
	DDX_Text(pDX, IDC_HEX, m_hex);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUDlg, CDialog)
	//{{AFX_MSG_MAP(CUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ, OnRead)
	ON_BN_CLICKED(IDWRITE, OnWrite)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDlg message handlers

inline char* decode(char* buf,int bufsize)
{
	for(int i=0;i<bufsize;i++)
	{
		buf[i]=~buf[i];
	}
	return buf;
}
#define DECODE(buf) decode(buf,sizeof(buf))

BOOL CUDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Logged=FALSE;

	char sig[]={0xB1,0xB5,0xAA,0xAC,0xB1,0xB6,0xAC,0xFF};//识别码NJUSNIS
	char invalid_u[]={0x8A,0x49,0x23,0x4D,0x44,0x2A,0x02,0x37,0x48,0xFF};
	char psw[]={0xCA,0x9B,0xC8,0xC8,0x9E,0xC9,0xC8,0x9D,0xC9,0xCA,0x9B,0xCA,
				0xC6,0x9D,0xCA,0x9C,0x9A,0x9A,0x9C,0xC6,0x9E,0xC8,0x9A,0xCC,
				0x9C,0x9C,0xCF,0xC9,0xC7,0x9A,0xC9,0x9C,0xFF};//5d77a67b65d59b5ceec9a7e3cc068e6c

	if(0!=NTFindFirst(DECODE(sig)))
	{
		AfxMessageBox(DECODE(invalid_u));
		Logged=FALSE;
		return FALSE;
	}
	if(0!=NTLogin(DECODE(psw)))
	{
		AfxMessageBox(DECODE(invalid_u));
		Logged=FALSE;
		return FALSE;
	}
	Logged=TRUE;

	char drivebuffer[]="c:\\";
	for(char i='c';i<='z';i++)
	{
		drivebuffer[0]=i;
		if(DRIVE_REMOVABLE == GetDriveType(drivebuffer))
		{
			m_list.AddString(CString(drivebuffer));
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUDlg::OnRead() 
{
	// TODO: Add your control notification handler code here
	BYTE buf[1024];
	
	char nologin[]={0x31,0x4B,0x4A,0x38,0x3D,0x43,0xDE,0xFF};

	if(!Logged)
	{
		AfxMessageBox(DECODE(nologin));
		return;
	}
	memset(buf,0,1024);
	NTRead(0,1024,buf);
	for(int i=0;i<1024;i++)
	{
		char s[8];
		sprintf(s,"%02X ",buf[i]);
		m_hex += s;
		if((i%16) == 15)
			m_hex += "\r\n";
	}
	UpdateData(FALSE);
}

struct U_DefenderInfo
{
	float Version;
	char CompanyName[48];
	BYTE Reserve[56];
	BYTE Data[0];
};

bool SetACL(LPTSTR OjbectName)
{
	PSID pEveryoneSID=NULL,pAdminSID=NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld=SECURITY_WORLD_SID_AUTHORITY;
	if(!AllocateAndInitializeSid(&SIDAuthWorld,1,SECURITY_WORLD_RID,0,0,0,0,0,0,0,&pEveryoneSID))
	{//ERROR
		if(pEveryoneSID) FreeSid(pEveryoneSID);
		return FALSE;
	}
	
	SID_IDENTIFIER_AUTHORITY SIDAuthNT=SECURITY_NT_AUTHORITY;
	if(!AllocateAndInitializeSid(&SIDAuthNT,2,SECURITY_BUILTIN_DOMAIN_RID,DOMAIN_ALIAS_RID_ADMINS,
		0,0,0,0,0,0,&pAdminSID))
	{
		if(pAdminSID) FreeSid(pAdminSID);
		if(pEveryoneSID) FreeSid(pEveryoneSID);
		return FALSE;
	}
	
	EXPLICIT_ACCESS ea[2];
	ZeroMemory(ea,2*sizeof(EXPLICIT_ACCESS));
	ea[0].grfAccessPermissions=GENERIC_ALL;
	ea[0].grfAccessMode=SET_ACCESS;
	ea[0].grfInheritance=NO_INHERITANCE;
	ea[0].Trustee.TrusteeForm=TRUSTEE_IS_SID;
	ea[0].Trustee.TrusteeType=TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[0].Trustee.ptstrName=(LPSTR)pEveryoneSID;
	ea[1].grfAccessPermissions=GENERIC_ALL;
	ea[1].grfAccessMode=SET_ACCESS;
	ea[1].grfInheritance=NO_INHERITANCE;
	ea[1].Trustee.TrusteeForm=TRUSTEE_IS_SID;
	ea[1].Trustee.TrusteeType=TRUSTEE_IS_GROUP;
	ea[1].Trustee.ptstrName=(LPSTR)pAdminSID;
	
	PACL pACL=NULL;
	if(!SetEntriesInAcl(2,ea,NULL,&pACL))
	{
		DWORD nRet=SetNamedSecurityInfo(OjbectName,SE_FILE_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,pACL,NULL);
		
		if(nRet == ERROR_ACCESS_DENIED)
		{
			SetNamedSecurityInfo(OjbectName,SE_FILE_OBJECT,OWNER_SECURITY_INFORMATION,pAdminSID,NULL,NULL,NULL);
			SetNamedSecurityInfo(OjbectName,SE_FILE_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,pACL,NULL);
		}
	}
	
	if(pACL) LocalFree(pACL);
	if(pAdminSID) FreeSid(pAdminSID);
	if(pEveryoneSID) FreeSid(pEveryoneSID);
	return 0;
}


void CUDlg::OnWrite() 
{
	int sel=m_list.GetCurSel();
	if(LB_ERR == sel)
	{
		AfxMessageBox("请选择要写入的U盘");
		return;
	}
	CString objdrive;
	m_list.GetText(sel,objdrive);

	if(PathFileExists(objdrive+"\\initialed"))
	{//已初始化
		return;
	}

	HANDLE sigfile=CreateFile(objdrive+"\\initialed",0,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	ASSERT(sigfile != INVALID_HANDLE_VALUE);
	CloseHandle(sigfile);
	
	DWORD readbyte;
	CString partitionstr="\\\\.\\"+objdrive;
	partitionstr=partitionstr.Left(partitionstr.GetLength()-1);

	SetACL((LPTSTR)(LPCTSTR)partitionstr);
	HANDLE holdfile=CreateFile(objdrive+"content\\HyTramSerial.exe",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	HANDLE hidden=CreateFile(partitionstr,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	ASSERT(hidden != INVALID_HANDLE_VALUE);
	ASSERT(holdfile != INVALID_HANDLE_VALUE);
	DWORD filesize=GetFileSize(holdfile,NULL);
	BOOL ret=FALSE;
	
	readbyte=SetFilePointer(hidden,0x40000000-0x01000000,NULL,FILE_BEGIN);

	BYTE* buff=new BYTE[0x01000000];
	memset(buff,0,0x01000000);
	*(DWORD*)buff=filesize;
	ret=ReadFile(holdfile,buff+sizeof(DWORD),filesize,&readbyte,NULL);
	if(!ret)
	{
		AfxMessageBox("读取失败!");
		return;
	}

	ret=WriteFile(hidden,buff,0x01000000,&readbyte,NULL);//写入长度

	if(!ret)
	{
		DeviceIoControl(hidden,FSCTL_DISMOUNT_VOLUME,NULL,0,NULL,0,&readbyte,NULL);
		readbyte=SetFilePointer(hidden,0x40000000-0x01000000,NULL,FILE_BEGIN);
		ret=WriteFile(hidden,buff,0x01000000,&readbyte,NULL);//写入长度
		if(!ret)
		{
			AfxMessageBox("写入失败!");
			return;
		}
		else
		{
			CloseHandle(hidden);
			hidden=CreateFile(partitionstr,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
		}
	}

	IMAGE_DOS_HEADER DosHeader;
    IMAGE_NT_HEADERS NtHeader;
    DWORD dwNumberOfBytesRead = 0;

	CopyMemory(&DosHeader,buff+sizeof(DWORD),sizeof(DosHeader));
	CopyMemory(&NtHeader,buff+sizeof(DWORD)+DosHeader.e_lfanew,sizeof(NtHeader));
	IMAGE_SECTION_HEADER curheader;
	WORD i=0;
	DWORD offset=sizeof(DWORD)+DosHeader.e_lfanew+sizeof(NtHeader);
	for(i=0;i<NtHeader.FileHeader.NumberOfSections;i++)
	{
		CopyMemory(&curheader,buff+offset,sizeof(curheader));
		if(!StrCmp((char*)curheader.Name,".text"))
		{
			break;
		}
		offset += sizeof(curheader);
	}

	CloseHandle(holdfile);
	holdfile=CreateFile(objdrive+"content\\HyTramSerial.exe",GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	SetFilePointer(holdfile,curheader.PointerToRawData,NULL,FILE_BEGIN);
	BYTE* newbuf=new BYTE[curheader.SizeOfRawData];
	memset(newbuf,0,curheader.SizeOfRawData);
	WriteFile(holdfile,newbuf,curheader.SizeOfRawData,&dwNumberOfBytesRead,NULL);

	CloseHandle(hidden);
	CloseHandle(holdfile);
	delete []buff;
	delete []newbuf;
	
	// TODO: Add your control notification handler code here
	char sig[]={0x3B,0x30,0x41,0x56,0x4B,0x0C,0x2E,0x58,0x46,0x05,0x43,0x2D,
				0x4E,0x5C,0x3C,0x23,0x2E,0x58,0x2B,0x45,0xD2,0x49,0x1F,0x1B,
				0x50,0x3F,0x3F,0x39,0x08,0x36,0x19,0x3C,0x23,0x43,0x13,0x4D,
				0x16,0x37,0x5E,0x29,0x5B,0x46,0x5B,0x41,0x20,0xFF};
	char nologin[]={0x31,0x4B,0x4A,0x38,0x3D,0x43,0xDE,0xFF};

	if(!Logged)
	{
		AfxMessageBox(DECODE(nologin));
		return;
	}

	HLOCAL mem=LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT,1024);
	U_DefenderInfo* u_info=(U_DefenderInfo*)mem;

	u_info->Version=1.0;
	strcpy(u_info->CompanyName,DECODE(sig));

	BYTE* ptr=u_info->Data;
#define AddString(str) {memcpy(ptr,str,sizeof(str)),ptr+=sizeof(str);}
	AddString("\\Data\\TaskDb.dat");//0
	AddString("\\Documents\\Thunder Network\\MiniXLOEM\\thunder\\Data\\TaskDb.dat");//1
	AddString("\\Opera\\Opera\\cookies4.dat");//2
	AddString("Opera\\download.dat");//3
	AddString("Setting\\History.dat");//4
	AddString("\\AppData\\Roaming\\360se\\data\\history.dat");//5
	AddString("\\SogouExplorer\\Favorite2.dat");//6
	AddString("\\Favorite2.dat");//7
	AddString("\\Thunder\\Profiles\\TaskDb.dat");//8
	AddString("Users\\Public\\Documents\\Thunder Network\\Thunder\\Profiles\\TaskDb.dat");//9
	AddString("\\Thunder\\Profiles\\TaskDb.dat");//10
	AddString("\\Documents\\Thunder Network\\Thunder\\Profiles\\TaskDb.dat");//11
	AddString("config\\FileList.db");//12
	AddString("\\dat\\FlashGet3db.db");//13
	AddString("\\FlashGet\\v3\\dat\\FlashGet3db.db");//14
	AddString("\\360se\\data\\360sefav.db");//15
	AddString("\\Tencent\\TencentTraveler\\100\\navinfo.db");//16
	AddString("\\UDown\\Data\\HisData.db");//17
	AddString("Users\\All Users\\115\\UDown\\Data\\HisData.db");//18
	ptr=(BYTE*)u_info;

	decode((char*)u_info->Data,1024-sizeof(U_DefenderInfo));
	NTWrite(0,1024,(BYTE*)u_info);
	LocalFree(mem);
	AfxMessageBox("写入成功!");
}

void CUDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(Logged)
		NTLogout();
	CDialog::OnClose();
}

