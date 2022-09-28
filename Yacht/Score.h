//Score.h
#pragma once
#define REROLLCOUNT_MAX 3
#define MAX_SCOREAMOUNT 22

typedef struct _scores {
	int Aces;
	int Duces;
	int Threes;
	int Fours;
	int Fives;
	int Sixes;
	int SubTotal;
	int Bonus;
	int Choice;
	int F_Kind;
	int F_House;
	int S_Straight;
	int L_Straight;
	int Yacht;
	int Total;
}scores;

//기록된 숫자의 갯수
int ScoreAmount;

//Turn = 0 or 1
int Turn;
//RerollCount = 0,1
int RerollCount;
scores Players[2];
scores Scoreboard;

void Score_Init();
void Score_ScoreBoard_Reset();
void Score_Setting(int* dice);

int Score_SavePlayersScore(int selected);
int Score_IsFinish();
int Score_WinnerPlayer();