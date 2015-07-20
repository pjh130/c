// CriticalSection.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <process.h>
#include <Windows.h>

/*
	1. ���⣺��ָĳһ��Դͬʱֻ����һ�������߶�����з��ʣ�����Ψһ�Ժ������ԡ��������޷����Ʒ����߶���Դ�ķ���˳�򣬼������������
	2. ͬ������ָ�ڻ���Ļ����ϣ�������������ͨ����������ʵ�ַ����߶���Դ��������ʡ��ڴ��������£�ͬ���Ѿ�ʵ���˻��⣬�ر�����
	   ��д����Դ������ض��ǻ���ġ����������ָ����������������ͬʱ������Դ

	�ؼ��ο��������̼߳�Ļ��⣬������������ͬ��

	���Խ��ؼ��α����ùݵķ���������EnterCriticalSection()�����뷿����
	�õ��������Լ���Ȼ�ǿ��Զ�ν�������ģ��������LeaveCriticalSection()
	��������֮ǰ��������Ȼ���޷�����÷��䡣

	1���ؼ��ι���ʼ���������١�������뿪�ؼ������ĸ�������
	2���ؼ��ο��Խ���̵߳Ļ������⣬����Ϊ���С��߳�����Ȩ���������޷����ͬ�����⡣
	3���Ƽ��ؼ�������ת�����ʹ�á�
*/

long g_nNum;
const int THREAD_NUM = 10;
//�ؼ��α�������  
CRITICAL_SECTION  g_csThreadParameter, g_csThreadCode;

unsigned int __stdcall Fun(void *pPM)
{
	int nThreadNum = *(int *)pPM; 
	LeaveCriticalSection(&g_csThreadParameter);//�뿪���߳���Źؼ�����  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);//��������̻߳�������  
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);//�뿪�����̻߳�������  
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//�ؼ��γ�ʼ��  
	InitializeCriticalSection(&g_csThreadParameter);
	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		EnterCriticalSection(&g_csThreadParameter);//�������߳���Źؼ�����  
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

