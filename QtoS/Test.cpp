#include <iostream>
#include "QStack.h"
#include "stop_watch.h"

double gettime(int restart = 0)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0 / CLOCKS_PER_SEC;
	static double t = double(clock());				// 静态局部变量。第一次调用时，确定计时起点
	if (restart) t = double(clock());				// 根据实参决定是否重新确定计时起点
	return c * (double(clock()) - t);					// 从上一计时点到现在所经历的时间
}

void test();
void test2(int num=0);
void OpenMenu();

int main()
{
	OpenMenu();
	return 0;
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

void OpenMenu()
{
	char c1 = '#';
	char c2 = '#';
	QStack<int> sa;
	int x;
	int num;
	while (c1 != '0')	
	{
		cout << endl << "队列模拟栈";
		cout << endl << "1. 生成栈.\t" << "a. Push_Switch\t" << "b. Push_Merge\t" << "c. Push_Solo";
		cout << endl << "2. 显示栈.";
		cout << endl << "3. 入栈.";
		cout << endl << "4. 出栈.";
		cout << endl << "5. 取栈顶.";
		cout << endl << "6. 运算速度测试.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能(0~6):";
		cin >> c1;
		switch (c1) 		{
			case '1':
				cin >>c2;
				switch (c2)
				{
					case 'a':
						sa.Clear();
						cout << "输入e(e =0时退出)" << endl;
						cin >> x;
						while (x != 0){
							sa.Push_Switch(x);
							cin >> x;
						}
						break;
					case 'b':
						sa.Clear();
						cout << "输入e(e =0时退出)" << endl;
						cin >> x;
						while (x != 0){
							sa.Push_Queue(x);
							cin >> x;
						}
						sa.Push_Merge_Neo();
						break;
					case 'c':
						sa.Clear();
						cout << "输入e(e =0时退出)" << endl;
						cin >> x;
						while (x != 0){
							sa.Push_Solo(x);
							cin >> x;
						}
						break;
					default:
						break;
				}
				
		   case '2':
				cout << endl;
				sa.Traverse(Write<int>);
				break;
		   case '3':
				cout << endl << "输入元素值:";
				cin >> x;
				sa.Push_Switch(x);
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
		   case '6':
			   cout << endl << "输入测试值:";
			   cin >> num;
			   test2(num);
			   break;
		}
	}

	system("PAUSE");  
}



void test()
{
	stop_watch watch;							//计时器
	QStack<int> s1,s2,s3;
	int edge=1000,route=1;
	double t1=0,t2=0,t3=0;
	while(edge>5 )
	{
		watch.start();
		for(int i=1;i<=edge;i++)
			s1.Push_Switch(i);					//入栈_左手倒右手
		watch.stop();
		t1 += watch.elapsed_ms();
		//cout << t1 <<"ms"<< endl;				//毫秒
		
		watch.restart();
		for(int i=1;i<=edge;i++)
			s2.Push_Queue(i);					//入队列
		s2.Push_Merge_Neo();						//入栈_归并倒置
		watch.stop();
		t2 += watch.elapsed_ms();
		//cout << t2 <<"ms"<< endl;
		
		watch.restart();
		for(int i=1;i<=edge;i++)
			s3.Push_Solo(i);					//入栈_单队列操作
		watch.stop();
		t3 += watch.elapsed_ms();
		//cout << t3 <<"ms"<< endl;
		
		if(route == 0)							//每五轮判断一次
		{
			if(t1<t2)	break;					//每五轮时间总和 判断大小
			t1=0;t2=0;t3=0;
		}
		
		s1.Clear();
		s2.Clear();
		s3.Clear();
		edge--;
		route = (route+1)%5;
	}
	cout << t1/5 <<"ms"<< endl;
	cout << t2/5 <<"ms"<< endl;
	cout << t3/5 <<"ms"<< endl;
	cout << "edge = "<< edge << endl;
	system("Pause");
}

void test2(int num)
{
	stop_watch watch;							//计时器
	QStack<int> s1,s2,s3;
	watch.start();
	for(int i=1;i<=num;i++)
		s1.Push_Switch(i);					//入栈_左手倒右手
	watch.stop();
	cout << endl <<"Push_Switch:\t";
	cout << watch.elapsed_ms() << "ms" << endl;
	
	watch.restart();
	for(int i=1;i<=num;i++)
		s2.Push_Queue(i);					//入队列
	s2.Push_Merge_Neo();						//入栈_归并倒置
	watch.stop();
	cout << endl <<"Push_Merge:\t";
	cout << watch.elapsed_ms() << "ms" << endl;
	//cout << t2 <<"ms"<< endl;
	
	watch.restart();
	for(int i=1;i<=num;i++)
		s3.Push_Solo(i);					//入栈_单队列操作
	watch.stop();
	cout << endl <<"Push_Solo:\t";
	cout << watch.elapsed_ms() << "ms" << endl;
}
