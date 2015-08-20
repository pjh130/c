#include "stdafx.h"
#include "Singleton.h"


Singleton::Singleton()
{
}


Singleton::~Singleton()
{
}

Singleton::Singleton(const Singleton&){

}

//此处初始化
Singleton *Singleton::m_pInstance = NULL;

Singleton *Singleton::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new Singleton();
	}

	return m_pInstance;
}

