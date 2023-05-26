#pragma once
#include	"Include.h"
class CEditMgr
{
	SINGLETON(CEditMgr);


public:
	EDIT_TYPE	Get_EType() { return m_eType; }

public:
	void		Set_EType(EDIT_TYPE p_Type)
	{
		m_eType = p_Type;
	}

private:
	EDIT_TYPE	m_eType;
};

