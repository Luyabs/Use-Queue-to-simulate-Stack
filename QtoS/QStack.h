#pragma once
#include "SeqQueue.h"
#include "Assistance.h"	// 辅助软件包

template<class ElemType> class QStack
{
public:
	QStack();
	virtual ~QStack();
	int GetLength() const;							// 求栈的长度			 
	bool IsEmpty(int mode = 1) const;				// 判断栈中队列是否为空 //mode = 1 两条队列是否全空(栈为空)?	mode = 2 至少有一条队列为空?	mode = 3 有且仅有一条空队列? 
	bool IsFull(int mode = 1) const;				// 判断栈中队列是否已满 
	Status Clear();									// 将栈清空
	void Traverse(void (*Visit)(const ElemType&)) const;	// 遍历栈
	Status Push(const ElemType e);				    // 入栈
	Status Top(ElemType& e) const;				    // 取顶元素
	Status Pop(ElemType& e);					    // 出栈 用e接收弹出的元素
	QStack(const QStack<ElemType>& s);		// 复制构造函数
	QStack<ElemType>& operator =(const QStack<ElemType>& s); // 赋值语句重载

private:
	SeqQueue<ElemType>* q;
	int cur;	//当前队列 当一条表为空时 cur应指向有数据的表
	int maxsize;
};

template<class ElemType>
QStack<ElemType>::QStack() :maxsize(2 * DEFAULT_SIZE), cur(0)
{
	q = new SeqQueue<ElemType>[2];
}

template<class ElemType>
QStack<ElemType>::~QStack()
{
	delete[]q;
}

template<class ElemType>
int QStack<ElemType>::GetLength() const
{
	int count = 0;
	for (int i = 0; i < 2; i++)
		for (int j = q[i].front; j != q[i].rear; j = (j + 1) % q[i].maxSize)
			count++;
	return count;
}

template<class ElemType>
bool QStack<ElemType>::IsEmpty(int mode) const		//mode = 1 两条队列是否全空(栈为空)?	mode = 2 至少有一条队列为空?	mode = 3 有且仅有一条空队列? 
{
	bool emp1 = q[0].IsEmpty();
	bool emp2 = q[1].IsEmpty();
	switch (mode)
	{
	case 1:
		return (emp1 && emp2) == 1;
	case 2:
		return (emp1 || emp2) == 1;
	case 3:
		return (emp1 ^ emp2) == 1;
	default:
		break;
	}
}

template<class ElemType>
Status QStack<ElemType>::Clear()
{
	for (int i = 0; i < 2; i++)
	{
		while (q[i].IsEmpty() == 0)
		{
			q[i].Clear();
		}
	}
	if (IsEmpty() == 1)
		return SUCCESS;
	else
		return FAIL;
}

template<class ElemType>
void QStack<ElemType>::Traverse(void (*Visit)(const ElemType&)) const
{
	int temp = cur;
	for (int i = q[temp].front; i != q[temp].rear; i = (i + 1) % q[temp].maxSize)
		(*Visit)(q[temp].elems[i]);
	temp = 1 - temp;
	for (int i = q[temp].front; i != q[temp].rear; i = (i + 1) % q[temp].maxSize)
		(*Visit)(q[temp].elems[i]);
}

template<class ElemType>
Status QStack<ElemType>::Push(const ElemType e)
{
	int L = q[cur].GetLength();
	if (L <= q[cur].maxSize)
	{
		q[1 - cur].EnQueue(e);
		ElemType t;
		for (int i = 0; i < L; i++)
		{
			q[cur].DelQueue(t);
			q[1 - cur].EnQueue(t);
		}
		cur = 1 - cur;
		return SUCCESS;
	}
	else
	{
		return Status();
	}
}

template<class ElemType>
Status QStack<ElemType>::Top(ElemType& e) const
{
	if (IsEmpty(1))	 // 栈空
		return UNDER_FLOW;
	else { // 栈非空,操作成功
		q[cur].GetHead(e);	// 用e返回栈顶元素
		return SUCCESS;
	}
}

template<class ElemType>
Status QStack<ElemType>::Pop(ElemType& e)		//弹出"栈"顶元素
{
	if (IsEmpty(1))
		return UNDER_FLOW;
	else
	{
		q[cur].DelQueue(e);
		return SUCCESS;
	}
}

template<class ElemType>
QStack<ElemType>::QStack(const QStack<ElemType>& s)
{
	maxsize = s.maxsize;
	cur = s.cur;
	q = new SeqQueue<ElemType>[2];		
	for (int i = 0; i < 2; i++)
		q[i] = s.q[i];
}

template<class ElemType>
QStack<ElemType>& QStack<ElemType>::operator =(const QStack<ElemType>& s)
{
	if (&s != this) 
	{
		maxsize = s.maxsize;
		cur = s.cur;
		if (IsEmpty(1) != 0)
			Clear();
		q = new SeqQueue<ElemType>[2];
		for (int i = 0; i < 2; i++)
			q[i] = s.q[i];
	}
	return *this;
}


