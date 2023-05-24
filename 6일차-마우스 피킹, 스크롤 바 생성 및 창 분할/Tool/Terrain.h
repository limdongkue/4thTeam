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
	void		Render(float p_Size = 1.f);
	void		Release(void);
	

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }

public:
	int		Get_TileIndex(const D3DXVECTOR3& vPos);
	void	Tile_Change(const D3DXVECTOR3& vPos, const int& iDrawID);
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
private:
	vector<TILE*>		m_vecTile;
	CToolView*			m_pMainView = nullptr;
};

