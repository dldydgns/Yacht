//UI.h
#pragma once
#define KEYCODE_SPACEBAR 32
#define SCOREBOARD_ARROW_X 2

int ScoreBoard_Player_X[2];

int ui_DiceArray_Y[2];
int ui_DiceArray_X[5];

COORD ThrowBtn_XY;
COORD NowArrowPoint;

// Y�� : 0��°�� ThrowBtn, �������� ������ �Ʒ��� ����
// X�� : 0��°�� Categories, �������� �������� ����
int Arrow_Y[15];
int Arrow_X[7];

int awidx_x, awidx_y;	//arrow�� idx�� ����

enum ScoreBoard_Categories {
	Aces = 13, Duces, Threes, Fours, Fives, Sixes, 
	SubTotal = 20, Bonus,
	Choice = 23, F_Kind, F_House, S_Straight, L_Straight, Yacht,
	Total = 30
};

void UI_Init();
void UI_LogoPrint();
void UI_DiceBoard();
void UI_ScoreBoard();
void UI_ScoreBoard_Mark();
void UI_PlayerPositionPrint();
void UI_RerollCount();
void UI_DicesPrint();
void UI_PlayerScore_Mark();

void UI_KeyUp();
void UI_KeyDown();
void UI_KeyLeft();
void UI_KeyRight();
void UI_KeySpaceBar();
void UI_WinnerPrint();