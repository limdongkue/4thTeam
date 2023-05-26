#pragma once
#include	"Include.h"
#include	"Obj.h"

class CObjMgr
{
	SINGLETON(CObjMgr);




public:
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	void		Add_Object(OBJID p_ID, CObj* p_Obj);
	void		Delete_Last()
	{
		Safe_Delete(m_ObjList[m_LastAddedList.back().first].back());
		m_ObjList[m_LastAddedList.back().first].pop_back();
		m_LastAddedList.pop_back();
	}

	void		Delete_All()
	{
		for (auto& iter : m_ObjList)
		{
			for (auto& iterB : iter)
			{
				Safe_Delete(iterB);
			}
			iter.clear();
		}
	}

	void		Delete(OBJID p_Type)
	{
		for (auto& iter : m_ObjList[p_Type])
		{
			Safe_Delete(iter);
		}
		m_ObjList[p_Type].clear();
	}

public:
	CObj*	Get_Last_Added() { return m_LastAddedList.back().second; }


private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<pair<OBJID, CObj*>>	m_LastAddedList;
};

