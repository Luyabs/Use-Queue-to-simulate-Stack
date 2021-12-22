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
	int cur;	//当前队列 当一条表为空时 cur应指向有数据的表
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

template<class ElemType>
bool QStack<ElemType>::IsEmpty() const		//case = 0 两条队列是否全空?;	case = 1 至少有一条队列为空?；	case = 2 有且仅有一条空队列? 
{
	bool emp1 = q[0].IsEmpty();
	bool emp2 = q[1].IsEmpty();

	if (emp1 & emp2 == 0)	return 0;
	else if (emp1 | emp2 == 0)	return 1;
	else if (emp1 ^ emp2 == 0)	return 2;
}

template<class ElemType>
Status QStack<ElemType>::Pop(ElemType& e)		//弹出"栈"顶元素
{
	if (IsEmpty())	 
		return UNDER_FLOW;
	else 
	{ 
		e = q[cur].DelQueue(); 
		return SUCCESS;
	}
}



