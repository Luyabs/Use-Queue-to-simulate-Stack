#pragma once
#include "SeqQueue.h"
#include "Assistance.h"	// ���������
#include <iostream>
#include <fstream>
#include <cmath>


double gettime(int restart = 0);

template<class ElemType> class QStack
{
public:
	QStack();
	virtual ~QStack();
	int GetLength() const;							// ��ջ�ĳ���			 
	bool IsEmpty(int mode = 1) const;				// �ж�ջ�ж����Ƿ�Ϊ�� //mode = 1 ���������Ƿ�ȫ��(ջΪ��)?	mode = 2 ������һ������Ϊ��?	mode = 3 ���ҽ���һ���ն���? 
	bool IsFull(int mode = 1) const;				// �ж�ջ�ж����Ƿ����� //mode = 1 ���������Ƿ�ȫ����?	  mode = 2 ���ҽ���һ����������?
	Status Clear();									// ��ջ���
	void Traverse(void (*Visit)(const ElemType&)) const;	// ����ջ
	Status Push_Switch(const ElemType e);				    // ��ջ_���ֵ����� ʱ�临�Ӷ�O(n^2)
	void Push_Merge(int stacklength = 0);				// stacklength��ԭ��ջ������Ԫ�ص�����	��ջ_�鲢���� ʱ�临�Ӷ�O(nlogn)
	void Push_Merge_Neo(int stacklength = 0);
	Status Push_Solo(const ElemType e);						// ��ջ_�����в��� ʱ�临�Ӷ�O(n^2)
	Status Push_Queue(const ElemType e);
	void Push(ElemType stop, int size = 100, istream& in = cin, int choice = 1);	 // ���ϰ���ջPush �����ֱ�Ϊ:��ֹ��/���ݴ�С/������/choice=1ʱswitch��2ʱMerge,3ʱʹ��Merge_Neo
	Status Top(ElemType& e) const;				    // ȡ��Ԫ��
	Status Pop();					    // �򻯳�ջ �����յ�����Ԫ��
	Status Pop(ElemType& e);					    // ��ջ ��e���յ�����Ԫ��
	QStack(const QStack<ElemType>& s);		// ���ƹ��캯��
	QStack<ElemType>& operator =(const QStack<ElemType>& s); // ��ֵ�������

private:
	SeqQueue<ElemType>* q;
	int cur;	//��ǰ���� ��һ����Ϊ��ʱ curӦָ�������ݵı�
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
bool QStack<ElemType>::IsEmpty(int mode) const		//mode = 1 ���������Ƿ�ȫ��(ջΪ��)?	mode = 2 ������һ������Ϊ��?	mode = 3 ���ҽ���һ���ն���? 
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
		//throw (int)FAIL;
		break;
	}
}

template<class ElemType>
bool QStack<ElemType>::IsFull(int mode) const	//mode = 1 ���������Ƿ�ȫ����?	mode = 2 ���ҽ���һ����������?   mode = 3	���Ӷ��ж�������
{
	bool emp1 = q[0].IsFull();
	bool emp2 = q[1].IsFull();
	switch (mode)
	{
	case 1:
		return emp1 && emp2;
	case 2:
		return emp1 ^ emp2;
	case 3:
		return !emp1 && !emp2;
	default:
		throw (int)FAIL;
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
Status QStack<ElemType>::Push_Solo(const ElemType e)			// ��ջ_�����в��� 
{
	if (IsFull(1))												//ȫ�� �쳣����
		return Status();
	else if (q[cur].IsFull())									//��ǰ�������� ����
		cur = 1 - cur;
	if (q[cur].IsEmpty())										//��Ϊ�� ֱ�Ӳ���
	{
		q[cur].EnQueue(e);
		return SUCCESS;
	}
	int L = q[cur].GetLength();
	if (L <= q[cur].maxSize)
	{
		ElemType t;
		q[cur].DelQueue(t);										//��ɾ�������
		q[cur].EnQueue(e);
		for (int i = 0; i < L - 1; i++)
		{
			q[cur].EnQueue(t);
			q[cur].DelQueue(t);
		}
		q[cur].EnQueue(t);
		return SUCCESS;
	}
	else
	{
		return Status();
	}
}

template<class ElemType>
Status QStack<ElemType>::Push_Queue(const ElemType e)							//�����
{
	if (IsFull(1))												//ȫ�� �쳣����
		return Status();
	else if (q[cur].IsFull())									//��ǰ�������� ����
		cur = 1 - cur;
	q[cur].EnQueue(e);
	return SUCCESS;
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
void QStack<ElemType>::Push_Merge(int stacklength)				// stacklength��ԭ��ջ������Ԫ�ص�����	��ջ_�鲢���� ʱ�临�Ӷ�O(nlogn)
{	//����Ҫȥstacklength������
	ElemType e;			//���ڽ���һ�ε�������
	int length = q[cur].GetLength() - stacklength;	//��Ҫ�鲢���õ�Ԫ������
	int count;
	int templength;			//templengthΪʵ����Ҫ���������
	int c = 1;
	ElemType blank;			//���λ��Ԫ�� ���������2^n���������ݵ����
	Top(blank);				//blank������г�ʼ��
	int sort_num = 1;
	int batch2 = 1;
	for (; sort_num * 2 <= length; sort_num *= 2);
	int unsort_num = length - sort_num;
	for (; batch2 < length - sort_num; batch2 *= 2);
	templength = batch2 - unsort_num;
	if (sort_num == length)
	{
		templength = 0;
		batch2 = 0;
	}
	for (int j = 0; j < templength; j++)		//�������Ϊi�ı���  ���ȷ��maxsize�ǿ��Ա��Ϊ2^m������ 
	{
		q[cur].EnQueue(blank);
	}
	count = sort_num;
	c = batch2;
	for (int i = 2; i <= length; i *= 2)
	{
		//cout << "i:" << i << endl;
		//cout << "tem:" << templength << endl;

		count /= 2; 	//q[cur].Traverse(Write<double>);	cout << endl;
		c /= 2;

		for (int j = 0; j < stacklength; j++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
		//cout << i << endl;
		//cout << count << endl;
		if (c > 0)
		{
			for (int j = 0; j < count; j++)
			{
				for (int k = 0; k < i; k++)		//������������Ԫ����2^k��һ�飬Ų����һ���ձ�
				{
					q[cur].DelQueue(e);
					q[1 - cur].EnQueue(e);  //cout << "������: ";   q[cur].Traverse(Write<double>);	cout << endl;
				}
				for (int k = 0; k < i / 2; k++)	//�ڿձ�������
				{
					q[1 - cur].DelQueue(e);
					q[1 - cur].EnQueue(e);
				}
				for (int k = 0; k < i; k++)		//������ص�ԭ���ı�
				{
					q[1 - cur].DelQueue(e);
					q[cur].EnQueue(e);  //cout << "�ض���: ";  q[cur].Traverse(Write<double>);	cout << endl;
				}
			}
			for (int j = 0; j < c; j++)
			{
				for (int k = 0; k < i; k++)		//������������Ԫ����2^k��һ�飬Ų����һ���ձ�
				{
					q[cur].DelQueue(e);
					q[1 - cur].EnQueue(e);  //cout << "������: ";   q[cur].Traverse(Write<double>);	cout << endl;
				}
				for (int k = 0; k < i / 2; k++)	//�ڿձ�������
				{
					q[1 - cur].DelQueue(e);
					q[1 - cur].EnQueue(e);
				}
				for (int k = 0; k < i; k++)		//������ص�ԭ���ı�
				{
					q[1 - cur].DelQueue(e);
					q[cur].EnQueue(e);  //cout << "�ض���: ";  q[cur].Traverse(Write<double>);	cout << endl;
				}
			}
		}
		else
		{
			for (int j = 0; j < count; j++)
			{
				for (int k = 0; k < i; k++)		//������������Ԫ����2^k��һ�飬Ų����һ���ձ�
				{
					q[cur].DelQueue(e);
					q[1 - cur].EnQueue(e);  //cout << "������: ";   q[cur].Traverse(Write<double>);	cout << endl;
				}
				for (int k = 0; k < i / 2; k++)	//�ڿձ�������
				{
					q[1 - cur].DelQueue(e);
					q[1 - cur].EnQueue(e);
				}
				for (int k = 0; k < i; k++)		//������ص�ԭ���ı�
				{
					q[1 - cur].DelQueue(e);
					q[cur].EnQueue(e);  //cout << "�ض���: ";  q[cur].Traverse(Write<double>);	cout << endl;
				}
			}
			for (int j = 0; j < batch2; j++)
			{
				q[cur].DelQueue(e);
				q[cur].EnQueue(e);
			}
		}


		//cout << "��ǰ�ִ�: ";
		//q[cur].Traverse(Write<double>);	cout << endl;
		//cout << "LOOP" << endl;
	}
	if (batch2 != 0)
	{
		for (int i = 0; i < stacklength; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[cur].DelQueue(e);
			q[1 - cur].EnQueue(e);
		}
		for (int i = 0; i < sort_num; i++)
		{
			q[cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
		for (int i = 0; i < stacklength; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[1 - cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
	}
	for (int i = 0; i < templength; i++)
	{
		q[cur].DelQueue(e);
	}
	for (int i = 0; i < stacklength && batch2 == 0; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
	{
		q[cur].DelQueue(e);
		q[cur].EnQueue(e);
	}
}

template<class ElemType>
void QStack<ElemType>::Push_Merge_Neo(int stacklength)				// stacklength��ԭ��ջ������Ԫ�ص�����	��ջ_�鲢���� ʱ�临�Ӷ�O(nlogn)
{	//����Ҫȥstacklength������
	ElemType e;			//���ڽ���һ�ε�������
	int length = q[cur].GetLength() - stacklength;	//��Ҫ�鲢���õ�Ԫ������
	int count = length;
	int templength;			//templengthΪʵ����Ҫ���������
	int sort_num = 1;
	ElemType blank;			//���λ��Ԫ�� ���������2^n���������ݵ����
	Top(blank);				//blank������г�ʼ��

	if (length <= 1)return;
	for (; sort_num * 2 <= length; sort_num *= 2);
	count = sort_num / 2;

	for (int i = 2; i / 2 < length && count > 0; i *= 2)
	{
		templength = i - length % i;


		//q[cur].Traverse(Write<double>);	cout << endl;

		for (int j = 0; j < stacklength; j++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			//cout << "ԭ��Ԫ���Ŷ�β" << endl;
			q[cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
		//cout << i << endl;
		//cout << count << endl;
		for (int j = 0; j < count; j++)
		{
			for (int k = 0; k < i; k++)		//������������Ԫ����2^k��һ�飬Ų����һ���ձ�
			{
				q[cur].DelQueue(e);
				q[1 - cur].EnQueue(e);  //cout << "������: ";   //q[cur].Traverse(Write<double>);	cout << endl;
			}
			for (int k = 0; k < i / 2; k++)	//�ڿձ�������
			{
				q[1 - cur].DelQueue(e);
				q[1 - cur].EnQueue(e);
			}
			for (int k = 0; k < i; k++)		//������ص�ԭ���ı�
			{
				q[1 - cur].DelQueue(e);
				q[cur].EnQueue(e);  //cout << "�ض���: ";  //q[cur].Traverse(Write<double>);	cout << endl;
			}
		}

		if (length - sort_num != 0)
		{
			for (int j = 0; j < length - sort_num; j++)
			{
				q[cur].DelQueue(e);
				q[cur].EnQueue(e);
				//cout << "�Ŷ�β: ";
				//q[cur].Traverse(Write<double>);	cout << endl;
			}
		}

		count /= 2;

		//cout << "��ǰ�ִ�: ";
		//q[cur].Traverse(Write<double>);	cout << endl;
		//cout << "LOOP" << endl;
	}
	if (length - sort_num == 1)
	{
		for (int i = 0; i < stacklength; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[cur].DelQueue(e);
			q[1 - cur].EnQueue(e);
		}
		for (int i = 0; i < sort_num; i++)
		{
			q[cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
		for (int i = 0; i < stacklength; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[1 - cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
	}
	else
	{
		for (int i = 0; i < stacklength; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
		for (int i = 0; i < sort_num; i++)
		{
			q[cur].DelQueue(e);
			q[1 - cur].EnQueue(e);
		}
		for (int i = 0; i < length - sort_num; i++)
		{
			q[cur].DelQueue(e);
			q[cur].EnQueue(e);
		}
		for (int i = 0; i < stacklength; i++)		//��"ջ"��ԭ����Ԫ��(����һ��������)�ص����е�β
		{
			q[cur].DelQueue(e);
			q[1 - cur].EnQueue(e);
		}
		for (int i = 0; i < length - sort_num; i++)
		{
			q[cur].DelQueue(e);
			q[1 - cur].EnQueue(e);
		}
		cur = 1 - cur;
	}

	//cout << "finish" << endl;
	Push_Merge_Neo(stacklength + sort_num);
}


template<class ElemType>
void QStack<ElemType>::Push(ElemType stop, int size, istream& in, int choice)
{
	ElemType buffer;		//��������
	ElemType* e = new ElemType[size];
	int length;
	//int edge = 10;		//�������˴���Ҫͨ�����������ҵ����ʵ����֣��ݶ�2048  if else ���ж�����ҲӦ�ø����� ��Ҫ����"ջ"��ԭ���ж���Ԫ��(����Ӻ����е���ʱ����)
	int process = 1;
	int stack_length = GetLength();		//"ջ"��ԭ���ж�������

	for (length = 0; length < size; length++)
	{
		in >> buffer;
		if (buffer == stop)
			break;
		e[length] = buffer;
	}
	if (choice == 1)
	{
		//cout << "���ڵ���Push_Switch:" << endl;
		for (int i = 0; i < length; i++)
		{
			switch (process)
			{
			case 1:
				if (IsFull(3))		//��ǰ�������в���
				{
					Push_Switch(e[i]);
				}
				else
				{
					process = 2;
					cur = 1 - cur;
				}
				break;
			case 2:
				if (IsFull(1) == 0)		//��һ���������� ���õ�������ջ��
				{
					//cout << "push_solo" << endl;
					Push_Solo(e[i]);
				}
				break;
			default:
				break;
			}
		}
	}
	else if (choice == 2)
	{
		//cout << "���ڵ���Push_Merge:" << endl;
		for (int i = 0; i < length; i++)
		{
			switch (process)
			{
			case 1:
				if (IsFull(3) && (i + stack_length + 1) <= (DEFAULT_SIZE / 2))		//��ǰ�������в���
					q[cur].EnQueue(e[i]);	//������ȫ���ȥ
				else
				{
					process = 2;
					Push_Merge(stack_length);	//�����͹鲢����
					cur = 1 - cur;
					i--;
				}
				if (i == length - 1)
				{
					Push_Merge(stack_length);	//û��Ҫpush��Ԫ�ؾ͹鲢����
				}
				break;
			case 2:
				if (IsFull(1) == 0)		//��һ���������� ���õ�������ջ��
				{
					//cout << "push_solo" << endl;
					Push_Solo(e[i]);
				}
				break;
			default:
				break;
			}


		}
	}
	else if (choice == 3)
	{
		//cout << "���ڵ���Push_Merge_Neo:" << endl;
		for (int i = 0; i < length; i++)
		{
			switch (process)
			{
			case 1:
				if (IsFull(3))		//��ǰ�������в���
					q[cur].EnQueue(e[i]);	//������ȫ���ȥ
				else
				{
					process = 2;
					Push_Merge_Neo(stack_length);	//�����͹鲢����
					cur = 1 - cur;
				}
				if (i == length - 1)
				{
					Push_Merge_Neo(stack_length);	//û��Ҫpush��Ԫ�ؾ͹鲢����
				}
				break;
			case 2:
				if (IsFull(1) == 0)		//��һ���������� ���õ�������ջ��
				{
					//cout << "push_solo" << endl;
					Push_Solo(e[i]);
				}
				break;
			default:
				break;
			}


		}
	}
	delete[]e;
}

template<class ElemType>
Status QStack<ElemType>::Top(ElemType& e) const
{
	if (IsEmpty(1))	 // ջ��
		return UNDER_FLOW;
	else { // ջ�ǿ�,�����ɹ�
		q[cur].GetHead(e);	// ��e����ջ��Ԫ��
		return SUCCESS;
	}
}

template<class ElemType>
Status QStack<ElemType>::Pop()		//������"ջ"��Ԫ��
{
	if (IsEmpty(1))
		return UNDER_FLOW;
	else
	{
		q[cur].DelQueue();
		return SUCCESS;
	}
}

template<class ElemType>
Status QStack<ElemType>::Pop(ElemType& e)		//����"ջ"��Ԫ��
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

double gettime(int restart)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	const double c = 1.0 / CLOCKS_PER_SEC;
	static double t = double(clock());				// ��̬�ֲ���������һ�ε���ʱ��ȷ����ʱ���
	if (restart) t = double(clock());				// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c * (double(clock()) - t);					// ����һ��ʱ�㵽������������ʱ��
}