#pragma once
#include	"Include.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual void	Late_Update()	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release()		PURE;


public:
	virtual	void	Collide(OBJID p_ID, CObj* p_Targ) PURE;

public:
	void			Set_Info(const INFO& p_Info)
	{
		m_tInfo = p_Info;
	}


public:
	const INFO&		Get_Info() { return m_tInfo; }

protected:
	tagFrame	m_tFrame;
	INFO		m_tInfo;

	bool		m_bDead;

};

