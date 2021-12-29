#pragma once
#include <fstream>
#include "QStack.h"

const char* datafile1 = "data1.txt";
const char* datafile2 = "data2.txt";
const char* datafile3 = "data3.txt";
const char* datafile4 = "data4.txt";
const char* stackfile = "stack.txt";
const int NUM = 1;		//1��һ����һ��ƽ��ʱ��
const int SCALE = 14;	//8~65536 ʮ����������
const int PIECES = 100;	

void Process(const char* infilename, const char* outfilename, int choice, int pieces, int begin, int end, int originalelems)		// ��ָ���ļ��ж�ȡ���ݣ���������  ����:�����ļ���/����ļ���/pushѡ��/�����г�pieces+2Ƭ/������ʼ��С/��ֹ��С/mode=1��������ģʽmode=2����״����ģʽ
{
	double time = 0;		//8~65536������ ÿ�����ݹ�ģ��һ�μ�ʱ

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
		for (int i = 0; i < NUM; i++)		//��originalelems�ȴ���ջ
		{
			qstack[i].Clear();
			qstack[i].Push(0, int(originalelems), infile, choice);
		}
		time = gettime(1);
		for (int i = 0; i < NUM; i++)		//����NUM����ͬscale(��ģ)��������ƽ������ʱ��
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

void Process2(const char* infilename, const char* outfilename, int choice, double rate, int begin, int end, int originalelems)		// ��ָ���ļ��ж�ȡ���ݣ���������  ����:�����ļ���/����ļ���/pushѡ��/������������/������ʼ��С/��ֹ��С/mode=1��������ģʽmode=2����״����ģʽ
{
	double time = 0;		//8~65536������ ÿ�����ݹ�ģ��һ�μ�ʱ

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
		for (int i = 0; i < NUM; i++)		//��originalelems�ȴ���ջ
		{
			qstack[i].Clear();
			qstack[i].Push(0, int(originalelems), infile, choice);
		}
		time = gettime(1);
		for (int i = 0; i < NUM; i++)		//����NUM����ͬscale(��ģ)��������ƽ������ʱ��
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
		// ��push�Ƚ�	Ŀ��:֤������mergeʱ�临�Ӷ�O(nlogn) switchʱ�临�Ӷ�O(n^2) 
		Process(stackfile, datafile1, 1, PIECES, 8, 4096, 0);
		Process(stackfile, datafile1, 2, PIECES, 8, 4096, 0);
		Process(stackfile, datafile1, 3, PIECES, 8, 4096, 0);
		break;
	case 2:
		//  merge��ϸ�±Ƚ�	Ŀ��:�Ƚ�merge��merge_neo������
		Process(stackfile, datafile2, 2, PIECES, 128, 65536, 0);
		Process(stackfile, datafile2, 3, PIECES, 128, 65536, 0);
		break;
	case 3:
		//  ջ��ԭ����������ʱ�Ĳ���
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 8);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 256);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 512);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 1024);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 2048);
		Process(stackfile, datafile3, 2, PIECES, 1024, 32768, 4096);
		break;
	case 4:
		// 2^n���ݲ���	Ŀ��:����log������������� 
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

