#include "stdafx.h"
#include "cObject.h"


cObject::cObject() : m_ulRefCount(1)
{
}


cObject::~cObject()
{
}

void cObject::AddRef()
{
	++m_ulRefCount;
}

void cObject::Release()
{
	--m_ulRefCount;
	if (m_ulRefCount == 0)
		delete this;
}

