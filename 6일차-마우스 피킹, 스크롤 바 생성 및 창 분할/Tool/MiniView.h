#pragma once
#include "Terrain.h"
#include	"ToolView.h"
// CMiniView 뷰입니다.

class CMiniView : public CView
{
	DECLARE_DYNCREATE(CMiniView)

protected:
	CMiniView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMiniView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void		Set_Ter(CToolView* p_P)
	{
		m_pTer = p_P;
	}

protected:
	DECLARE_MESSAGE_MAP()

	CToolView*	m_pTer;

};


