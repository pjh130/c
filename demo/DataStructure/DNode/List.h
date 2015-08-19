#pragma once

struct DNode
{
	int iData;
	DNode *pPre;
	DNode *pNext;
};

class List
{
private:
	DNode *pHeader;
public:
	List();
	~List();

	void printfList();//打印链表
	void insertList(int iData);//链表结点的插入
	void deleteList(int iData, bool bDelAll = true);//链表结点的删除
	DNode* searchList(int iData); //查找链表
	void sortList(bool bAsc = true); //链表排序
	void reverseList();

	int lengthList();
	DNode* getHead(){ return pHeader; }
};

