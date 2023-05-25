#pragma once
#include "afxcmn.h"

// CMapTool 대화 상자입니다.

class CDlgTab1;
class CDlgTab2;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnChangeTap(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CTabCtrl m_tab;
	CDlgTab1* m_dlg1;
	CDlgTab2* m_dlg2;


};
