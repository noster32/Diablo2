#pragma once
#include <Windows.h>

class IWindowMessage
{
public:
	/*
	virtual void IFunctionA() = 0;
	virtual void IFunctionB() = 0;
	virtual void IFunctionC() = NULL;
	virtual void IFunctionD() PURE; 
	virtual void IFunctionE() abstract;
	*/
	IWindowMessage();
	~IWindowMessage();
};

