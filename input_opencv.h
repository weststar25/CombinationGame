#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

#define CORREC 1.015	//1.045

class Input_OpenCv{
private:
	VideoCapture cap;
	Mat edges;
	Mat mask;
	Mat mask2;
	Mat frame;
	Mat handImage;
	double radius;
	Point center;
public:
	Mat getEdges(){ return this->edges; }
	Mat getMask(){ return this->mask; }
	Mat getMask2(){ return this->mask2; }
	Point getPoint(){ return this->center; }
	bool getSelect(){ return this->getFingerCount(); }
	void initVideoCapture(){ this->cap=0; }
	Mat getHandMask(int minCr=165*CORREC, int maxCr=255, int minCb=0*CORREC, int maxCb=230); // 熱薑說除儀
	//Mat getHandMask(int minCr=142*CORREC, int maxCr=240, int minCb=0*CORREC, int maxCb=230); // 說除儀
	//Mat getHandMask(int minCr=0*CORREC, int maxCr=150, int minCb=140*CORREC, int maxCb=255); // だ塢儀
	Point getHandCenter();
	int getFingerCount(double scale=2.0);
	int input();
};