#pragma once
#include	"Include.h"
#include	"Obj.h"

class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr);


private:
	CObjMgr();
	~CObjMgr();

public:
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	void		Add_Object(OBJID p_ID, CObj* p_Obj);


public:
	CObj*	Get_Last_Added() { return m_LastAddedList.back(); }


private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_LastAddedList;
};

