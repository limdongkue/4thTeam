#pragma once

#include "Include.h"

class CToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	HRESULT		Initialize(void);
	void		Update(void);
	void		Render();
	void		Mini_Render(void);
	void		Release(void);
	

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);
	void		Set_Index(const int& p_Int) 
	{ 
		m_iSelectedList.clear();
		m_iSelectedList.push_back(p_Int);
	}
	void		Add_Index(const int& p_Int)
	{
		if(find(m_iSelectedList.begin(), m_iSelectedList.end(), p_Int) == m_iSelectedList.end())
			m_iSelectedList.push_back(p_Int);
	}

public:
	int		Get_TileIndex(const D3DXVECTOR3& vPos);
	void	Tile_Change();
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);


private:
	vector<TILE*>		m_vecTile;

	int			m_iSelectedIndex;
	list<int>	m_iSelectedList;

	int			m_iImgCode;

	CToolView*			m_pMainView = nullptr;
};

