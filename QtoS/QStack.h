#pragma once
#include "SeqQueue.h"
#include "Assistance.h"	// 辅助软件包




template<class ElemType> class QStack
{
public:
	QStack();
	virtual ~QStack();
	int GetLength() const;							// 求栈的长度			 
	bool IsEmpty() const;							// 判断栈是否为空
	void Clear();									// 将栈清空
	void Traverse(void (*Visit)(const ElemType&)) const;	// 遍历栈
	Status Push(const ElemType e);				    // 入栈
	Status Top(ElemType& e) const;				    // 取顶元素
	Status Pop(ElemType& e);					    // 出栈
	QStack(const QStack<ElemType>& s);		// 复制构造函数
	QStack<ElemType>& operator =(const QStack<ElemType>& s); // 赋值语句重载

private:
	SeqQueue<ElemType> q[2];
	int top;
	int maxsize;
};

template<class ElemType>
QStack<ElemType>::QStack()
{
}


template<class ElemType>
QStack<ElemType>::~QStack()
{
}






