#include "stdafx.h"
#include "List.h"


List::List()
{
	pHeader = NULL;
}


List::~List()
{
}

void List::printfList()
{
	
}
void List::insertList(int iData)
{
	DNode *pNew = new DNode;
	pNew->pNext = NULL;
	pNew->pPre = NULL;
	pNew->iData = iData;

	if (NULL == pHeader)
	{
		pHeader = pNew;
		return;
	}
	else {
		//在最前边插入
		pHeader->pPre = pNew;
		pNew->pNext = pHeader;
		pHeader = pNew;
	}
}
void List::deleteList(int iData, bool bDelAll)
{

}
DNode* List::searchList(int iData)
{

}
void List::sortList(bool bAsc)
{

}
void List::reverseList()
{

}

int List::lengthList()
{

}
