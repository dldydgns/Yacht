//App.c
#include "Std.h"

void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void App_Init(){
	//콘솔창 크기 설정
	system("mode con cols=90 lines=33 | title Yacht");

	//랜덤시드 설정
	srand((unsigned int)time(NULL));

	UI_Init();
	Dice_Init();
	Score_Init();
	UI_LogoPrint();
}

void App_Run(){
	int arrowbtn = 224;
	int key;

	while (1) {
		UI_DiceBoard();
		UI_ScoreBoard();
		UI_DicesPrint();
		UI_RerollCount();
		UI_PlayerPositionPrint();
		UI_ScoreBoard_Mark();
		UI_PlayerScore_Mark();

		//게임종료 판별
		if (Score_IsFinish() == 1)
			return;

		key = _getch();

		if (key == KEYCODE_SPACEBAR) {
			UI_KeySpaceBar();
		}
		else if (key == arrowbtn) {
			switch (_getch()) {
			case 72: UI_KeyUp();    break;    // UP
			case 80: UI_KeyDown();  break;    // Down
			case 75: UI_KeyLeft();  break;    // Left
			case 77: UI_KeyRight(); break;    // Right
			default: return;
			}
		}

		system("cls");
	}
}

void App_Exit() {
	UI_WinnerPrint();
}
