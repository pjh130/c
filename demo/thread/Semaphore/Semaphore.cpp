// Semaphore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>  
#include <process.h>  
#include <windows.h>  

/*
	1. 互斥：是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的
	2. 同步：是指在互斥的基础上（大多数情况），通过其它机制实现访问者对资源的有序访问。在大多数情况下，同步已经实现了互斥，特别是所
	   有写入资源的情况必定是互斥的。少数情况是指可以允许多个访问者同时访问资源
*/

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//信号量与关键段  
HANDLE            g_hThreadParameter;
CRITICAL_SECTION  g_csThreadCode;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("     经典线程同步 信号量Semaphore\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	//初始化信号量和关键段  
	//第一个参数表示安全控制，一般直接传入NULL。
	//第二个参数表示初始资源数量。
	//第三个参数表示最大并发数量。
	//第四个参数表示信号量的名称，传入NULL表示匿名信号量。
	g_hThreadParameter = CreateSemaphore(NULL, 0, 1, NULL);//当前0个资源，最大允许1个同时访问  
	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadParameter, INFINITE);//等待信号量>0  
		++i;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	//销毁信号量和关键段  
	DeleteCriticalSection(&g_csThreadCode);
	CloseHandle(g_hThreadParameter);
	for (i = 0; i < THREAD_NUM; i++)
		CloseHandle(handle[i]);

	return 0;
}

unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM;
	ReleaseSemaphore(g_hThreadParameter, 1, NULL);//信号量++  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);
	++g_nNum;
	Sleep(0);//some work should to do  
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;
}

