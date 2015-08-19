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

	void printfList();//��ӡ����
	void insertList(int iData);//������Ĳ���
	void deleteList(int iData, bool bDelAll = true);//�������ɾ��
	DNode* searchList(int iData); //��������
	void sortList(bool bAsc = true); //��������
	void reverseList();

	int lengthList();
	DNode* getHead(){ return pHeader; }
};

