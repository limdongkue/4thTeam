// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"
#include	"EditMgr.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{
}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO2, m_TypeBut[0]);
	DDX_Control(pDX, IDC_RADIO1, m_TypeBut[1]);

}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_RADIO2, &CMyForm::OnTileEdit)
	ON_BN_CLICKED(IDC_RADIO1, &CMyForm::OnObjectEdit)
END_MESSAGE_MAP()


void CMyForm::OnUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (nullptr == m_UnitTool.GetSafeHwnd())
	{
		m_UnitTool.Create(IDD_UNITTOOL);
		m_UnitTool.m_pOwner = this;
	}

	m_UnitTool.ShowWindow(SW_SHOW);
	m_UnitTool.m_Radio[0].SetCheck(TRUE);
	CEditMgr::Get_Instance()->Set_EType(EDIT_TILE);

}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_Font.CreatePointFont(150, L"궁서");

	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);

	m_TypeBut[0].SetCheck(TRUE);

}

void CMyForm::Closed_Edit()
{
	switch (CEditMgr::Get_Instance()->Get_EType())
	{	
	case EDIT_TILE: 
		m_TypeBut[0].SetCheck(TRUE);
		break;

	case EDIT_OBJECT:
		m_TypeBut[1].SetCheck(TRUE);

		break;

	default:
		break;
	}
}

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMyForm::OnTileEdit()
{
	CEditMgr::Get_Instance()->Set_EType(EDIT_TILE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm::OnObjectEdit()
{
	CEditMgr::Get_Instance()->Set_EType(EDIT_OBJECT);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
