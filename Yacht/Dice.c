//Dice.c
#include "Std.h"

void Dice_Init() {
	for (int i = 0; i < 5; i++) {
		SavedDice[i] = 0;
		RerollDice[i] = 0;
	}
}

void Dice_ThrowDice() {
	for (int i = 0; i < 5; i++) {
		if (SavedDice[i] == 0) {
			RerollDice[i] = rand() % 6 + 1;
		}
	}

	//dice에는 주사위 배열이 들어감.
	int dice[5];
	for (int i = 0; i < 5; i++)
		dice[i] = SavedDice[i] + RerollDice[i];

	Score_Setting(dice);
	UI_DicesPrint();
}

void Dice_ChangeDicePosition(int num_y, int num_x) {
	num_x--;
	if (SavedDice[num_x] != 0 && num_y == 1) {	//SavedDice 선택
		RerollDice[num_x] = SavedDice[num_x];
		SavedDice[num_x] = 0;
	}
	else if (RerollDice[num_x] != 0 && num_y == 2) {	//RerollDice 선택
		SavedDice[num_x] = RerollDice[num_x];
		RerollDice[num_x] = 0;
	}
}