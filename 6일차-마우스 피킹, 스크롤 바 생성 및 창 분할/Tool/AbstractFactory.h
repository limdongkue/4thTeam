#pragma once
#pragma once
#include	"Obj.h"
#include	"Define.h"

template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory()
	{
	}

	~CAbstractFactory()
	{
	}

	static	CObj*	Create()
	{
		CObj*		rObj = new T();
		rObj->Initialize();

		return rObj;

	}
};