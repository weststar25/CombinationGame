#pragma once
#include"card.h"

int Card::cCnt;

Card::Card()
{
	this->cCnt++;
}
Card::Card(char *mode)				// 신규카드생성(랜덤)
{
	this->cShape = rand()%3;
	this->cColor = rand()%3;
	this->cBgColor = rand()%3;
	this->cNum = this->cCnt++;
	this->cSelect = 0;
}
Card::~Card()
{
	//this->cCnt--;
}
void Card::show()
{
	cout << "No."<< this->cNum << " - "
		<< this->cShape << " / "
		<< this->cColor << " / "
		<< this->cBgColor << endl;
}
bool Card::hap(char *mode, Card &pCard1, Card &pCard2)
{
	int equ=0, dif=0;

	if( // 모양 판정
		this->cShape == pCard1.cShape &&
		pCard1.cShape == pCard2.cShape
		){ equ++; }
	else if(
		this->cShape != pCard1.cShape &&
		this->cShape != pCard2.cShape &&
		pCard1.cShape != pCard2.cShape
		){ dif++; }
	else { return false; }

	if( // 도형색 판정
		this->cColor == pCard1.cColor &&
		pCard1.cColor == pCard2.cColor
		){ equ++; }
	else if(
		this->cColor != pCard1.cColor &&
		this->cColor != pCard2.cColor &&
		pCard1.cColor != pCard2.cColor
		){ dif++; }
	else { return false; }

	if( // 배경색 판정
		this->cBgColor == pCard1.cBgColor &&
		pCard1.cBgColor == pCard2.cBgColor
		){ equ++; }
	else if(
		this->cBgColor != pCard1.cBgColor &&
		this->cBgColor != pCard2.cBgColor &&
		pCard1.cBgColor != pCard2.cBgColor
		){ dif++; }
	else { return false; }

	if(!strcmp(mode, EZ)){ equ=0; }	// 이지모드?

	if(equ+dif==3){ return true; }
	else{ return false; }
}
bool operator==(Card &c1, Card &c2)
{
	if(c1.cShape != c2.cShape){ return false; }
	if(c1.cColor != c2.cColor){ return false; }
	if(c1.cBgColor != c2.cBgColor){ return false; }
	return true;
}