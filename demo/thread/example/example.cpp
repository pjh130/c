// example.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <process.h>
#include <stdio.h>
#include <Windows.h>

int g_nCount;

//子线程函数  
DWORD WINAPI ThreadFun1(LPVOID pM)
{
	printf("子线程的线程ID号为：%d\n", GetCurrentThreadId());
	return 0;
}

//子线程函数  
unsigned int __stdcall ThreadFun2(PVOID pM)
{
	g_nCount++;
	printf("线程ID号为%4d的子线程报数%d\n", GetCurrentThreadId(), g_nCount);
	return 0;
}

void Test1();
void Test2();

int main(int argc, _TCHAR* argv[])
{
	printf("最简单的创建多线程实例\n");

	Test1();
	Test2();

	return 0;
}

//CreateThread()函数是Windows提供的API接口
void Test1()
{
	/*
	函数说明：
	第一个参数表示线程内核对象的安全属性，一般传入NULL表示使用默认设置。
	第二个参数表示线程栈空间大小。传入0表示使用默认大小（1MB）。
	第三个参数表示新线程所执行的线程函数地址，多个线程可以使用同一个函数地址。
	第四个参数是传给线程函数的参数。
	第五个参数指定额外的标志来控制线程的创建，为0表示线程创建之后立即就可以进行调度，如果为CREATE_SUSPENDED则表示线程创建后暂停运行，这样它就无法调度，直到调用ResumeThread()。
	第六个参数将返回线程的ID号，传入NULL表示不需要返回该线程ID号。
	函数返回值：
	成功返回新线程的句柄，失败返回NULL。*/
	HANDLE handle = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);

	/*
	函数说明：
	第一个参数为要等待的内核对象。
	第二个参数为最长等待的时间，以毫秒为单位，如传入5000就表示5秒，传入0就立即返回，传入INFINITE表示无限等待。*/
	WaitForSingleObject(handle, INFINITE);
}

//在C/C++语言另有一个创建线程的函数_beginthreadex()，在很多书上（包括《Windows核心编程》）提到过尽量使用_beginthreadex()来代替使用CreateThread()
void Test2()
{
	g_nCount = 0;
	const int THREAD_NUM = 10;
	HANDLE handle[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++)
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun2, NULL, 0, NULL);
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
}



