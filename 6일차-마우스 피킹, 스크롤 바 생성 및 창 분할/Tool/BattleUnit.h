#pragma once
#include "Obj.h"

class CBattleUnit :
	public CObj
{
public:
	CBattleUnit();
	virtual ~CBattleUnit();

public:
	void		Set_UData(const UNITDATA& p_Data)
	{
		m_tUData = p_Data;
	}

protected:
	UNITDATA	 m_tUData;
	
};

