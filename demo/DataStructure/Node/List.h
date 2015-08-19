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

	void printfList();//��ӡ����
	void insertList(int iData);//������Ĳ���
	void deleteList(int iData, bool bDelAll = true);//�������ɾ��
	Node* searchList(int iData); //��������
	void sortList(bool bAsc = true); //��������
	void reverseList();

	int lengthList();
	Node* getHead(){ return pHeader; }
};

