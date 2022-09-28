//Score.c
#include "Std.h"

void Score_Init() {
	ScoreAmount = 0;
	Turn = 0;
	RerollCount = 0;
	memset(Players, -1, sizeof(scores) * 2);
	memset(&Scoreboard, 0, sizeof(scores));

	for (int i = 0; i < 2; i++) {
		Players[i].SubTotal = 0;
		Players[i].Bonus = 0;
		Players[i].Total = 0;
	}
}

void Score_ScoreBoard_Reset() {
	memset(&Scoreboard, 0, sizeof(scores));
}

void Score_Setting(int* dice) {
	//ace ~ six 까지 계산하여 넣기
	for (int i = 0; i < 5; i++) {
		switch (dice[i]) {
		case 1: Scoreboard.Aces += dice[i]; break;
		case 2: Scoreboard.Duces += dice[i]; break;
		case 3: Scoreboard.Threes += dice[i]; break;
		case 4: Scoreboard.Fours += dice[i]; break;
		case 5: Scoreboard.Fives += dice[i]; break;
		case 6: Scoreboard.Sixes += dice[i]; break;
		}
		Scoreboard.Choice += dice[i];
	}
	// subtotal은 1 ~ 6까지 점수 총합, 점수판에는 보여줄 필요 없음.
	// 현재 Bonus도 주사위 리롤과정에서 출력해서 보여줄 필요 없음.
	// Total도 마찬가지. (셋다 Player점수 표시에서 처리할것.)

	//F_Kind 초기화(각 주사위가 나온 횟수가 4 이상)
	if (Scoreboard.Aces / 1 >= 4 || Scoreboard.Duces / 2 >= 4 || Scoreboard.Threes / 3 >= 4 ||
		Scoreboard.Fours / 4 >= 4 || Scoreboard.Fives / 5 >= 4 || Scoreboard.Sixes / 6 >= 4) {
		Scoreboard.F_Kind = Scoreboard.Choice;
	}

	//Yacht 초기화(각 주사위가 나온 횟수가 5 이상)
	if (Scoreboard.Aces / 1 >= 5 || Scoreboard.Duces / 2 >= 5 || Scoreboard.Threes / 3 >= 5 ||
		Scoreboard.Fours / 4 >= 5 || Scoreboard.Fives / 5 >= 5 || Scoreboard.Sixes / 6 >= 5) {
		Scoreboard.Yacht = 50;
	}

	//중복 숫자를 막기 위해, 한번 나왔던 숫자들만 배열에 저장.
	int nums[8] = { 0 };
	for (int i = 1; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == dice[j])
				nums[i] = i;
		}
	}

	//시작 인덱스 구하기,(시작 인덱스들은 list_idx에 순서대로 저장)
	int list_idx[3];
	int n = 0;
	for (int i = 0; i < 7; i++) {
		if (nums[i] == 0 && nums[i + 1] != 0)
		{
			list_idx[n] = i + 1;
			n++;
		}
	}

	//시작 인덱스부터 0이 나올때까지 count 증가, 4면 S_Straight, 5면 L_Staright
	int count = 1;
	for (int startidx = 0; startidx < n; startidx++) {
		for (int i = list_idx[startidx]; nums[i + 1] != 0; i++) {
			count++;
		}
		if (count >= 4) {
			Scoreboard.S_Straight = 15;
			if (count == 5)
				Scoreboard.L_Straight = 30;
		}
		count = 1;
	}

	//풀하우스 추가
	count = 0;
	int numcount = 0;
	int sum = 0;
	for (int i = 0; i < 7; i++) {
		if (nums[i] != 0)
			count++;
	}
	if (count == 2) {
		for (int i = 0; i < 5; i++) {
			if (dice[0] == dice[i])
				numcount++;
			sum += dice[i];
		}

		if (numcount == 2 || numcount == 3)
			Scoreboard.F_House = sum;
	}
}
 
int Score_SavePlayersScore(int selected) { 
	int num = 0;
	//-1은 초기값(비어있는 값) 
	switch (selected) { 
	case Aces: if(Players[Turn].Aces != -1) return -1;
		num = Scoreboard.Aces;
		Players[Turn].Aces = num;
		Players[Turn].SubTotal += num;
		break;
	case Duces:	if(Players[Turn].Duces != -1) return -1;
		num = Scoreboard.Duces;
		Players[Turn].Duces = num;
		Players[Turn].SubTotal += num;
		break;
	case Threes: if(Players[Turn].Threes != -1) return -1;
		num = Scoreboard.Threes;
		Players[Turn].Threes = num;
		Players[Turn].SubTotal += num;
		break;
	case Fours:	if(Players[Turn].Fours	!= -1) return -1;
		num = Scoreboard.Fours;
		Players[Turn].Fours = num;
		Players[Turn].SubTotal += num;
		break;
	case Fives:	if(Players[Turn].Fives	!= -1) return -1;
		num = Scoreboard.Fives;
		Players[Turn].Fives = num;
		Players[Turn].SubTotal += num;
		break;
	case Sixes:	 if(Players[Turn].Sixes	!= -1) return -1;
		num = Scoreboard.Sixes;
		Players[Turn].Sixes = num;
		Players[Turn].SubTotal += num;
		break;
	case Choice: if(Players[Turn].Choice != -1) return -1;	
		num = Scoreboard.Choice;
		Players[Turn].Choice = num;
		break;
	case F_Kind: if(Players[Turn].F_Kind != -1) return -1;
		num = Scoreboard.F_Kind;
		Players[Turn].F_Kind = num;
		break;
	case F_House: if (Players[Turn].F_House != -1) return -1;
		num = Scoreboard.F_House;
		Players[Turn].F_House = num;
		break;
	case S_Straight: if(Players[Turn].S_Straight != -1) return -1;
		num = Scoreboard.S_Straight;
		Players[Turn].S_Straight = num;
		break;
	case L_Straight: if(Players[Turn].L_Straight != -1) return -1;
		num = Scoreboard.L_Straight;
		Players[Turn].L_Straight = num;
		break;
	case Yacht:	if(Players[Turn].Yacht != -1) return -1;
		num = Scoreboard.Yacht;
		Players[Turn].Yacht = num;
		break;
	default: return -1;
	 }
	//Total에 저장한 숫자 추가
	Players[Turn].Total += num;
	return 0;
 } 

int Score_IsFinish() {
	if (ScoreAmount >= MAX_SCOREAMOUNT)
		return 1;
	return 0;
}

int Score_WinnerPlayer() {
	if (Players[0].Total == Players[1].Total) //무승부
		return 0;

	if (Players[0].Total > Players[1].Total)
		return 1;
	else
		return 2;
}