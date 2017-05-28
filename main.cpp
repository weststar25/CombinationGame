#pragma once
#include<vector>
#include<process.h>
#include<Windows.h>
#include<time.h>         //_strtime()�� ���ؼ� ��Ŭ��� �� 
#include<windows.h>         // strtok(), atoi()�� ���ؼ� ��Ŭ��� ��
#include"card.h"
#include"input_opencv.h"
#include"output_opengl.h"
#include"arg.h"
#include<conio.h>

#define HAPLIST1(x) ((x)/100)            // 1��ī��
#define HAPLIST2(x) ((x)%100/10)         // 2��ī��
#define HAPLIST3(x) ((x)%10)            // 3��ī��
#define HAPINT(x,y,z) ((x)*100+(y)*10+(z))   // ��


struct time{
	unsigned int ti_hour;
	unsigned int ti_min;
	unsigned int ti_sec;
};

unsigned WINAPI inThread(void *pvoid);
unsigned WINAPI outThread(void *pvoid);
void createCList(char *mode, vector<Card> &, int);
void choiceRange(iArg &iarg);
//bool eqInt_3(int n1[3], int n2[3]);
bool judge(iArg &iarg);
void gettime(struct time *);
//////////////////////////////////////////////
void border();
void printScore(int a);
void printHap(int a);
void printState(int a);
int startOutput();
bool checkGuel;         //�� �������� �� �� ������ ���̿��� Ȯ��
void textcolor(int foreground, int background);
void removeCursor();
void displayCursor();
void gotoxy(int x, int y);
void moveWindow();
void printState(int a);

#define UP_ARROW 72 
#define DOWN_ARROW 80
#define ENTER 13 
#define ESC 27
#define BLACK 0
#define DARKGRAY 8
#define LIGHTRED 12
#define WHITE 15
//////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int count = 0, i, time_change;
	iArg iarg = { argc, argv };
	eArgp = &iarg;               // extern ����
	int end = 0;
	struct time sttime;
	////////////////////////////////////////////////
	int start = -1;      //�ʱ�ȭ

	while (1)
	{
		start = startOutput();
		if (start == 1){                     //�����ϱ�
			border();
			printScore(0);
			printState(7);
			break;
		}
		else if (start == 2){ goto done; }         //����
	}
	////////////////////////////////////////////////
	HWND hWnd;
	HDC hdc; // �ڵ� : ����� �����ϴ� 4����Ʈ ����(HWND, HDC ��) 

	HANDLE hInThread = (HANDLE)_beginthreadex(NULL, 0, inThread, eArgp, 0, NULL);
	HANDLE hOutThread = (HANDLE)_beginthreadex(NULL, 0, outThread, eArgp, 0, NULL);
	srand(time(0)); // ��ġ�� �ʴ� ���� �߻�

	createCList(HD, iarg. cList, rand()%6+1);   // 0~6, 8, 12(����) - ����
	//createCList(HD, iarg.cList, 1); // �׽�Ʈ��
	gettime(&sttime); // ���� �ð� ��������
	int init_second = sttime.ti_min * 60 + sttime.ti_sec; // ���� �����Ҷ��� �ð�
	iarg.time = 0; // �⺻�ð� 0���� �ʱ�ȭ

	while (1){
		waitKey(30);
		moveWindow();      //â ��ġ ���� 

		gettime(&sttime); // ����ð� �ҷ���
		time_change = (sttime.ti_min * 60 + sttime.ti_sec - init_second); //  ����ð� - �����Ҷ� �ð�(��)
		if (time_change == 153)
		{
			printState(6);
		}
		if (time_change > 1)
		{
			eArgp->time = time_change; // ���� �ð����� �ʱ�ȭ 
			if (eArgp->time == 153) // ���� ��û�ϰ� ���� ��������
			{
				goto done;
			}
		}

		choiceRange(iarg);

		for (i = 0; i<iarg.hapCnt; i++)
		{
			if (iarg.hapList[i] == (-iarg.hapCnt))
			{
				end = 1;         //�� �� ã��
				break;
			}

		}
		if (iarg.gyeolEDa == 1 && end == 1){   //�� �����µ� ���� ��� 
			printState(3);
			printScore(5);
			printState(5);
			goto done;
		}
		else if (checkGuel == FALSE && iarg.gyeolEDa == 1 && end != 1)   //�� �����µ� ���� �ƴ� ���
		{
			checkGuel = TRUE;
			printState(4);
			printScore(-3);
			iarg.gyeolEDa = 0;
			for (int i = 0; i<9; i++)
			{
				iarg.cList[i].setSelect(0);
			}
		}
		// ���ư ���� ���� ���Ṯ 
		for (i = 0; i<9; i++)
		{
			if (iarg.cList[i].getSelect() == 1) // ī�带 ������ ���
			{
				count++; // ī��Ʈ ���� ����
				checkGuel = FALSE;   //ī�� �ϳ��� �����ϸ� �� ���� �ʱ�ȭ
			}
		}
		if (count < 3) // �ʿ�ġ�� ���� �ڵ� 
		{
			count = 0;
		}
		if (count == 3)
		{
			if (judge(iarg)){      // ���̸� ����
				eArgp->hapEDa = 1;
				waitKey(2500);
				eArgp->hapEDa = 0;
			}
			else               // �� �ƴϸ� : Ʋ�Ⱦ� Ÿ�� �پ��
			{
				waitKey(2500);
			}
			for (int i = 0; i<9; i++)   // �����ʱ�ȭ
			{
				iarg.cList[i].setSelect(0);
			}
			count = 0;
		}
	}

	waitKey(10000);
done:
	return 0;
}

unsigned WINAPI inThread(void *iargp)   // �Է� �ڵ� ������
{
	Input_OpenCv obj;
	iArg *ip = (iArg *)iargp;

	obj.initVideoCapture();
	namedWindow("edges", 2);
	namedWindow("mask", 2);


	while (1){
		obj.input();
		imshow("edges", obj.getEdges());
		imshow("mask", obj.getMask());
		ip->center = obj.getPoint();
		ip->center.x -= 50, ip->center.y -= 45;
		ip->select = !obj.getFingerCount();
		waitKey(30);
	}
}
unsigned WINAPI outThread(void *argp)   // ��� �ڵ� ������
{

	eArgp = (iArg *)argp;

	waitKey(10);
	output(eArgp);
	return 0;
}
// createCList(HD, iarg. cList, rand()%7);   // 0~6, 8, 12(����)
void createCList(char *mode, vector<Card> &cList, int n)
{
	Card tList[9]; // ī�� Ŭ������ �迭 ��ü ����
	int hapCnt; // �ӽ� �� ī��Ʈ ���� ����

	while (1){            // �ӽ� ī�嵦 ����
		hapCnt = 0;
		for (int i = 0; i<9; i++)
		{
			tList[i] = Card(RAND); // �ӽ� ī�� ���� 
			for (int j = 0; j<i; j++)
			{
				if (tList[i] == tList[j]){ i--; } // �ߺ��� ī�� ���°�� i�� �����ϰ� �ٽ� ����
			}
		}
		eArgp->hapList.clear(); // hapList ���� ���� ���� ��� ���� 
		for (int i = 0; i<7; i++)
			for (int j = i + 1; j<8; j++)
				for (int k = j + 1; k<9; k++)
					if (tList[i].hap(mode, tList[j], tList[k])) // �ӽ� ī�� ����Ʈ�� ���� ���
					{
						eArgp->hapList.push_back(HAPINT(i, j, k)); // �� ����Ʈ�� �߰� 
						hapCnt++; // ��ī���� ���� 
					}
					if (hapCnt == n){ // ���� ������ ���� ī��Ʈ ������ ���� ���
						eArgp->hapCnt = hapCnt; // ��ī��Ʈ ������ ���� ����ü ��ī��Ʈ������ ����
						break;
					}
	}

	cList.clear();               // ī�嵦 ����
	for (int i = 0; i<9; i++){
		cList.push_back(tList[i]); // �ӽ� ����� ī�� ���� cList ���� �ں��� ����
		cList[i].setNum(i);   // ī�� ��ȣ �ʱ�ȭ
		//cList[i].show(); // ī�� ���� ���                     -> ��� �ּ�ó��
	}
	
	//for (int i = 0; i<7; i++){      // ���� ��� ī�嵦 ���
	//for (int j = i + 1; j<8; j++)
	//for (int k = j + 1; k<9; k++)
	//if (tList[i].hap(mode, tList[j], tList[k])){
	//cout << i << "," << j << "," << k << "�� ī�� ";                     // �̰� �ּ�ó���س���
	//cout << "��(" << mode << ")!" << endl;

	//}
	//}
	//
	//for(int i=0 ; i<eArgp->hapCnt ; i++)
	//{
	//cout << eArgp->hapList[i] << endl;
	//}
	//for(int i=0 ; i<eArgp->hapCnt ; i++)
	//{
	//cout << HAPLIST1(eArgp->hapList[i]) << "/"
	//<< HAPLIST2(eArgp->hapList[i]) << "/"
	//<< HAPLIST3(eArgp->hapList[i]) << "/" << endl;
	//}
}
void choiceRange(iArg &iarg) // ī�� �����ϴ� �Լ�
{
	if (iarg.select == TRUE){
		if (iarg.center.x >= 28 && iarg.center.x <= 162 && iarg.center.y >= 21 && iarg.center.y <= 122){
			iarg.cList[0].setSelect(1);
		}
		else if (iarg.center.x >= 199 && iarg.center.x <= 335 && iarg.center.y >= 21 && iarg.center.y <= 122){
			iarg.cList[1].setSelect(1);
		}
		else if (iarg.center.x >= 372 && iarg.center.x <= 508 && iarg.center.y >= 21 && iarg.center.y <= 122){
			iarg.cList[2].setSelect(1);
		}
		else if (iarg.center.x >= 28 && iarg.center.x <= 162 && iarg.center.y >= 149 && iarg.center.y <= 251){
			iarg.cList[3].setSelect(1);
		}
		else if (iarg.center.x >= 199 && iarg.center.x <= 335 && iarg.center.y >= 149 && iarg.center.y <= 251){
			iarg.cList[4].setSelect(1);
		}
		else if (iarg.center.x >= 372 && iarg.center.x <= 508 && iarg.center.y >= 149 && iarg.center.y <= 251){
			iarg.cList[5].setSelect(1);
		}
		else if (iarg.center.x >= 28 && iarg.center.x <= 162 && iarg.center.y >= 279 && iarg.center.y <= 380){
			iarg.cList[6].setSelect(1);
		}
		else if (iarg.center.x >= 199 && iarg.center.x <= 335 && iarg.center.y >= 279 && iarg.center.y <= 380){
			iarg.cList[7].setSelect(1);
		}
		else if (iarg.center.x >= 372 && iarg.center.x <= 508 && iarg.center.y >= 279 && iarg.center.y <= 380){
			iarg.cList[8].setSelect(1);
		}
		else if (iarg.center.x >= 28 && iarg.center.x <= 508 && iarg.center.y >= 408 && iarg.center.y <= 460){
			iarg.gyeolEDa = 1;
		}
	}
}
//bool eqInt_3(int n1[3], int n2[3]) // ���ʿ��� �ڵ�
//{
//   if (n1[0] != n2[0]) return false;
//   if (n1[1] != n2[1]) return false;
//   if (n1[2] != n2[2]) return false;
//   return true;
//}
bool judge(iArg &iarg)
{
	int i, j = 0;
	int temp[3];
	int tempi;
	static int end = 0;
	
	for (i = 0; i<9; i++) // ī�弱�ø���Ʈ(3��) -> temp[3] ����
	{
		if (iarg.cList[i].getSelect()) // ī�� ���� �ν� 
		{
			temp[j++] = iarg.cList[i].getNum();
		}
	}
	
	tempi = HAPINT(temp[0], temp[1], temp[2]); // ���ڸ� ���ڷ� ���� 

	for (i = 0; i<iarg.hapCnt; i++)
	{
		if (tempi == iarg.hapList[i]) // ��ī�� ���� 
		{
			printState(1); // ���� ���
			printHap(tempi);
			printScore(2);
			end--;
			iarg.hapList[i] = end;
			return true;
		}
	}

	printState(2);   //���� �ƴ� ���
	printScore(-2);
	return false;
}
void gettime(struct time *p) // ���� �����͸� ��ȯ�Ҽ� �ֵ��� Call by pointer ��� ��� 
{
	char temp[30];
	char *cp;

	_strtime(temp); // temp char�迭 �ȿ� 00:00:00(��:��:��)���� ���ڿ� ���·� ���� 
	cp = strtok(temp, ":"); // temp�迭�� ù��° ':'���� ���ڿ��� ����� cp���� �ÿ� �ش��ϴ� ���ڿ��� �����ּҸ� ���� 
	p->ti_hour = atoi(cp); // ��� �ÿ� �ش��ϴ� ���ڿ��� ������ �����ͷ� ��ȯ�Ͽ� p->ti_hour�� ���� 
	cp = strtok(NULL, ":"); // temp�迭�� �ι�° ':'���� ���ڿ��� ����� cp���� �п� �ش��ϴ� ���ڿ��� �����ּҸ� ���� 
	p->ti_min = atoi(cp); // ��� �п� �ش��ϴ� ���ڿ��� ������ �����ͷ� ��ȯ�Ͽ� p->ti_min�� ���� 
	cp = strtok(NULL, ":"); // temp�迭�� ����° ':'���� ���ڿ��� ������ϳ� ':'�� ��Ÿ���� �ʰ� ���ڿ��� 
	// ������ �ǹǷ� ���� ���ڿ� ��ü�� �����Ѵ� ��, cp���� �ʿ� �ش��ϴ� ���ڿ��� �����ּҰ� �����Ѵ�. 
	p->ti_sec = atoi(cp); // ��� �ʿ� �ش��ϴ� ���ڿ��� ������ �����ͷ� ��ȯ�Ͽ� p->ti_sec�� ���� 
}
////////////////////////////////////////////////////////////////
int startOutput()
{
	char key;
	int x = 30, y = 10;
	int cursorP = 0;

	removeCursor();
	while (1)
	{
		gotoxy(x, y); textcolor(WHITE, BLACK);
		if (cursorP == 0){ textcolor(WHITE, DARKGRAY); }
		printf("  ������ ��������  ");
		gotoxy(x + 4, y + 4); textcolor(WHITE, BLACK);
		if (cursorP == 1){ textcolor(WHITE, DARKGRAY); }
		printf("  ������  ");

		key = getch();
		switch (key)
		{
		case UP_ARROW: cursorP--; break;
		case DOWN_ARROW: cursorP++; break;
		case ENTER:
			textcolor(WHITE, BLACK);               //ȭ��� �������
			system("cls");
			if (cursorP == 0){ return 1; }
			else if (cursorP == 1){ return 2; }
			break;
		}
		if (cursorP < 0){ cursorP = 1; }               //���ۺ���
		else if (cursorP > 1){ cursorP = 0; }
	}
}
void removeCursor()
{
	// Ŀ���� ���ִ� �ڵ� �κ� 
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 50;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}

void displayCursor()
{
	// Ŀ���� �츮�� �ڵ� �κ� 
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}
void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void moveWindow()
{
	HWND gl, mask, edge, con;
	gl = FindWindow(NULL, L"���հ���");
	mask = FindWindow(NULL, L"mask");
	edge = FindWindow(NULL, L"edges");
	con = FindWindow(NULL, L"C:\\Windows\\system32\\cmd.exe");

	SetWindowPos(gl, HWND_TOP, 0, 0, 640, 640, SWP_NOSIZE);
	MoveWindow(mask, 0, 0, 640, 640, true);
	MoveWindow(edge, 0, 0, 640, 640, true);
	MoveWindow(con, 650, 0, 800, 680, true);
}
////////////////////////////////////////////////////////////////////////
void printScore(int a)
{
	static int score = 0;
	gotoxy(5, 10);
	score += a;
	if (score < 0)
	{
		score = 0;
	}
	printf("���� : %d", score);

	gotoxy(5, 13);
	printf("�� ã����   +2");
	gotoxy(5, 14);
	printf("���� �ƴϸ� -2");
	gotoxy(5, 15);
	printf("�� : ���̸� +5");
	gotoxy(5, 16);
	printf("�� : Ʋ���� -3");


}
void printState(int a)
{
	int x = 33;
	static int y = 7;
	y += 1;
	gotoxy(x, y);
	if (y == 25)
	{
		y = 7;
		for (int i = 8; i < 28; i++)
		{
			gotoxy(x, i);
			printf("                       ");
		}
		return;
	}
	switch (a)
	{
	case 1:
		printf("'��' �Դϴ�");
		break;
	case 2:
		printf("'��' �� �ƴմϴ�");
		break;
	case 3:
		printf("'��' �Դϴ�");
		break;
	case 4:
		printf("'��' �� �ƴմϴ�");
		break;
	case 5:
		printf("�����մϴ�!!");
		break;
	case 6:
		printf("�ð� �ʰ�");
		break;
	case 7:
		printf("������ �����մϴ�");
		break;
	}
}
void printHap(int a)
{
	int x = 3;
	static int y = 20;
	y += 1;
	gotoxy(x, y);
	printf("�� ( %d, %d, %d )", HAPLIST1(a) + 1, HAPLIST2(a) + 1, HAPLIST3(a) + 1);
}
void border()
{

	printf("\n\n\n\n         ��   ��   ��   ��   ��   ��   ��   ��   ��\n");
	printf("\n����������������������������������������������������������������\n");
	for (int i = 0; i < 12; i++)
	{

		printf("��                          ��                                ��\n");
	}

	printf("������������������������������                                ��\n");
	for (int i = 0; i < 14; i++)
	{

		printf("��                          ��                                ��\n");
	}

	printf("����������������������������������������������������������������\n");

	gotoxy(0, 0);
	printf(" ");
}