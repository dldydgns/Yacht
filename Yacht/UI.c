//UI.c
#include "Std.h"

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UI_Init() {
	//커서 깜빡임 없애기
	CONSOLE_CURSOR_INFO cur;
	cur.dwSize = 1;
	cur.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);

	//스코어보드에서 Player1, Player2의 X좌표 
	ScoreBoard_Player_X[0] = 28;
	ScoreBoard_Player_X[1] = 51;

	ui_DiceArray_Y[0] = 2;
	ui_DiceArray_Y[1] = 7;

	for (int i = 0; i < 5; i++) {
		ui_DiceArray_X[i] = 7 + (i * 12);
	}

	ThrowBtn_XY.X = 75;
	ThrowBtn_XY.Y = 3;

	//Arrow가 갈 수 있는 Y값 초기화
	Arrow_Y[0] = ThrowBtn_XY.Y;	//0번째는 ThrowBtn
	Arrow_Y[1] = ui_DiceArray_Y[0] - 2;	//주사위 중앙에서 주사위의 가장 위로 위치 옮겨서 저장.
	Arrow_Y[2] = ui_DiceArray_Y[1] - 2;
	int idx = 3;
	for (enum ScoreBoard_Categories ct = Aces; ct <= Sixes; ct++) {
		Arrow_Y[idx] = ct;
		idx++;
	}
	for (enum ScoreBoard_Categories ct = Choice; ct <= Yacht; ct++) {
		Arrow_Y[idx] = ct;
		idx++;
	}

	//Arrow가 갈 수 있는 X값 초기화
	Arrow_X[0] = SCOREBOARD_ARROW_X;
	for (int i = 1; i < 6; i++) {
		Arrow_X[i] = ui_DiceArray_X[i - 1];
	}
	Arrow_X[6] = ThrowBtn_XY.X;

	//arrow idx값 초기화
	awidx_y = 0;
	awidx_x = 6;

	NowArrowPoint = ThrowBtn_XY;
};

void UI_LogoPrint() {
	printf(" -----------------------------------------------------\n");
	printf("|                                                     |\n");
	printf("|   ##    ##   ###      ######  ##     ## ########    |\n");
	printf("|    ##  ##   ## ##    ##    ## ##     ##    ##       |\n");
	printf("|     ####   ##   ##   ##       ##     ##    ##       |\n");
	printf("|      ##   ##     ##  ##       #########    ##       |\n");
	printf("|      ##   #########  ##       ##     ##    ##       |\n");
	printf("|      ##   ##     ##  ##    ## ##     ##    ##       |\n");
	printf("|      ##   ##     ##   ######  ##     ##    ##       |\n");
	printf("|                                                     |\n");
	printf(" -----------------------------------------------------\n");
	printf("                                                       \n");
	printf("                Press Spacebar to Start                \n");
	
	while (1)
		if (_getch() == KEYCODE_SPACEBAR)
		{
			system("cls");
			return;
		}
}

void UI_DiceBoard() {
	printf("   +-------+   +-------+   +-------+   +-------+   +-------+   \n");
	printf("   |       |   |       |   |       |   |       |   |       |   \n");
	printf("   |       |   |       |   |       |   |       |   |       |   \n");
	printf("   |       |   |       |   |       |   |       |   |       |          +---------+\n");
	printf("   +-------+   +-------+   +-------+   +-------+   +-------+          |  Throw  |\n");
	printf("   +-------+   +-------+   +-------+   +-------+   +-------+          |   Dice  |\n");
	printf("   |       |   |       |   |       |   |       |   |       |          +---------+\n");
	printf("   |       |   |       |   |       |   |       |   |       |   \n");
	printf("   |       |   |       |   |       |   |       |   |       |   \n");
	printf("   +-------+   +-------+   +-------+   +-------+   +-------+   \n");
}

void UI_ScoreBoard() {
	printf("+--------------------------------------------------------------+\n");
	printf("|  [Categorise]  |     [ player 1 ]     |     [ player 2 ]     |\n");
	printf("|----------------+----------------------+----------------------|\n");
	printf("|   | Aces       |                      |                      |\n");
	printf("|   | Duces      |                      |                      |\n");
	printf("|   | Threes     |                      |                      |\n");
	printf("|   | Fours      |                      |                      |\n");
	printf("|   | Fives      |                      |                      |\n");
	printf("|   | Sixes      |                      |                      |\n");
	printf("|---+------------+----------------------+----------------------|\n");
	printf("|   | [SubTotal] |                      |                      |\n");
	printf("|   | +35 Bouse  |                      |                      |\n");
	printf("|---+------------+----------------------+----------------------|\n");
	printf("|   | Choice     |                      |                      |\n");
	printf("|   | 4 of Kind  |                      |                      |\n");
	printf("|   | Full House |                      |                      |\n");
	printf("|   | S.Straght  |                      |                      |\n");
	printf("|   | L.Straght  |                      |                      |\n");
	printf("|   | Yacht      |                      |                      |\n");
	printf("|---+------------+----------------------+----------------------|\n");
	printf("|   |  [Total]   |                      |                      |\n");
	printf("+--------------------------------------------------------------+\n");
}

void UI_ScoreBoard_Mark() {
	gotoxy(ScoreBoard_Player_X[Turn], Aces);
	printf("%d", Scoreboard.Aces);
	gotoxy(ScoreBoard_Player_X[Turn], Duces);
	printf("%d", Scoreboard.Duces);
	gotoxy(ScoreBoard_Player_X[Turn], Threes);
	printf("%d", Scoreboard.Threes);
	gotoxy(ScoreBoard_Player_X[Turn], Fours);
	printf("%d", Scoreboard.Fours);
	gotoxy(ScoreBoard_Player_X[Turn], Fives);
	printf("%d", Scoreboard.Fives);
	gotoxy(ScoreBoard_Player_X[Turn], Sixes);
	printf("%d", Scoreboard.Sixes);
	gotoxy(ScoreBoard_Player_X[Turn], Choice);
	printf("%d", Scoreboard.Choice);
	gotoxy(ScoreBoard_Player_X[Turn], F_Kind);
	printf("%d", Scoreboard.F_Kind);
	gotoxy(ScoreBoard_Player_X[Turn], F_House);
	printf("%d", Scoreboard.F_House);
	gotoxy(ScoreBoard_Player_X[Turn], S_Straight);
	printf("%d", Scoreboard.S_Straight);
	gotoxy(ScoreBoard_Player_X[Turn], L_Straight);
	printf("%d", Scoreboard.L_Straight);
	gotoxy(ScoreBoard_Player_X[Turn], Yacht);
	printf("%d", Scoreboard.Yacht);
}

void UI_PlayerPositionPrint() {
	gotoxy(NowArrowPoint.X, NowArrowPoint.Y);
	if (NowArrowPoint.Y < Aces) {
		printf("V");
	}
	else {
		printf(">");
	}
}

void UI_RerollCount() {
	gotoxy(Arrow_X[6] - 4, 1);
	printf("Reroll : %d", 3 - RerollCount);
}

void UI_DicePrint(int row, int col, int number) {
	int distance = 2;

	int y = row;
	int x = col;

	switch (number) {
	case 1: 
		gotoxy(ui_DiceArray_X[x], ui_DiceArray_Y[y]);
		printf("*");
		break;
	case 2:
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] - 1);
		printf("*");
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] + 1);
		printf("*");   
		break;		   
	case 3:			   
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] - 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x], ui_DiceArray_Y[y]);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] + 1);
		printf("*");   
		break;		   
	case 4:			   
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] - 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] - 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] + 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] + 1);
		printf("*");   
		break;		   
	case 5:			   
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] - 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] - 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x], ui_DiceArray_Y[y]);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] + 1);
		printf("*");   
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] + 1);
		printf("*");
		break;
	case 6: 
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] - 1);
		printf("*");
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y]);
		printf("*");
		gotoxy(ui_DiceArray_X[x] - distance, ui_DiceArray_Y[y] + 1);
		printf("*");
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] - 1);
		printf("*");
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y]);
		printf("*");
		gotoxy(ui_DiceArray_X[x] + distance, ui_DiceArray_Y[y] + 1);
		printf("*"); 
		break;
	}
}

void UI_DicesPrint() {
	//Arrow_Y[1] => SavedDice, Arrow_Y[2] => RerollDice
	//Arrow_X[1],[2].....[5]
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0) UI_DicePrint(i, j, SavedDice[j]);
			if (i == 1) UI_DicePrint(i, j, RerollDice[j]);
		}
	}
}

void UI_PlayerScore_Mark() {
	SetColor(SkyBlue);
	for (int i = 0; i < 2; i++) {
		if (i == 0) SetColor(SkyBlue);
		else if (i == 1) SetColor(Green);
		gotoxy(ScoreBoard_Player_X[i], Aces);
		if (Players[i].Aces != -1)   printf("%-3d", Players[i].Aces);
		gotoxy(ScoreBoard_Player_X[i], Duces);
		if (Players[i].Duces != -1)   printf("%-3d", Players[i].Duces);
		gotoxy(ScoreBoard_Player_X[i], Threes);
		if (Players[i].Threes != -1)   printf("%-3d", Players[i].Threes);
		gotoxy(ScoreBoard_Player_X[i], Fours);
		if (Players[i].Fours != -1)   printf("%-3d", Players[i].Fours);
		gotoxy(ScoreBoard_Player_X[i], Fives);
		if (Players[i].Fives != -1)   printf("%-3d", Players[i].Fives);
		gotoxy(ScoreBoard_Player_X[i], Sixes);
		if (Players[i].Sixes != -1)   printf("%-3d", Players[i].Sixes);
		//SubTotal과 Bonus는 무조건 출력
		gotoxy(ScoreBoard_Player_X[i] - 3, SubTotal);
		printf("[%2d/63]", Players[i].SubTotal);
		gotoxy(ScoreBoard_Player_X[i], Bonus);
		printf("%-3d", Players[i].Bonus);
		gotoxy(ScoreBoard_Player_X[i], Choice);
		if (Players[i].Choice != -1)   printf("%-3d", Players[i].Choice);
		gotoxy(ScoreBoard_Player_X[i], F_Kind);
		if (Players[i].F_Kind != -1)   printf("%-3d", Players[i].F_Kind);
		gotoxy(ScoreBoard_Player_X[i], F_House);
		if (Players[i].F_House != -1)   printf("%-3d", Players[i].F_House);
		gotoxy(ScoreBoard_Player_X[i], S_Straight);
		if (Players[i].S_Straight != -1)   printf("%-3d", Players[i].S_Straight);
		gotoxy(ScoreBoard_Player_X[i], L_Straight);
		if (Players[i].L_Straight != -1)   printf("%-3d", Players[i].L_Straight);
		gotoxy(ScoreBoard_Player_X[i], Yacht);
		if (Players[i].Yacht != -1)   printf("%-3d", Players[i].Yacht);
		//Total도 무조건 출력, Total은 100이 넘을 수 있으니 3칸차지
		gotoxy(ScoreBoard_Player_X[i], Total);
		printf("%-3d", Players[i].Total);
		SetColor(White);
	}
}

void UI_KeyUp() {
	if (awidx_y == 0) //throwbtn.y
		return;

	if (awidx_y == 1)
		return;

	awidx_y--;

	if (awidx_y == 2)	//Dice쪽으로 넘어갔으면 X값도 첫번째 주사위 위치로 변경
		awidx_x = 1;

	NowArrowPoint.X = Arrow_X[awidx_x];
	NowArrowPoint.Y = Arrow_Y[awidx_y];
}

void UI_KeyDown() {
	if (awidx_y == 0) {		//throwbtn.y
		awidx_x = 0;
		awidx_y = 3;

		NowArrowPoint.X = Arrow_X[awidx_x];
		NowArrowPoint.Y = Arrow_Y[awidx_y];
		return;
	}

	if (awidx_y == 14)
		return;

	awidx_y++;

	if (awidx_y > 2)	//ScoreBoard로 넘어갔으면 X값도 변경
		awidx_x = 0;

	NowArrowPoint.X = Arrow_X[awidx_x];
	NowArrowPoint.Y = Arrow_Y[awidx_y];
}

void UI_KeyLeft() {
	if (awidx_x == 6) {		//throwbtn
		// [1,4]주사위 위치로 이동
		awidx_y = 2;
		awidx_x = 5;

		NowArrowPoint.X = Arrow_X[awidx_x];
		NowArrowPoint.Y = Arrow_Y[awidx_y];
		return;
	}

	if (awidx_x == 0 || awidx_x == 1)
		return;

	awidx_x--;

	NowArrowPoint.X = Arrow_X[awidx_x];
	NowArrowPoint.Y = Arrow_Y[awidx_y];
}

void UI_KeyRight() {
	if (awidx_x == 6)	//throwbtn
		return;

	if (awidx_y > 2)
		return;

	if (awidx_x == 5)
		awidx_y = 0;

	awidx_x++;


	NowArrowPoint.X = Arrow_X[awidx_x];
	NowArrowPoint.Y = Arrow_Y[awidx_y];
}

void UI_KeySpaceBar() {
	if (awidx_x == 6) {	//ThrowBtn
		if (RerollCount == REROLLCOUNT_MAX)
			return;
		Score_ScoreBoard_Reset();
		Dice_ThrowDice();
		RerollCount++;
	}

	if (awidx_x == 0) {	//ScoreBoard
		//players에 저장코드
		if (Score_SavePlayersScore(Arrow_Y[awidx_y]) == -1)
			return;

		//기록된 숫자의 갯수 증가
		ScoreAmount++;
		
		//서브 보너스 판별
		if (Players[Turn].Bonus == 0 && Players[Turn].SubTotal >= 63)
		{
			Players[Turn].Bonus = 35;
			Players[Turn].Total += Players[Turn].Bonus;
		}

		//초기화코드
		Dice_Init();
		Score_ScoreBoard_Reset();
		NowArrowPoint = ThrowBtn_XY;
		awidx_x = 6; awidx_y = 0;

		RerollCount = 0;
		Turn = !Turn;
	}

	if (0 < awidx_x && awidx_x < 6) { //Dices
		Dice_ChangeDicePosition(awidx_y, awidx_x);
	}
}

void UI_WinnerPrint() {
	gotoxy(0, 0);
	SetColor(Yellow);
	printf("   +-------------------------------------------------------+   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   |                                                       |   \n");
	printf("   +-------------------------------------------------------+   \n");
	switch(Score_WinnerPlayer()) {
	case 0:
		SetColor(Red);
		gotoxy(8, 2); printf(":::::::::  :::::::::      :::     :::       ::: ");
		gotoxy(8, 3); printf(":+:    :+: :+:    :+:   :+: :+:   :+:       :+: "); 
		gotoxy(8, 4); printf("+:+    +:+ +:+    +:+  +:+   +:+  +:+       +:+ "); 
		gotoxy(8, 5); printf("+#+    +:+ +#++:++#:  +#++:++#++: +#+  +:+  +#+ "); 
		gotoxy(8, 6); printf("+#+    +#+ +#+    +#+ +#+     +#+ +#+ +#+#+ +#+ "); 
		gotoxy(8, 7); printf("#+#    #+# #+#    #+# #+#     #+#  #+#+# #+#+#  ");
		gotoxy(8, 8); printf("#########  ###    ### ###     ###   ###   ###   ");
		break;
	case 1: 
		SetColor(SkyBlue);
		gotoxy(8, 2); printf(":::       ::: ::::::::::: ::::    :::    :::   ");
		gotoxy(8, 3); printf(":+:       :+:     :+:     :+:+:   :+:  :+:+:   ");
		gotoxy(8, 4); printf("+:+       +:+     +:+     :+:+:+  +:+    +:+   ");
		gotoxy(8, 5); printf("+#+  +:+  +#+     +#+     +#+ +:+ +#+    +#+   ");
		gotoxy(8, 6); printf("+#+ +#+#+ +#+     +#+     +#+  +#+#+#    +#+   ");
		gotoxy(8, 7); printf(" #+#+# #+#+#      #+#     #+#   #+#+#    #+#   ");
		gotoxy(8, 8); printf("  ###   ###   ########### ###    ####  ####### "); break;
	case 2:
		SetColor(Green);
		gotoxy(7, 2); printf(":::       ::: ::::::::::: ::::    :::   ::::::::  ");
		gotoxy(7, 3); printf(":+:       :+:     :+:     :+:+:   :+:  :+:    :+: ");
		gotoxy(7, 4); printf("+:+       +:+     +:+     :+:+:+  +:+        +:+  ");
		gotoxy(7, 5); printf("+#+  +:+  +#+     +#+     +#+ +:+ +#+      +#+    ");
		gotoxy(7, 6); printf("+#+ +#+#+ +#+     +#+     +#+  +#+#+#    +#+      ");
		gotoxy(7, 7); printf(" #+#+# #+#+#      #+#     #+#   #+#+#   #+#       ");
		gotoxy(7, 8); printf("  ###   ###   ########### ###    ####  ########## "); break;
	}
	//화면아래 끝
	gotoxy(0, 32);
	SetColor(White);
	system("pause");
}