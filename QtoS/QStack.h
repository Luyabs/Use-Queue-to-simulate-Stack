#pragma once
#include "SeqQueue.h"
#include "Assistance.h"	// 辅助软件包
#include <iostream>
#include <fstream>

template<class ElemType> class QStack
{
public:
	QStack();
	virtual ~QStack();
	int GetLength() const;							// 求栈的长度			 
	bool IsEmpty(int mode = 1) const;				// 判断栈中队列是否为空 //mode = 1 两条队列是否全空(栈为空)?	mode = 2 至少有一条队列为空?	mode = 3 有且仅有一条空队列? 
	bool IsFull(int mode = 1) const;				// 判断栈中队列是否已满 //mode = 1 两条队列是否全满队?	  mode = 2 有且仅有一条队列满队?
	Status Clear();									// 将栈清空
	void Traverse(void (*Visit)(const ElemType&)) const;	// 遍历栈
	Status Push_Switch(const ElemType e);				    // 入栈_左手倒右手 时间复杂度O(n^2)
	void Push_Merge();										// 入栈_归并倒置 时间复杂度O(nlogn)
	Status Push_Solo(const ElemType e);						// 入栈_单队列操作 时间复杂度O(n^2)
	void Push(ElemType stop, int size = 100, istream& in = cin);	 // 整合版入栈Push 参数分别为:终止符/数据大小/输入流
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
bool QStack<ElemType>::IsFull(int mode) const	//mode = 1 两条队列是否全满队?	mode = 2 有且仅有一条队列满队? 
{
	bool emp1 = q[0].IsFull();
	bool emp2 = q[1].IsFull();
	switch (mode)
	{
	case 1:
		return(emp1 && emp2) == 1;
	case 2:
		return(emp1 ^ emp2) == 1;
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
Status QStack<ElemType>::Push_Switch(const ElemType e)
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
void QStack<ElemType>::Push(ElemType stop, int size, istream& in)
{
	ElemType buffer;
	ElemType *e = new ElemType[size];
	int length;
	int edge = 2048;		//！！！此处需要通过分析数据找到合适的数字，暂定2048  if else 的判定条件也应该更复杂 需要考虑"栈"中原来有多少元素(需添加函数中的临时变量)
	int process = 1;

	for (length = 0; length < maxsize; length++)
	{
		in >> buffer;	//当输入-999时退出录入数据
		if (buffer = stop)
			break;
		e[length] = buffer;
	}
	if (length < edge)
	{
		for (int i = 0; i < length; i++)
		{
			switch (process)
			{
			case 1:
				if (IsFull(2) == 0)		//至少有一条队列为空 
					Push_Switch(e[i]);
				else
				{
					process = 2;
					cur = 1 - cur;
				}
				break;
			case 2:
				if (IsFull(1) == 0)		//有一条队列已满 调用单队列作栈法
					Push_Solo(e[i]);
				else
					return OVERFLOW;	//栈满溢出
				break;
			default:
				break;
			}
		}
	}
	else if (length >= edge)
	{
		for (int i = 0; i < length; i++)
		{
			switch (case)
			{
			case 1:
				if (IsFull(2) == 0)		//至少有一条队列为空
					q[cur].EnQueue(e[i]);	//将数据全插进去
				else
				{
					process = 2;
					Push_Merge();		//调用归并法倒置队列
					cur = 1 - cur;
				}
				break;
			case 2:
				if (IsFull(1) == 0)		//有一条队列已满 调用单队列作栈法
					Push_Solo(e[i]);
				break;
			default:
				break;
			}


		}
	}
	delete e;
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


