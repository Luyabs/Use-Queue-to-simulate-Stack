#pragma once
#include <fstream>
#include "QStack.h"

const char* datafile1 = "data1.txt";
const char* datafile2 = "data2.txt";
const char* datafile3 = "data3.txt";
const char* datafile4 = "data4.txt";
const char* stackfile = "stack.txt";
const int NUM = 1;		//1个一组算一次平均时间
const int SCALE = 14;	//8~65536 十四批次数据
const int PIECES = 100;	

void Process(const char* infilename, const char* outfilename, int choice, int pieces, int begin, int end, int originalelems)		// 从指定文件中读取数据，构造链表  参数:输入文件名/输出文件名/push选项/数据切成pieces+2片/数据起始大小/终止大小/mode=1倍率增加模式mode=2阶梯状增加模式
{
	double time = 0;		//8~65536数据组 每个数据规模有一次计时

	ifstream infile(infilename);
	if (infile.fail())
		return;

	ofstream outfile;
	outfile.open(outfilename, ios::app);
	if (outfile.fail())
		return;

	double step = (end - begin) / pieces;

	for (double scale = begin; scale <= end; scale += step)
	{
		QStack<double>* qstack = new QStack<double>[NUM];
		for (int i = 0; i < NUM; i++)		//把originalelems先打入栈
		{
			qstack[i].Clear();
			qstack[i].Push(0, int(originalelems), infile, choice);
		}
		time = gettime(1);
		for (int i = 0; i < NUM; i++)		//运行NUM次相同scale(规模)的数据求平均运算时间
		{
			qstack[i].Push(0, int(scale), infile, choice);
		}
		time = gettime() / NUM;
		if (scale + step <= end)
			outfile << time << ' ';
		else
			outfile << time << endl;
		delete[]qstack;
	}
}

void Process2(const char* infilename, const char* outfilename, int choice, double rate, int begin, int end, int originalelems)		// 从指定文件中读取数据，构造链表  参数:输入文件名/输出文件名/push选项/数据增长倍率/数据起始大小/终止大小/mode=1倍率增加模式mode=2阶梯状增加模式
{
	double time = 0;		//8~65536数据组 每个数据规模有一次计时

	ifstream infile(infilename);
	if (infile.fail())
		return;

	ofstream outfile;
	outfile.open(outfilename, ios::app);
	if (outfile.fail())
		return;

	QStack<double>* qstack = new QStack<double>[NUM];

	for (double scale = begin; scale <= end; scale *= rate)
	{
		for (int i = 0; i < NUM; i++)		//把originalelems先打入栈
		{
			qstack[i].Clear();
			qstack[i].Push(0, int(originalelems), infile, choice);
		}
		time = gettime(1);
		for (int i = 0; i < NUM; i++)		//运行NUM次相同scale(规模)的数据求平均运算时间
		{
			qstack[i].Push(0, int(scale), infile, choice);
		}
		time = gettime() / NUM;
		if (scale * rate <= end)
			outfile << time << ' ';
		else
			outfile << time << endl;
	}
	delete[]qstack;
}

void Build_Data(int choice)
{	
	switch (choice)
	{
	case 1:
		// 三push比较	目的:证明两个merge时间复杂度O(nlogn) switch时间复杂度O(n^2) 
		Process(stackfile, datafile1, 1, PIECES, 8, 4096, 0);
		Process(stackfile, datafile1, 2, PIECES, 8, 4096, 0);
		Process(stackfile, datafile1, 3, PIECES, 8, 4096, 0);
		break;
	case 2:
		//  merge的细致比较	目的:比较merge和merge_neo的性能
		Process(stackfile, datafile2, 2, PIECES, 128, 65536, 0);
		Process(stackfile, datafile2, 3, PIECES, 128, 65536, 0);
		break;
	case 3:
		//  栈中原先已有数据时的测试
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 8);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 256);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 512);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 1024);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 2048);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 4096);
		break;
	case 4:
		// 2^n数据测试	目的:按照log数级别测量数据 
		Process2(stackfile, datafile4, 2, 2, 8, 262144*4, 0);
		Process2(stackfile, datafile4, 3, 2, 8, 262144*4, 0);
		break;

	default:
		break;
	}

}


/*
void Save(double t)
{
	ofstream outfile;
	outfile.open(datafile, ios::app);
	if (outfile.fail())
		return;
	outfile << t << ' ';
	outfile.close();
}*/

