#include "stdafx.h"
#include "List.h"
#include <stdio.h>


List::List()
{
	pHeader = NULL;
}


List::~List()
{
	printf("start delete item ...\n");
	Node *pTemp = pHeader;
	while (NULL != pTemp)
	{
		Node *pDel = pTemp;
		pTemp = pTemp->pNext;
		printf(" %d ", pDel->iData);
		delete pDel;
	}
	printf("\nstart delete item finish\n");
}

void List::printfList()
{
	Node *pTemp = pHeader;
	while (NULL != pTemp )
	{
		printf(" %2d ", pTemp->iData);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

void List::insertList(int iData)
{
	Node *pNew = new Node;
	pNew->iData = iData;

	pNew->pNext = pHeader;
	pHeader = pNew;
}

void List::deleteList(int iData, bool bDelAll)
{
	Node *pCurr = pHeader;
	Node *pBefore = NULL;
	while (pCurr != NULL)
	{
		Node *pDel = NULL;
		//找到
		if (iData == pCurr->iData)
		{
			pDel = pCurr;

			//如果删除的是头节点
			if (pCurr == pHeader)
			{
				pHeader = pHeader->pNext;
			}
			else {
				pBefore->pNext = pCurr->pNext;
			}

			if (true == bDelAll)
			{
				pCurr = pCurr->pNext;
				delete pDel;
				continue;
			}
			else {
				delete pDel;
				return;
			}

		} 

		pBefore = pCurr;
		pCurr = pCurr->pNext;

	}
}
Node* List::searchList(int iData)
{
	Node *pTemp = pHeader;
	while (pTemp != NULL)
	{
		//找到
		if (iData == pTemp->iData)
		{
			return  pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
}

void List::sortList(bool bAsc)
{
	////如果只有一个或者没有节点,不需要排序
	if (NULL == pHeader || NULL == pHeader->pNext)
	{
		return;
	}

	int n = lengthList();

	Node *pCurr = NULL;
	Node *pBefore = NULL;

	//
	for (int i = 0; i < n; i++)
	{
		pCurr = pHeader;
		pBefore = NULL;
		for (int j = 0; j < n-i; j++)
		{
			Node *pNext = pCurr->pNext;
			if (NULL != pNext)
			{
				bool bChangeData = true;
				if (true == bAsc)
				{
					//printf("curr:%d   next:%d\n", pCurr->iData, pNext->iData);
					if (pCurr->iData > pNext->iData)
					{
						if (bChangeData)
						{
							//不需要交换节点，只需要交换节点里边的内容
							int iTemp = pCurr->iData;
							pCurr->iData = pNext->iData;
							pNext->iData = iTemp;
						}
						else {
							//交换指针
							//头节点
							if (NULL == pBefore)
							{
								pHeader = pNext;
								printf("header:%d\n", pHeader->iData);
								pCurr->pNext = pNext->pNext;
								pHeader->pNext = pCurr;

								pBefore = pHeader;
								continue;
							}
							else {
								pBefore->pNext = pNext;
								pCurr->pNext = pNext->pNext;
								pNext->pNext = pCurr;

								pBefore = pNext;
								continue;
							}
						}
					}
				}
				else {
					if (pCurr->iData < pNext->iData)
					{
						if (bChangeData)
						{
							//不需要交换节点，只需要交换节点里边的内容
							int iTemp = pCurr->iData;
							pCurr->iData = pNext->iData;
							pNext->iData = iTemp;
						}
						else {
							//交换指针
							//头节点
							if (NULL == pBefore)
							{
								pHeader = pNext;
								printf("header:%d\n", pHeader->iData);
								pCurr->pNext = pNext->pNext;
								pHeader->pNext = pCurr;

								pBefore = pHeader;
								continue;
							}
							else {
								pBefore->pNext = pNext;
								pCurr->pNext = pNext->pNext;
								pNext->pNext = pCurr;

								pBefore = pNext;
								continue;
							}
						}
					}
				}
			}

			pBefore = pCurr;
			pCurr = pCurr->pNext;
		}
	}
}

int List::lengthList()
{
	int n = 0;
	Node *pTemp = pHeader;
	while (NULL != pTemp)
	{
		pTemp = pTemp->pNext;
		n++;
	}
	//printf("length:%d\n", n);
	return n;
}

void List::reverseList()
{
	Node *p1 = NULL;
	Node *p2 = NULL;
	Node *p3 = NULL;

	if (NULL == pHeader || NULL == pHeader->pNext)
	{
		return;
	}

	p1 = pHeader;
	p2 = p1->pNext;

	while (p2)
	{
		p3 = p2->pNext;
		p2->pNext = p1;
		p1 = p2;
		p2 = p3;
	}

	pHeader->pNext = NULL;
	pHeader = p1;
}
