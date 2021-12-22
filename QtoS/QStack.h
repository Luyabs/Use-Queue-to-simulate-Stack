#pragma once
#include "SeqQueue.h"
#include "Assistance.h"	// ���������




template<class ElemType> class QStack
{
public:
	QStack();
	virtual ~QStack();
	int GetLength() const;							// ��ջ�ĳ���			 
	bool IsEmpty() const;							// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
	void Traverse(void (*Visit)(const ElemType&)) const;	// ����ջ
	Status Push(const ElemType e);				    // ��ջ
	Status Top(ElemType& e) const;				    // ȡ��Ԫ��
	Status Pop(ElemType& e);					    // ��ջ
	QStack(const QStack<ElemType>& s);		// ���ƹ��캯��
	QStack<ElemType>& operator =(const QStack<ElemType>& s); // ��ֵ�������

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






