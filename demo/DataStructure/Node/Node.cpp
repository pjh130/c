// Node.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "List.h"

int _tmain(int argc, _TCHAR* argv[])
{
	List *pTest = new List;

	pTest->insertList(10);
	pTest->insertList(9);
	pTest->insertList(8);
	pTest->insertList(7);
	pTest->insertList(6);
	pTest->insertList(5);
	pTest->insertList(4);
	pTest->insertList(3);
	pTest->insertList(2);
	pTest->insertList(1);

	pTest->insertList(7);
	pTest->insertList(8);
	pTest->insertList(6);
	pTest->insertList(4);
	pTest->insertList(5);

	pTest->printfList();

	pTest->sortList();
	pTest->printfList();
	

	pTest->sortList(false);
	pTest->printfList();
	

	pTest->reverseList();
	pTest->printfList();

	pTest->deleteList(1, true);
	pTest->deleteList(4, true);
	pTest->deleteList(100, true);
	pTest->deleteList(7, true);
	pTest->deleteList(10, true);
	pTest->deleteList(10111, true);
	//pTest->deleteList(4, false);
	//pTest->deleteList(7, false);
	pTest->printfList();

	delete pTest;

	return 0;
}

