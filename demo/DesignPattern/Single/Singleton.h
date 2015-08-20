#pragma once

class Singleton
{
public:
	Singleton();
	~Singleton();
	
private:
	//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
	Singleton(const Singleton&);
	static Singleton *m_pInstance;

public:
	static Singleton *GetInstance();
	
};
