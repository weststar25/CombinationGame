#pragma once
#include<time.h>
#include<iostream>
using namespace std;
#include<stdlib.h>

// ���
#define CIR 0	// ��
#define TRI 1	// ����
#define REC 2	// �׸�
#define RAND "random"
#define EZ "easy"
#define HD "hard"

class Card{
private:
	int cNum;		// ī���ȣ
	int cShape;		// ���
	int cColor;		// ������
	int cBgColor;	// ����
	static int cCnt;	// ī�������
	int cSelect; // ���� ����
public:
	Card();
	Card(char*);	// �ű�ī�����(����)
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