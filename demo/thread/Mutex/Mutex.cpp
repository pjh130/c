// Mutex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>  
#include <process.h>  
#include <windows.h>  

/*
	1. 互斥：是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的
	2. 同步：是指在互斥的基础上（大多数情况），通过其它机制实现访问者对资源的有序访问。在大多数情况下，同步已经实现了互斥，特别是所
	   有写入资源的情况必定是互斥的。少数情况是指可以允许多个访问者同时访问资源

	互斥量也是一个内核对象，它用来确保一个线程独占一个资源的访问。互斥量与关键段的行为非常相似，
	并且互斥量可以用于不同进程中的线程互斥访问资源。

	1．互斥量是内核对象，它与关键段都有“线程所有权”所以不能用于线程的同步。
	2．互斥量能够用于多个进程之间线程互斥问题，并且能完美的解决某进程意外终止所造成的“遗弃”问题。
*/

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//互斥量与关键段  
HANDLE  g_hThreadParameter;
CRITICAL_SECTION g_csThreadCode;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("     经典线程同步 互斥量Mutex\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	//初始化互斥量与关键段 第二个参数为TRUE表示互斥量为创建线程所有
	//第一个参数表示访问权限，对互斥量一般传入MUTEX_ALL_ACCESS。详细解释可以查看MSDN文档。
	//第二个参数表示互斥量句柄继承性，一般传入TRUE即可。
	//第三个参数表示名称。某一个进程中的线程创建互斥量后，其它进程中的线程就可以通过这个函数来找到这个互斥量。
	g_hThreadParameter = CreateMutex(NULL, FALSE, NULL);

	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadParameter, INFINITE); //等待互斥量被触发  
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	//销毁互斥量和关键段  
	CloseHandle(g_hThreadParameter);
	DeleteCriticalSection(&g_csThreadCode);

	for (i = 0; i < THREAD_NUM; i++)
	{
		CloseHandle(handle[i]);
	}

	return 0;
}

unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM;
	ReleaseMutex(g_hThreadParameter);//触发互斥量  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;
}

