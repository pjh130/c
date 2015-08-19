#pragma once

struct Node
{
	int iData;
	Node *pNext;
};

class List
{
private:
	Node *pHeader;
public:
	List();
	~List();

	void printfList();//打印链表
	void insertList(int iData);//链表结点的插入
	void deleteList(int iData, bool bDelAll = true);//链表结点的删除
	Node* searchList(int iData); //查找链表
	void sortList(bool bAsc = true); //链表排序
	void reverseList();

	int lengthList();
	Node* getHead(){ return pHeader; }
};

