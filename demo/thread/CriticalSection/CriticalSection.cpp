// CriticalSection.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <process.h>
#include <Windows.h>

/*
	1. 互斥：是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的
	2. 同步：是指在互斥的基础上（大多数情况），通过其它机制实现访问者对资源的有序访问。在大多数情况下，同步已经实现了互斥，特别是所
	   有写入资源的情况必定是互斥的。少数情况是指可以允许多个访问者同时访问资源

	关键段可以用于线程间的互斥，但不可以用于同步

	可以将关键段比作旅馆的房卡，调用EnterCriticalSection()即申请房卡，
	得到房卡后自己当然是可以多次进出房间的，在你调用LeaveCriticalSection()
	交出房卡之前，别人自然是无法进入该房间。

	1．关键段共初始化化、销毁、进入和离开关键区域四个函数。
	2．关键段可以解决线程的互斥问题，但因为具有“线程所有权”，所以无法解决同步问题。
	3．推荐关键段与旋转锁配合使用。
*/

long g_nNum;
const int THREAD_NUM = 10;
//关键段变量声明  
CRITICAL_SECTION  g_csThreadParameter, g_csThreadCode;

unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM; 
	LeaveCriticalSection(&g_csThreadParameter);//离开子线程序号关键区域  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);//进入各子线程互斥区域  
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//离开各子线程互斥区域  
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//关键段初始化  
	InitializeCriticalSection(&g_csThreadParameter);
	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		EnterCriticalSection(&g_csThreadParameter);//进入子线程序号关键区域  
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		++i;
		printf("i: %4d\r\n", i);
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	DeleteCriticalSection(&g_csThreadCode);
	DeleteCriticalSection(&g_csThreadParameter);

	for (i = 0; i < THREAD_NUM; i++)
	{
		CloseHandle(handle[i]);
	}

	return 0;
}

