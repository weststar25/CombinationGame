#pragma once
#include<time.h>
#include<iostream>
using namespace std;
#include<stdlib.h>

// 모양
#define CIR 0	// 원
#define TRI 1	// 세모
#define REC 2	// 네모
#define RAND "random"
#define EZ "easy"
#define HD "hard"

class Card{
private:
	int cNum;		// 카드번호
	int cShape;		// 모양
	int cColor;		// 도형색
	int cBgColor;	// 배경색
	static int cCnt;	// 카드생성수
	int cSelect; // 선택 여부
public:
	Card();
	Card(char*);	// 신규카드생성(랜덤)
	~Card();
	void setNum(int n){ this->cNum=n; }
	void setShape(int s){ this->cShape=s; }
	void setColor(int c){ this->cColor=c; }
	void setBgColor(int b){ this->cBgColor=b; }
	void setSelect(int t){ this->cSelect=t; }
	int getNum() const { return this->cNum; }
	int getShape() const { return this->cShape; }
	int getColor() const { return this->cColor; }
	int getBgColor() const { return this->cBgColor; }
	int getSelect(){ return this->cSelect; }
	void show();
	bool hap(char *, Card &c1, Card &c2);
	friend bool operator==(Card &, Card &);
};