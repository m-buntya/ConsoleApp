//======================================
//	�u���b�N������ ���C��
//======================================
#include "Stage.h"
#include "Utility.h"  // InitRand(),GetKey()
#include "IntervalTimer.h"
#include <stdio.h>  // printf()
// �֐��v���g�^�C�v
void game();

int main()
{
	InitRand();

	int c;
	do {
		game();
		printf("������x(y/n)?");
		while (true) {
			c = GetKey();
			if (c == 'y' || c == 'n') {
				break;
			}
		}
	} while (c == 'y');

	return 0;
}

const int FPS = 10;

void game()
{
	Stage stage[1];
	IntervalTimer timer[1];

	InitializeStage(stage);
	DrawScreen(stage, DM_READY);
	WaitKey();

	StartTimer(timer, FPS);
	while (true) {
		if (IsInterval(timer)) {
			MoveBall(stage);
			DrawScreen(stage, DM_GAME);

			if (IsBallMiss(stage)) {
				DrawScreen(stage, DM_READY);
				WaitKey();
				ResetBall(stage);
			}
			if (IsClear(stage)) {
				DrawScreen(stage, DM_CLEAR);
				WaitKey();
				break;
			}
		}
		if (KeyAvailable()) {
			Key c = GetKey();
			switch (c) {
			case ARROW_LEFT:
				// ���������R�[�f�B���O���Ă��������B
				// MovePaddle()���Ăт܂�
				MovePaddle(stage, -1);
				break;
			case ARROW_RIGHT:
				// ���������R�[�f�B���O���Ă��������B
				// MovePaddle()���Ăт܂�
				MovePaddle(stage, 1);
				break;
			case SPACE:  // �ꎞ��~
				DrawScreen(stage, DM_PAUSE);
				do {
					c = GetKey();
				} while (c != SPACE);
				break;
			}
		}
	}
}