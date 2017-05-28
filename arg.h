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
	vector<Card> cList; // Card Class형의 cList란 벡터객체 선언
	int hapEDa;		//합일 경우 1
	int hapCnt;		// 합의 개수
	int time;
	int gyeolEDa;	//결일 경우 1
	vector<int> hapList; // int형의 합의 경우 리스트 벡터
};
 
extern iArg *eArgp;