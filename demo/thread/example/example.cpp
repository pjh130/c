// example.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>
#include <stdio.h>
#include <Windows.h>

int g_nCount;

//���̺߳���  
DWORD WINAPI ThreadFun1(LPVOID pM)
{
	printf("���̵߳��߳�ID��Ϊ��%d\n", GetCurrentThreadId());
	return 0;
}

//���̺߳���  
unsigned int __stdcall ThreadFun2(PVOID pM)
{
	g_nCount++;
	printf("�߳�ID��Ϊ%4d�����̱߳���%d\n", GetCurrentThreadId(), g_nCount);
	return 0;
}

void Test1();
void Test2();

int main(int argc, _TCHAR* argv[])
{
	printf("��򵥵Ĵ������߳�ʵ��\n");

	Test1();
	Test2();

	return 0;
}

//CreateThread()������Windows�ṩ��API�ӿ�
void Test1()
{
	/*
	����˵����
	��һ��������ʾ�߳��ں˶���İ�ȫ���ԣ�һ�㴫��NULL��ʾʹ��Ĭ�����á�
	�ڶ���������ʾ�߳�ջ�ռ��С������0��ʾʹ��Ĭ�ϴ�С��1MB����
	������������ʾ���߳���ִ�е��̺߳�����ַ������߳̿���ʹ��ͬһ��������ַ��
	���ĸ������Ǵ����̺߳����Ĳ�����
	���������ָ������ı�־�������̵߳Ĵ�����Ϊ0��ʾ�̴߳���֮�������Ϳ��Խ��е��ȣ����ΪCREATE_SUSPENDED���ʾ�̴߳�������ͣ���У����������޷����ȣ�ֱ������ResumeThread()��
	�����������������̵߳�ID�ţ�����NULL��ʾ����Ҫ���ظ��߳�ID�š�
	��������ֵ��
	�ɹ��������̵߳ľ����ʧ�ܷ���NULL��*/
	HANDLE handle = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);

	/*
	����˵����
	��һ������ΪҪ�ȴ����ں˶���
	�ڶ�������Ϊ��ȴ���ʱ�䣬�Ժ���Ϊ��λ���紫��5000�ͱ�ʾ5�룬����0���������أ�����INFINITE��ʾ���޵ȴ���*/
	WaitForSingleObject(handle, INFINITE);
}

//��C/C++��������һ�������̵߳ĺ���_beginthreadex()���ںܶ����ϣ�������Windows���ı�̡����ᵽ������ʹ��_beginthreadex()������ʹ��CreateThread()
void Test2()
{
	g_nCount = 0;
	const int THREAD_NUM = 10;
	HANDLE handle[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++)
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun2, NULL, 0, NULL);
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
}



