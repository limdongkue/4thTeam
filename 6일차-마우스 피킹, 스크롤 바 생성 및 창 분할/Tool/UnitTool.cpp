// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strName(_T(""))
	, m_iHp(0)
	, m_iAttack(0)
{

}

CUnitTool::~CUnitTool()
{
	//// m_mapUnitData의 모든 요소 해제
	//for (auto& pair : m_mapUnitData) {
	//	delete pair.second;
	//}
	//m_mapUnitData.clear();

	//// m_ListBox의 모든 아이템 삭제
	//m_ListBox.ResetContent();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_iHp);
	DDX_Text(pDX, IDC_EDIT3, m_iAttack);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnPush)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnSave)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnLoad)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnDelete)

	ON_WM_DESTROY()

END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.



void CUnitTool::OnPush()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	UNITDATA*	pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iHp = m_iHp;
	pUnit->iAttack = m_iAttack;
	
	for (int i = 0; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck())
		{
			pUnit->byJobIndex = i;
			break;
		}
	}

	m_ListBox.AddString(pUnit->strName);
	m_mapUnitData.insert({ pUnit->strName, pUnit });

	UpdateData(FALSE);

}


void CUnitTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strSelectName;

	// GetCurSel : 현재 리스트 박스에서 선택된 목록의 인덱스를 반환
	int		iSelect = m_ListBox.GetCurSel();

	if (-1 == iSelect)
		return;

	// GetText : 현재 인덱스에 해당하는 문자열을 얻어오는 함수
	m_ListBox.GetText(iSelect, strSelectName);

	auto	iter = m_mapUnitData.find(strSelectName);

	if (iter == m_mapUnitData.end())
		return;

	m_strName = iter->second->strName;
	m_iHp = iter->second->iHp;
	m_iAttack = iter->second->iAttack;

	for (int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);

	m_Radio[iter->second->byJobIndex].SetCheck(TRUE);

	UpdateData(FALSE);
}

void CUnitTool::OnDestroy()
{
	CDialog::OnDestroy();

	//// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	for_each(m_mapUnitData.begin(), m_mapUnitData.end(), CDeleteMap());
	m_mapUnitData.clear();

	m_ListBox.ResetContent();
}



void CUnitTool::OnSave()
{

	HANDLE hFile = CreateFile(L"../Data/Player.dat",
		GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		AfxMessageBox(L"Save Failed");
		return;
	}

	DWORD dwByte = 0;
	DWORD dwStringSize = 0;

	for (auto& Pair : m_mapUnitData)
	{
		dwStringSize = sizeof(wchar_t) * (Pair.second->strName.GetLength() + 1);
		WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
		WriteFile(hFile, Pair.second->strName.GetString(), dwStringSize, &dwByte, nullptr);
		WriteFile(hFile, &Pair.second->iAttack, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &Pair.second->iHp, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &Pair.second->byJobIndex, sizeof(int), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	AfxMessageBox(L"Save Successful");

}


void CUnitTool::OnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	HANDLE hFile = CreateFile(L"../Data/Player.dat",
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		AfxMessageBox(L"Load Failed");
		return;
	}

	DWORD dwByte = 0;
	DWORD dwStringSize = 0;
	UNITDATA* pUnit = nullptr;

	while (true)
	{
		pUnit = new UNITDATA;
		ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);

		wchar_t pTemp[MAX_PATH];

		ReadFile(hFile, pTemp, dwStringSize, &dwByte, nullptr);
		ReadFile(hFile, &pUnit->iAttack, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pUnit->iHp, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pUnit->byJobIndex, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete<UNITDATA*>(pUnit);
			break;
		}

		pUnit->strName = pTemp;
		m_mapUnitData.insert({ pUnit->strName, pUnit });
		m_ListBox.AddString(pUnit->strName);
	}

	CloseHandle(hFile);

	AfxMessageBox(L"Load Successful");

}


void CUnitTool::OnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iIndex = m_ListBox.GetCurSel(); // 현재 리스트 박스의 인덱스 반환

	if (-1 == iIndex)
		return;

	CString wstrName;
	m_ListBox.GetText(iIndex, wstrName);
	// GetText : 현재 인덱스에 해당하는 문자열을 얻어오기

	auto iter = m_mapUnitData.find(wstrName); // 삭제할 키 값 찾기
	
	if (iter == m_mapUnitData.end())
		return;

	Safe_Delete(iter->second); // 찾은 키 값의 Value 삭제
	m_mapUnitData.erase(wstrName); // erase
	m_ListBox.DeleteString(iIndex); // list박스 인덱스 삭제

	UpdateData(FALSE);
}
