#include "stdafx.h"
#include "BattleUnit.h"


CBattleUnit::CBattleUnit()
{
	m_tUData.strName = L"";

	m_tUData.iAttack = 0;
	m_tUData.iHp = 0;
	m_tUData.byItem = 0;
	m_tUData.byJobIndex = 0;


}


CBattleUnit::~CBattleUnit()
{
}
