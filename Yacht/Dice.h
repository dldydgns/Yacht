//Dice.h
#pragma once

// 0�̸� ����ִ� �ֻ���
int SavedDice[5];
int RerollDice[5];

void Dice_Init();
void Dice_ThrowDice();
void Dice_ChangeDicePosition(int num_y, int num_x);
