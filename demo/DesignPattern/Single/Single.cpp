// Single.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Singleton.h"
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	Singleton *p1 = Singleton::GetInstance();
	Singleton *p2 = Singleton::GetInstance();

	if (p1 == p2)
	{
		printf("single instance\n");
	}
	else {
		printf("more instance\n");
	}

	return 0;
}

