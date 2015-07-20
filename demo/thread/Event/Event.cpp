// Event.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>  
#include <process.h>  
#include <windows.h>  

/*
	1. 互斥：是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的
	2. 同步：是指在互斥的基础上（大多数情况），通过其它机制实现访问者对资源的有序访问。在大多数情况下，同步已经实现了互斥，特别是所
	   有写入资源的情况必定是互斥的。少数情况是指可以允许多个访问者同时访问资源

	1．事件是内核对象，事件分为手动置位事件和自动置位事件。事件Event内部它包含一个使用计数（所有内核对象都有），
	   一个布尔值表示是手动置位事件还是自动置位事件，另一个布尔值用来表示事件有无触发。
	2．事件可以由SetEvent()来触发，由ResetEvent()来设成未触发。还可以由PulseEvent()来发出一个事件脉冲。
	3．事件可以解决线程间同步问题，因此也能解决互斥问题。

	在经典多线程问题中设置一个事件和一个关键段。用事件处理主线程与子线程的同步，用关键段来处理各子线程间的互斥
*/

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//事件与关键段  
HANDLE  g_hThreadEvent;
CRITICAL_SECTION g_csThreadCode;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("     经典线程同步 事件Event\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");
	//初始化事件和关键段 自动置位,初始无触发的匿名事件  
	g_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadEvent, INFINITE); //等待事件被触发  
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	//销毁事件和关键段  
	CloseHandle(g_hThreadEvent);
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
	SetEvent(g_hThreadEvent); //触发事件  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;
}

