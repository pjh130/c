// Event.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>  
#include <process.h>  
#include <windows.h>  

/*
	1. ���⣺��ָĳһ��Դͬʱֻ����һ�������߶�����з��ʣ�����Ψһ�Ժ������ԡ��������޷����Ʒ����߶���Դ�ķ���˳�򣬼������������
	2. ͬ������ָ�ڻ���Ļ����ϣ�������������ͨ����������ʵ�ַ����߶���Դ��������ʡ��ڴ��������£�ͬ���Ѿ�ʵ���˻��⣬�ر�����
	   ��д����Դ������ض��ǻ���ġ����������ָ����������������ͬʱ������Դ

	1���¼����ں˶����¼���Ϊ�ֶ���λ�¼����Զ���λ�¼����¼�Event�ڲ�������һ��ʹ�ü����������ں˶����У���
	   һ������ֵ��ʾ���ֶ���λ�¼������Զ���λ�¼�����һ������ֵ������ʾ�¼����޴�����
	2���¼�������SetEvent()����������ResetEvent()�����δ��������������PulseEvent()������һ���¼����塣
	3���¼����Խ���̼߳�ͬ�����⣬���Ҳ�ܽ���������⡣

	�ھ�����߳�����������һ���¼���һ���ؼ��Ρ����¼��������߳������̵߳�ͬ�����ùؼ�������������̼߳�Ļ���
*/

long g_nNum;
unsigned int __stdcall Fun(void *pPM);
const int THREAD_NUM = 10;
//�¼���ؼ���  
HANDLE  g_hThreadEvent;
CRITICAL_SECTION g_csThreadCode;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("     �����߳�ͬ�� �¼�Event\n");
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");
	//��ʼ���¼��͹ؼ��� �Զ���λ,��ʼ�޴����������¼�  
	g_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&g_csThreadCode);

	HANDLE  handle[THREAD_NUM];
	g_nNum = 0;
	int i = 0;
	while (i < THREAD_NUM)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		WaitForSingleObject(g_hThreadEvent, INFINITE); //�ȴ��¼�������  
		i++;
	}
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);

	//�����¼��͹ؼ���  
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
	SetEvent(g_hThreadEvent); //�����¼�  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&g_csThreadCode);
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;
}

