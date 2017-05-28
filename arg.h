#pragma once
#include "opencv2/opencv.hpp"
using namespace cv;
#include <vector>
#include "card.h"
#include <windows.h>

struct iArg{
	int oArgc;		// argc
	char **oArgv;	// argv
	Point center;
	bool select;
	vector<Card> cList; // Card Class���� cList�� ���Ͱ�ü ����
	int hapEDa;		//���� ��� 1
	int hapCnt;		// ���� ����
	int time;
	int gyeolEDa;	//���� ��� 1
	vector<int> hapList; // int���� ���� ��� ����Ʈ ����
};
 
extern iArg *eArgp;