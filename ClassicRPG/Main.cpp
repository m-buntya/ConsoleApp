//======================================
//	�^�[�����o�g�� ���C��
//======================================
#include "Stage.h"
#include "Map.h"
#include "Character.h"
#include "Utility.h"  // InitRand(),GetKey()
#include <stdio.h>  // printf()
#include "time.h"
// �֐��v���g�^�C�v
static void game();
static void TalkToKing(Stage* stage);
static void TalkToPrincess(Stage* stage);
static void TalkToBoss(Stage* stage);
static void RevivePlayer(Stage* stage);
static void DrawEnding();

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

static void game()
{
	Stage stage[1];
	Character player[1];
	Character boss[1];
	Character zako[1];

	SetCharacter(player,
		100,        // HP
		15,         // MP
		30,         // �U����
		"�䂤����", // ���O
		"");        // �A�X�L�[�A�[�g
	SetCharacter(boss,
		255,      // HP
		0,        // MP
		50,       // �U����
		"�܂���", // ���O
		"�@�@�`���`\n" // �A�X�L�[�A�[�g
		"�Ձi���M���j��"
	);
	SetCharacter(zako,
		3,          // HP
		0,          // MP
		2,          // �U����
		"�X���C��", // ���O 
		"�^�E�D�E�_\n" // �A�X�L�[�A�[�g
		"�`�`�`�`�`"
	);

	InitializeStage(stage, player, boss);
	RegistZako(stage, zako);
	ChangeStartMap(stage);

	while (true) {
		MapSpec* spec = GetMapSpec(stage);
		DrawMap(stage);

		int playerX = GetPlayerX(stage);
		int playerY = GetPlayerY(stage);
		switch (GetKey()) {
		case ARROW_UP:    playerY--; break;
		case ARROW_DOWN:  playerY++; break;
		case ARROW_LEFT:  playerX--; break;
		case ARROW_RIGHT: playerX++; break;
		}

		char c = GetMapData(spec, playerX, playerY);
		switch (c) {
		case outOfMap:
			ChangeMap(stage, &spec->nextMap_Out);
			break;
		case 'K':  // ���l�̏�
			ChangeMap(stage, &spec->nextMap_K);
			break;
		case 'B':  // �����̏�
			ChangeMap(stage, &spec->nextMap_B);
			break;
		case '0':  // ��
			TalkToKing(stage);
			break;
		case '1':  // �P
			TalkToPrincess(stage);
			break;
		case '2':  // ����
			TalkToBoss(stage);
			break;
		case '.':  // ��/���n
		case '#':  // �K�i/��
			SetPlayerPosition(stage, playerX, playerY);
			if (IsBattleEncount(spec)) {
				// ���������R�[�f�B���O���Ă��������B
				// �P�U����1�̊m���ŃU�R�퓬���s���܂�
				if (GetRand(16) == 0) {
					BattleZako(stage);
				}
			}
			break;
		}
		if (IsPlayerDead(stage)) {
			RevivePlayer(stage);
			continue; // continue while()
		}
		if (IsBossDead(stage)) {
			break;  // exit while()
		}
	}
	DrawEnding();
}
// ���l�Ƙb��
static void TalkToKing(Stage* stage)
{
	// ���������R�[�f�B���O���Ă��������B
	// �ȉ���\������ �L�[�E�F�C�g���܂�
	printf("���u�����@�䂤�����I\n"
		"�Ђ����́@�܂��傤�́@�܂�����\n"
		"�������@���������@�������Ă���I\n");
	WaitKey();
	
}
// �P�Ƙb��
static void TalkToPrincess(Stage* stage)
{
	// ���������R�[�f�B���O���Ă��������B
	// �ȉ���\������ �L�[�E�F�C�g�����̂��A�v���[���̑S�񕜂��s���܂�
	printf("���u���݂Ɂ@���̂���@�������܂��B\n"
		"�����@���݂�I\n"
		"�䂤���Ⴓ�܂Ɂ@���キ�ӂ����I\n");
	WaitKey();
	for (int i = 0; i < 2; ++i)
	{
		printf(EscBgWHITE);
		DrawMap(stage);	
		Wait(200);
		printf(EscBgDEFAULT);
		DrawMap(stage);		
		Wait(200);
	}
	RecoverAllStatus(stage->player);
}
// �{�X�Ƙb��
static void TalkToBoss(Stage* stage)
{
	// ���������R�[�f�B���O���Ă��������B
	// �ȉ���\������ �L�[�E�F�C�g�����̂��A�{�X�퓬���s���܂�
	printf("���u���납�ȁ@�ɂ񂰂��I\n"
		"�킪�@��ڂ����@�͂΂ނ��̂�\n"
		"���̂悩��@���������Ă����I\n");
	WaitKey();
	
	BattleBoss(stage);
}
// �v���[������
static void RevivePlayer(Stage* stage)
{
	// ���������R�[�f�B���O���Ă��������B
	// �v���[���̑S�񕜁A�����}�b�v�ւ̍ăG���g���[�����̂�
	// �ȉ���\�����āA�L�[�E�F�C�g���܂�
	RecoverAllStatus(stage->player);
	ChangeStartMap(stage);
	DrawMap(stage);
	printf( "���u�����@�䂤�����I\n"
	 "���݂��@���Ȃ����@������ꂽ�I\n"
	 "�䂤����Ɂ@���������@����I\n");
	WaitKey();
}

// �G���f�B���O�`��
static void DrawEnding()
{
	// ���������R�[�f�B���O���Ă��������B
	// ��ʏ������āA�ȉ���\�����܂��B�L�[�E�F�C�g���܂�
	printf("�@�܂����́@�ق�с@��������\n"
		"�߂ڂ��̂�������@������ꂽ�I\n"
		"\n"
		"�@�����́@�ӂ�������@�䂤�����\n"
		"���������Ƃ߂����A�����\n"
		"�݂����̂́@���Ȃ������Ƃ����c\n"
		"\n"
		"\n"
		"�@�@�@�@�s�g�d�@�d�m�c\n"
		"\n");

	WaitKey();
}