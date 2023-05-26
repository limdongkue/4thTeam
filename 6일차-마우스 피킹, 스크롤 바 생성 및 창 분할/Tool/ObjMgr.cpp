#include "stdafx.h"
#include "ObjMgr.h"


CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

int CObjMgr::Update()
{
	for (auto& iterA : m_ObjList)
	{
		for (auto iterB = iterA.begin(); iterB != iterA.end();)
		{
			if ((*iterB)->Update())
			{
				Safe_Delete(*iterB);
				iterB = iterA.erase(iterB);
			}
			else
				++iterB;

		}
	}
	return 0;
}

void CObjMgr::Late_Update()
{

}

void CObjMgr::Render(HDC hDC)
{
	for (auto& iterA : m_ObjList)
	{
		for (auto& iterB : iterA)
		{
			iterB->Render(hDC);
		}
	}
}

void CObjMgr::Release()
{
}

void CObjMgr::Add_Object(OBJID p_ID, CObj * p_Obj)
{
	m_ObjList[p_ID].push_back(p_Obj);
	m_LastAddedList.push_back({ p_ID,p_Obj });
}

