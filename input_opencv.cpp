#pragma once
#include"input_opencv.h"

Mat Input_OpenCv::getHandMask(int minCr, int maxCr, int minCb, int maxCb)
{	// 여기서 Cr Cv가 색데이터로 얘를 바꿔서 무슨색 검출할지 결정하는듯

	//컬러 공간 변환 BGR->YCrCb
	Mat YCrCb;
	cvtColor(edges, YCrCb, CV_BGR2YCrCb);

	//각 채널별로 분리
	vector<Mat> planes;
	split(YCrCb, planes);

	//각 채널별로 화소마다 비교
	Mat mask(edges.size(), CV_8U, Scalar(0));   //결과 마스크를 저장할 영상
	int nr=edges.rows;    //전체 행의 수
	int nc=edges.cols;
	
	for(int i=0; i<nr; i++){
		uchar* CrPlane=planes[1].ptr<uchar>(i);   //Cr채널의 i번째 행 주소
		uchar* CbPlane=planes[2].ptr<uchar>(i);   //Cb채널의 i번째 행 주소
		for(int j=0; j<nc; j++){
			if( (minCr < CrPlane[j]) && (CrPlane[j] <maxCr) && (minCb < CbPlane[j]) && (CbPlane[j] < maxCb) )
				mask.at<uchar>(i, j)=255;
		}
	}

	return mask;
}
int Input_OpenCv::getFingerCount(double scale){
	//손가락 개수를 세기 위한 원 그리기
	Mat cImg(mask.size(), CV_8U, Scalar(0));
	circle(cImg, center, radius*scale, Scalar(255));

	//원의 외곽선을 저장할 벡터
	vector<vector<Point>> contours;
	findContours(cImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if(contours.size()==0)   //외곽선이 없을 때 == 손 검출 X
		return -1;

	//외곽선을 따라 돌며 mask의 값이 0에서 1로 바뀌는 지점 확인
	int fingerCount=0;
	for(int i=1; i<contours[0].size(); i++){
		Point p1=contours[0][i-1];
		Point p2=contours[0][i];
		if(mask.at<uchar>(p1.y, p1.x)==0 && mask.at<uchar>(p2.y, p2.x)>1)
			fingerCount++;
	}

	//손목과 만나는 개수 1개 제외
	return fingerCount-1;
}
Point Input_OpenCv::getHandCenter(){
	//거리 변환 행렬을 저장할 변수
	Mat dst;
	distanceTransform(mask, dst, CV_DIST_L2, 5);  //결과는 CV_32SC1 타입

	//거리 변환 행렬에서 값(거리)이 가장 큰 픽셀의 좌표와, 값을 얻어온다.
	int maxIdx[2];    //좌표 값을 얻어올 배열(행, 열 순으로 저장됨)
	minMaxIdx(dst, NULL, &radius, NULL, maxIdx, mask);   //최소값은 사용 X

	return Point(maxIdx[1], maxIdx[0]);
}
int Input_OpenCv::input()
{
	if(!cap.isOpened()){ return -1; }  // check if we succeeded
   	
	cap >> frame; // get a new frame from camera
	flip(frame, edges, 1);								// 대칭(code: 양수(좌우), 음수(상하))
	flip(frame, mask, 1);
    
	mask=getHandMask();   //스킨 컬러로 피부색 검출
	handImage=Mat(edges.size(), CV_8UC3, Scalar(0));
	add(edges, Scalar(0), handImage, mask);    //mask에서 0이 아닌 픽셀만 handImage로 더해짐.

	erode(mask, mask, Mat(2, 2, CV_8U, Scalar(1)), Point(-1, -1), 2);	// 침식
	erode(mask, mask, Mat(1, 1, CV_8U, Scalar(1)), Point(-1, -1), 2);	// 침식
	erode(mask, mask, Mat(2, 2, CV_8U, Scalar(1)), Point(-1, -1), 2);	// 침식
	
	/*cvtColor(handImage, mask2, CV_BGR2GRAY );
	equalizeHist( mask2, mask2 );
	erode(mask2, mask2, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);*/

	center=getHandCenter();  		//손바닥 중심점, 영역 그리기
	if(getFingerCount()==0){
		circle(edges, center, 2, Scalar(255, 0, 255), -1);
		circle(edges, center, (int)(radius+0.5), Scalar(255, 0, 255), 2);
	}
	else{
		circle(edges, center, 2, Scalar(0, 255, 0), -1);
		circle(edges, center, (int)(radius+0.5), Scalar(0, 255, 0), 2);
	}
		
	//cout<< "손바닥 중심점 좌표: " << center << endl
	//	<< "반지름: " << radius << endl
	//	<< "손가락 개수: " << getFingerCount() << endl;

    return 0;
}