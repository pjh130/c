// Mutex.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>  
#include <process.h>  
#include <windows.h>  

/*
	1. ���⣺��ָĳһ��Դͬʱֻ����һ�������߶�����з��ʣ�����Ψһ�Ժ������ԡ��������޷����Ʒ����߶���Դ�ķ���˳�򣬼������������
	2. ͬ������ָ�ڻ���Ļ����ϣ�������������ͨ����������ʵ�ַ����߶���Դ��������ʡ��ڴ��������£�ͬ���Ѿ�ʵ���˻��⣬�ر�����
	   ��д����Դ������ض��ǻ���ġ����������ָ����������������ͬʱ������Դ

	������Ҳ��һ���ں˶���������ȷ��һ���̶߳�ռһ����Դ�ķ��ʡ���������ؼ��ε���Ϊ�ǳ����ƣ�
	���һ������������ڲ�ͬ�����е��̻߳��������Դ��

	1�����������ں˶�������ؼ��ζ��С��߳�����Ȩ�����Բ��������̵߳�ͬ����
	2���������ܹ����ڶ������֮���̻߳������⣬�����������Ľ��ĳ����������ֹ����ɵġ����������⡣
*/

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//��������ؼ���  
HANDLE  g_hThreadParameter;
CRITICAL_SECTION g_csThreadCode;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("     �����߳�ͬ�� ������Mutex\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

	//��ʼ����������ؼ��� �ڶ�������ΪTRUE��ʾ������Ϊ�����߳�����
	//��һ��������ʾ����Ȩ�ޣ��Ի�����һ�㴫��MUTEX_ALL_ACCESS����ϸ���Ϳ��Բ鿴MSDN�ĵ���
	//�ڶ���������ʾ����������̳��ԣ�һ�㴫��TRUE���ɡ�
	//������������ʾ���ơ�ĳһ�������е��̴߳��������������������е��߳̾Ϳ���ͨ������������ҵ������������
	g_hThreadParameter = CreateMutex(NULL, FALSE, NULL);

	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadParameter, INFINITE); //�ȴ�������������  
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	//���ٻ������͹ؼ���  
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
	ReleaseMutex(g_hThreadParameter);//����������  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;
}

