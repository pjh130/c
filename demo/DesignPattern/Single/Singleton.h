#pragma once

class Singleton
{
public:
	Singleton();
	~Singleton();
	
private:
	//把复制构造函数和=操作符也设为私有,防止被复制
	Singleton(const Singleton&);
	static Singleton *m_pInstance;

public:
	static Singleton *GetInstance();
	
};
