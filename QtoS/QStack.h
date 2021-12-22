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
QStack<ElemType>::QStack():cur(0)
{
	q[0] = SeqQueue<ElemType>();
	q[1] = SeqQueue<ElemType>();
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
	cout<<emp1<<endl;
	cout<<emp2<<endl;
	if (emp1 == 0 && emp2 == 0)	
		return 0;
	else if (emp1 == 0 || emp2 == 0)	
		return 1;
	else 
		return 2;
}

template<class ElemType>
Status QStack<ElemType>::Pop(ElemType& e)		//弹出"栈"顶元素
{
	if (IsEmpty()==0)	 
		return UNDER_FLOW;
	else 
	{ 
		q[cur].DelQueue(e); 
		return SUCCESS;
	}
}

template<class ElemType>
Status QStack<ElemType>::Top(ElemType& e) const
{
	if (IsEmpty()==0)	 
		return UNDER_FLOW;
	else 
	{ 
		q[cur].GetHead(e); 
		return SUCCESS;
	}
}

template<class ElemType>
Status QStack<ElemType>::Push(const ElemType e)
{
	q[1-cur].EnQueue(e);
	ElemType rest;
	while(q[cur].IsEmpty()==0)
	{
		q[cur].DelQueue(rest); 
		q[1-cur].EnQueue(rest);
	}
	cur = (cur+1)%2;
	return SUCCESS;
}

template<class ElemType>
void QStack<ElemType>::Traverse(void (*Visit)(const ElemType&)) const
{
	q[cur].Traverse(Write<ElemType>);
}

template<class ElemType>
void QStack<ElemType>::Clear()
{
	q[0].Clear();
	q[1].Clear();
}
