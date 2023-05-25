// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "DlgTab1.h"
#include "DlgTab2.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
	Safe_Delete<CDlgTab1*>(m_dlg1);
	Safe_Delete<CDlgTab2*>(m_dlg2);
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect	rect;
	m_tab.GetWindowRect(rect);

	m_tab.InsertItem(0, L"Tile");
	m_tab.InsertItem(1, L"None");

	m_tab.SetCurSel(0);

	m_dlg1 = new CDlgTab1;
	m_dlg1->Create(IDD_DIALOG1, &m_tab);
	m_dlg1->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_dlg1->ShowWindow(SW_HIDE);

	m_dlg2 = new CDlgTab2;
	m_dlg2->Create(IDD_DIALOG2, &m_tab);
	m_dlg2->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_dlg2->ShowWindow(SW_HIDE);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMapTool::OnChangeTap)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnChangeTap(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (IDD_MAPTOOL == pNMHDR->idFrom)
	{
		int iSelect = m_tab.GetCurSel();

		switch (iSelect)
		{
		case OBJID::OBJ_PLAYER:
			m_dlg1->ShowWindow(SW_SHOW);
			m_dlg2->ShowWindow(SW_HIDE);
			break;
		case OBJID::OBJ_BULLET:
			m_dlg1->ShowWindow(SW_HIDE);
			m_dlg2->ShowWindow(SW_SHOW);
			break;
		}

	}

	*pResult = 0;
}


