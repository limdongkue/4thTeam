// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

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
	//// m_mapUnitData�� ��� ��� ����
	//for (auto& pair : m_mapUnitData) {
	//	delete pair.second;
	//}
	//m_mapUnitData.clear();

	//// m_ListBox�� ��� ������ ����
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


// CUnitTool �޽��� ó�����Դϴ�.



void CUnitTool::OnPush()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString		strSelectName;

	// GetCurSel : ���� ����Ʈ �ڽ����� ���õ� ����� �ε����� ��ȯ
	int		iSelect = m_ListBox.GetCurSel();

	if (-1 == iSelect)
		return;

	// GetText : ���� �ε����� �ش��ϴ� ���ڿ��� ������ �Լ�
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

	//// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iIndex = m_ListBox.GetCurSel(); // ���� ����Ʈ �ڽ��� �ε��� ��ȯ

	if (-1 == iIndex)
		return;

	CString wstrName;
	m_ListBox.GetText(iIndex, wstrName);
	// GetText : ���� �ε����� �ش��ϴ� ���ڿ��� ������

	auto iter = m_mapUnitData.find(wstrName); // ������ Ű �� ã��
	
	if (iter == m_mapUnitData.end())
		return;

	Safe_Delete(iter->second); // ã�� Ű ���� Value ����
	m_mapUnitData.erase(wstrName); // erase
	m_ListBox.DeleteString(iIndex); // list�ڽ� �ε��� ����

	UpdateData(FALSE);
}
