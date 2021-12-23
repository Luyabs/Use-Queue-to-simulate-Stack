#include <iostream>
#include "QStack.h"

double gettime(int restart = 0)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0 / CLOCKS_PER_SEC;
	static double t = double(clock());				// 静态局部变量。第一次调用时，确定计时起点
	if (restart) t = double(clock());				// 根据实参决定是否重新确定计时起点
	return c * (double(clock()) - t);					// 从上一计时点到现在所经历的时间
}

int main()
{
	double e = 0;
	QStack<double> s;
	/*
	s.Push_Switch(1);
	s.Push_Switch(2);
	s.Push_Switch(3);
	s.Push_Switch(4);
	s.Push_Switch(5);
	s.Push_Switch(6);
	s.Push_Switch(7);
	s.Push_Switch(8);
	s.Traverse(Write<double>);
	cout << endl;
	*/
	//s.Push_Switch(666);	
	//s.Push_Switch(999);

	s.Push(0,11);
	s.Traverse(Write<double>);
	cout << endl;


	//cout << s.IsEmpty(1) << endl;
	//cout << s.IsEmpty(2) << endl;
	//cout << s.IsEmpty(3) << endl;
	cout << "IsEmpty3?  " << s.IsEmpty(3) << endl;
	//s.Push(0.5);
	s.Clear();
	//s.Push(1.2);
	//s.Push(3.4);

	QStack<double> s_copy(s);
	QStack<double> s_equal;
	s_equal = s_copy;
	cout << "Copy_construction_Traverse:  ";
	s_copy.Traverse((Write<double>));
	cout << endl << "Assignment_Traverse:  ";
	s_equal.Traverse((Write<double>));
	cout << endl;

	cout << "GetLength:  " << s.GetLength() << endl;
	s.Top(e);	cout << "Top:  " << e << endl << "Traverse:  ";
	s.Traverse((Write<double>));	cout << endl;
	cout << "IsEmpty3?  " << s.IsEmpty(3) << endl;
	s.Pop(e);	cout << "Pop:  " << e << endl;
	s.Pop(e);	cout << "Pop:  " << e << endl << "Traverse:  ";
	s.Traverse((Write<double>));	cout << endl;
	cout << "IsEmpty3?  " << s.IsEmpty(3) << endl;
}
/*
char c = '#';
QStack<int> sa;
int x;
while (c != '0')	{
	cout << endl << "1. 生成栈.";
	cout << endl << "2. 显示栈.";
	cout << endl << "3. 入栈.";
	cout << endl << "4. 出栈.";
	cout << endl << "5. 取栈顶.";
	cout << endl << "0. 退出";
	cout << endl << "选择功能(0~5):";
	cin >> c;
	switch (c) 		{
		case '1':
			sa.Clear();
			cout << "输入e(e =0时退出)" << endl;
			cin >> x;
			while (x != 0){
				sa.Push(x);
				cin >> x;
			}
			break;
	   case '2':
			cout << endl;
			sa.Traverse(Write<int>);
			break;
	   case '3':
			cout << endl << "输入元素值:";
			cin >> x;
			sa.Push(x);
			break;
	   case '4':
			if (sa.Pop(x) == SUCCESS)
				   cout << endl << "栈顶元素值为：" << x << "." << endl;
			else
				   cout << endl << "栈为空." << endl;
			break;
	   case '5':
			if (sa.Top(x) == SUCCESS)
				   cout << endl << "栈顶元素值为：" << x << "." << endl;
			else
				   cout << endl << "栈为空." << endl;
			break;
	}
}

system("PAUSE");
return 0;  
}
*/

