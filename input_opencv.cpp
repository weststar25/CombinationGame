#pragma once
#include"input_opencv.h"

Mat Input_OpenCv::getHandMask(int minCr, int maxCr, int minCb, int maxCb)
{	// ���⼭ Cr Cv�� �������ͷ� �긦 �ٲ㼭 ������ �������� �����ϴµ�

	//�÷� ���� ��ȯ BGR->YCrCb
	Mat YCrCb;
	cvtColor(edges, YCrCb, CV_BGR2YCrCb);

	//�� ä�κ��� �и�
	vector<Mat> planes;
	split(YCrCb, planes);

	//�� ä�κ��� ȭ�Ҹ��� ��
	Mat mask(edges.size(), CV_8U, Scalar(0));   //��� ����ũ�� ������ ����
	int nr=edges.rows;    //��ü ���� ��
	int nc=edges.cols;
	
	for(int i=0; i<nr; i++){
		uchar* CrPlane=planes[1].ptr<uchar>(i);   //Crä���� i��° �� �ּ�
		uchar* CbPlane=planes[2].ptr<uchar>(i);   //Cbä���� i��° �� �ּ�
		for(int j=0; j<nc; j++){
			if( (minCr < CrPlane[j]) && (CrPlane[j] <maxCr) && (minCb < CbPlane[j]) && (CbPlane[j] < maxCb) )
				mask.at<uchar>(i, j)=255;
		}
	}

	return mask;
}
int Input_OpenCv::getFingerCount(double scale){
	//�հ��� ������ ���� ���� �� �׸���
	Mat cImg(mask.size(), CV_8U, Scalar(0));
	circle(cImg, center, radius*scale, Scalar(255));

	//���� �ܰ����� ������ ����
	vector<vector<Point>> contours;
	findContours(cImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if(contours.size()==0)   //�ܰ����� ���� �� == �� ���� X
		return -1;

	//�ܰ����� ���� ���� mask�� ���� 0���� 1�� �ٲ�� ���� Ȯ��
	int fingerCount=0;
	for(int i=1; i<contours[0].size(); i++){
		Point p1=contours[0][i-1];
		Point p2=contours[0][i];
		if(mask.at<uchar>(p1.y, p1.x)==0 && mask.at<uchar>(p2.y, p2.x)>1)
			fingerCount++;
	}

	//�ո�� ������ ���� 1�� ����
	return fingerCount-1;
}
Point Input_OpenCv::getHandCenter(){
	//�Ÿ� ��ȯ ����� ������ ����
	Mat dst;
	distanceTransform(mask, dst, CV_DIST_L2, 5);  //����� CV_32SC1 Ÿ��

	//�Ÿ� ��ȯ ��Ŀ��� ��(�Ÿ�)�� ���� ū �ȼ��� ��ǥ��, ���� ���´�.
	int maxIdx[2];    //��ǥ ���� ���� �迭(��, �� ������ �����)
	minMaxIdx(dst, NULL, &radius, NULL, maxIdx, mask);   //�ּҰ��� ��� X

	return Point(maxIdx[1], maxIdx[0]);
}
int Input_OpenCv::input()
{
	if(!cap.isOpened()){ return -1; }  // check if we succeeded
   	
	cap >> frame; // get a new frame from camera
	flip(frame, edges, 1);								// ��Ī(code: ���(�¿�), ����(����))
	flip(frame, mask, 1);
    
	mask=getHandMask();   //��Ų �÷��� �Ǻλ� ����
	handImage=Mat(edges.size(), CV_8UC3, Scalar(0));
	add(edges, Scalar(0), handImage, mask);    //mask���� 0�� �ƴ� �ȼ��� handImage�� ������.

	erode(mask, mask, Mat(2, 2, CV_8U, Scalar(1)), Point(-1, -1), 2);	// ħ��
	erode(mask, mask, Mat(1, 1, CV_8U, Scalar(1)), Point(-1, -1), 2);	// ħ��
	erode(mask, mask, Mat(2, 2, CV_8U, Scalar(1)), Point(-1, -1), 2);	// ħ��
	
	/*cvtColor(handImage, mask2, CV_BGR2GRAY );
	equalizeHist( mask2, mask2 );
	erode(mask2, mask2, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);*/

	center=getHandCenter();  		//�չٴ� �߽���, ���� �׸���
	if(getFingerCount()==0){
		circle(edges, center, 2, Scalar(255, 0, 255), -1);
		circle(edges, center, (int)(radius+0.5), Scalar(255, 0, 255), 2);
	}
	else{
		circle(edges, center, 2, Scalar(0, 255, 0), -1);
		circle(edges, center, (int)(radius+0.5), Scalar(0, 255, 0), 2);
	}
		
	//cout<< "�չٴ� �߽��� ��ǥ: " << center << endl
	//	<< "������: " << radius << endl
	//	<< "�հ��� ����: " << getFingerCount() << endl;

    return 0;
}