#pragma once
#include<vector>
#include<process.h>
#include<Windows.h>
#include<time.h>         //_strtime()를 위해서 인클루드 함 
#include<windows.h>         // strtok(), atoi()를 위해서 인클루드 함
#include"card.h"
#include"input_opencv.h"
#include"output_opengl.h"
#include"arg.h"
#include<conio.h>

#define HAPLIST1(x) ((x)/100)            // 1번카드
#define HAPLIST2(x) ((x)%100/10)         // 2번카드
#define HAPLIST3(x) ((x)%10)            // 3번카드
#define HAPINT(x,y,z) ((x)*100+(y)*10+(z))   // 합


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
bool checkGuel;         //결 선택했을 때 그 전에도 결이였나 확인
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
	eArgp = &iarg;               // extern 변수
	int end = 0;
	struct time sttime;
	////////////////////////////////////////////////
	int start = -1;      //초기화

	while (1)
	{
		start = startOutput();
		if (start == 1){                     //시작하기
			border();
			printScore(0);
			printState(7);
			break;
		}
		else if (start == 2){ goto done; }         //종료
	}
	////////////////////////////////////////////////
	HWND hWnd;
	HDC hdc; // 핸들 : 대상을 구분하는 4바이트 정수(HWND, HDC 등) 

	HANDLE hInThread = (HANDLE)_beginthreadex(NULL, 0, inThread, eArgp, 0, NULL);
	HANDLE hOutThread = (HANDLE)_beginthreadex(NULL, 0, outThread, eArgp, 0, NULL);
	srand(time(0)); // 겹치지 않는 난수 발생

	createCList(HD, iarg. cList, rand()%6+1);   // 0~6, 8, 12(느림) - 원본
	//createCList(HD, iarg.cList, 1); // 테스트용
	gettime(&sttime); // 현재 시간 가져오기
	int init_second = sttime.ti_min * 60 + sttime.ti_sec; // 게임 시작할때의 시간
	iarg.time = 0; // 기본시간 0으로 초기화

	while (1){
		waitKey(30);
		moveWindow();      //창 위치 조절 

		gettime(&sttime); // 현재시간 불러옴
		time_change = (sttime.ti_min * 60 + sttime.ti_sec - init_second); //  현재시간 - 시작할때 시간(초)
		if (time_change == 153)
		{
			printState(6);
		}
		if (time_change > 1)
		{
			eArgp->time = time_change; // 기준 시간으로 초기화 
			if (eArgp->time == 153) // 정말 멍청하게 만든 종료조건
			{
				goto done;
			}
		}

		choiceRange(iarg);

		for (i = 0; i<iarg.hapCnt; i++)
		{
			if (iarg.hapList[i] == (-iarg.hapCnt))
			{
				end = 1;         //합 다 찾음
				break;
			}

		}
		if (iarg.gyeolEDa == 1 && end == 1){   //결 눌렀는데 결인 경우 
			printState(3);
			printScore(5);
			printState(5);
			goto done;
		}
		else if (checkGuel == FALSE && iarg.gyeolEDa == 1 && end != 1)   //결 눌렀는데 결이 아닌 경우
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
		// 결버튼 누른 조건 종료문 
		for (i = 0; i<9; i++)
		{
			if (iarg.cList[i].getSelect() == 1) // 카드를 선택한 경우
			{
				count++; // 카운트 값을 증가
				checkGuel = FALSE;   //카드 하나라도 선택하면 결 상태 초기화
			}
		}
		if (count < 3) // 필요치는 않은 코드 
		{
			count = 0;
		}
		if (count == 3)
		{
			if (judge(iarg)){      // 합이면 돌려
				eArgp->hapEDa = 1;
				waitKey(2500);
				eArgp->hapEDa = 0;
			}
			else               // 합 아니면 : 틀렸어 타임 줄어듬
			{
				waitKey(2500);
			}
			for (int i = 0; i<9; i++)   // 선택초기화
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

unsigned WINAPI inThread(void *iargp)   // 입력 핸들 쓰레드
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
unsigned WINAPI outThread(void *argp)   // 출력 핸들 쓰레드
{

	eArgp = (iArg *)argp;

	waitKey(10);
	output(eArgp);
	return 0;
}
// createCList(HD, iarg. cList, rand()%7);   // 0~6, 8, 12(느림)
void createCList(char *mode, vector<Card> &cList, int n)
{
	Card tList[9]; // 카드 클래스형 배열 객체 선언
	int hapCnt; // 임시 합 카운트 변수 선언

	while (1){            // 임시 카드덱 생성
		hapCnt = 0;
		for (int i = 0; i<9; i++)
		{
			tList[i] = Card(RAND); // 임시 카드 생성 
			for (int j = 0; j<i; j++)
			{
				if (tList[i] == tList[j]){ i--; } // 중복된 카드 나온경우 i를 제거하고 다시 생성
			}
		}
		eArgp->hapList.clear(); // hapList 벡터 내의 값들 모두 삭제 
		for (int i = 0; i<7; i++)
			for (int j = i + 1; j<8; j++)
				for (int k = j + 1; k<9; k++)
					if (tList[i].hap(mode, tList[j], tList[k])) // 임시 카드 리스트가 합인 경우
					{
						eArgp->hapList.push_back(HAPINT(i, j, k)); // 합 리스트에 추가 
						hapCnt++; // 합카운터 증가 
					}
					if (hapCnt == n){ // 합의 개수와 랜덤 카운트 변수가 같은 경우
						eArgp->hapCnt = hapCnt; // 합카운트 변수의 값을 구조체 합카운트변수에 대입
						break;
					}
	}

	cList.clear();               // 카드덱 생성
	for (int i = 0; i<9; i++){
		cList.push_back(tList[i]); // 임시 저장된 카드 값을 cList 벡터 뒤부터 삽입
		cList[i].setNum(i);   // 카드 번호 초기화
		//cList[i].show(); // 카드 내용 출력                     -> 출력 주석처리
	}
	
	//for (int i = 0; i<7; i++){      // 합인 경우 카드덱 출력
	//for (int j = i + 1; j<8; j++)
	//for (int k = j + 1; k<9; k++)
	//if (tList[i].hap(mode, tList[j], tList[k])){
	//cout << i << "," << j << "," << k << "번 카드 ";                     // 이거 주석처리해놓음
	//cout << "합(" << mode << ")!" << endl;

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
void choiceRange(iArg &iarg) // 카드 선택하는 함수
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
//bool eqInt_3(int n1[3], int n2[3]) // 불필요한 코드
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
	
	for (i = 0; i<9; i++) // 카드선택리스트(3장) -> temp[3] 으로
	{
		if (iarg.cList[i].getSelect()) // 카드 선택 인식 
		{
			temp[j++] = iarg.cList[i].getNum();
		}
	}
	
	tempi = HAPINT(temp[0], temp[1], temp[2]); // 세자리 숫자로 대입 

	for (i = 0; i<iarg.hapCnt; i++)
	{
		if (tempi == iarg.hapList[i]) // 합카드 선택 
		{
			printState(1); // 합인 경우
			printHap(tempi);
			printScore(2);
			end--;
			iarg.hapList[i] = end;
			return true;
		}
	}

	printState(2);   //합이 아닌 경우
	printScore(-2);
	return false;
}
void gettime(struct time *p) // 원본 데이터를 변환할수 있도록 Call by pointer 기법 사용 
{
	char temp[30];
	char *cp;

	_strtime(temp); // temp char배열 안에 00:00:00(시:분:초)순의 문자열 상태로 저장 
	cp = strtok(temp, ":"); // temp배열의 첫번째 ':'까지 문자열를 끊어내어 cp에게 시에 해당하는 문자열의 시작주소를 리턴 
	p->ti_hour = atoi(cp); // 끊어낸 시에 해당하는 문자열을 정수형 데이터로 변환하여 p->ti_hour에 저장 
	cp = strtok(NULL, ":"); // temp배열의 두번째 ':'까지 문자열를 끊어내어 cp에게 분에 해당하는 문자열의 시작주소를 리턴 
	p->ti_min = atoi(cp); // 끊어낸 분에 해당하는 문자열을 정수형 데이터로 변환하여 p->ti_min에 저장 
	cp = strtok(NULL, ":"); // temp배열의 세번째 ':'까지 문자열를 끊어내려하나 ':'은 나타나지 않고 문자열이 
	// 끝나게 되므로 남은 문자열 전체를 리턴한다 즉, cp에게 초에 해당하는 문자열의 시작주소가 리턴한다. 
	p->ti_sec = atoi(cp); // 끊어낸 초에 해당하는 문자열을 정수형 데이터로 변환하여 p->ti_sec에 저장 
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
		printf("  게임을 시작하지  ");
		gotoxy(x + 4, y + 4); textcolor(WHITE, BLACK);
		if (cursorP == 1){ textcolor(WHITE, DARKGRAY); }
		printf("  끝내기  ");

		key = getch();
		switch (key)
		{
		case UP_ARROW: cursorP--; break;
		case DOWN_ARROW: cursorP++; break;
		case ENTER:
			textcolor(WHITE, BLACK);               //화면색 원래대로
			system("cls");
			if (cursorP == 0){ return 1; }
			else if (cursorP == 1){ return 2; }
			break;
		}
		if (cursorP < 0){ cursorP = 1; }               //빙글빙글
		else if (cursorP > 1){ cursorP = 0; }
	}
}
void removeCursor()
{
	// 커서를 없애는 코드 부분 
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 50;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}

void displayCursor()
{
	// 커서를 살리는 코드 부분 
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
	gl = FindWindow(NULL, L"결합게임");
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
	printf("점수 : %d", score);

	gotoxy(5, 13);
	printf("합 찾으면   +2");
	gotoxy(5, 14);
	printf("합이 아니면 -2");
	gotoxy(5, 15);
	printf("결 : 결이면 +5");
	gotoxy(5, 16);
	printf("결 : 틀리면 -3");


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
		printf("'합' 입니다");
		break;
	case 2:
		printf("'합' 이 아닙니다");
		break;
	case 3:
		printf("'결' 입니다");
		break;
	case 4:
		printf("'결' 이 아닙니다");
		break;
	case 5:
		printf("축하합니다!!");
		break;
	case 6:
		printf("시간 초과");
		break;
	case 7:
		printf("게임을 시작합니다");
		break;
	}
}
void printHap(int a)
{
	int x = 3;
	static int y = 20;
	y += 1;
	gotoxy(x, y);
	printf("합 ( %d, %d, %d )", HAPLIST1(a) + 1, HAPLIST2(a) + 1, HAPLIST3(a) + 1);
}
void border()
{

	printf("\n\n\n\n         ☆   결   ★   합   ☆   게   ★   임   ☆\n");
	printf("\n┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┓\n");
	for (int i = 0; i < 12; i++)
	{

		printf("┃                          ┃                                ┃\n");
	}

	printf("┣━━━━━━━━━━━━━┫                                ┃\n");
	for (int i = 0; i < 14; i++)
	{

		printf("┃                          ┃                                ┃\n");
	}

	printf("┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┛\n");

	gotoxy(0, 0);
	printf(" ");
}