#pragma once

#include "SingleTexture.h"
#include "MultiTexture.h"

class CTextureMgr
{
	SINGLETON(CTextureMgr)

private:

public:
	const TEXINFO*		Get_Texture(const TCHAR* pObjKey,
									const TCHAR* pStateKey = L"",
									const int& iCount = 0);

	HRESULT		Insert_Texture(const TCHAR* pFilePath,
								TEXTYPE eType,
								const TCHAR* pObjKey,
								const TCHAR* pStateKey = L"",
								const int& iCount = 0);

	 void		Release(void);

private:
	map<wstring, CTexture*>		m_mapTexture;
};

