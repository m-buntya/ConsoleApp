//======================================
//	�퍑�V�~�����[�V����  UI
//======================================
#include "UI.h"
#include "Stage.h"
#include "Castle.h"
#include "Lord.h"
#include "Utility.h"
#include "Troop.h"
#include <stdio.h>
#include <string.h> // strchr()
// �֐��v���g�^�C�v
static int getKeyInRange(int min, int max);
static char getKeyInList(const char* list);

// �v���[��ID����͂���
CastleId InputPlayerCastle(Stage* stage)
{
	DrawScreen(stage, DM_Intro, 0);
	printf("���₩�����܁A���炪����́@���̂�����\n"
		"�ǂ��Ɂ@����܂��邩�H�I�i0�`%d�j\n", stage->castlesSize - 1);
	putchar('\n');

	int num = getKeyInRange(0, stage->castlesSize - 1);
	return (CastleId)num;
}
// �v���[���^�[���̋��������
Command InputPlayerTurn(Stage* stage, Castle* castle, CastleId* outTarget, int* outTroopCount)
{
	const char CANCEL = 'x';
	char list[CASTLE_MAX + 2];
	char* listp;
	//
	// �i�R������
	//
	printf("%s���܁A�ǂ��Ɂ@���񂮂�@���܂����H\n", GetLordFirstName(stage, stage->playerLord));
	putchar('\n');

	listp = list;
	CastleId* connectedList = castle->connectedList;
	for (int i = 0; ; i++) {
		CastleId id = connectedList[i];
		if (id == CASTLE_NONE) break;
		const char* opt = (GetCastleOwner(stage, id) == stage->playerLord) ? "�ڑ�" : "�U��";
		printf("%d %s (%s)\n", id, GetCastleName(stage, id), opt);
		*listp++ = id + '0';
	}
	printf("%c ���񂮂񂵂Ȃ�\n", CANCEL);
	*listp++ = CANCEL;
	*listp = '\0';
	putchar('\n');

	char c = getKeyInList(list);
	if (c == CANCEL) {
		return CMD_Cancel;
	}
	//
	// �i�R���镺�������
	//
	CastleId targetId = (CastleId)(c - '0');
	Command cmd = CMD_Attack;

	int troopMax = castle->troopCount;
	if (GetCastleOwner(stage, targetId) == stage->playerLord) {
		int targetCapacity = TROOP_MAX - GetCastleTroopCount(stage, targetId);
		if (troopMax > targetCapacity) {
			troopMax = targetCapacity;
		}
		cmd = CMD_Transit;
	}
	printf("%s�Ɂ@�Ȃ񂺂�ɂ�@���񂮂�@���܂����H�i0�`%d�j\n"
		, GetCastleName(stage, targetId)	// �i�R��̏�̖��O
		, troopMax);					    // �i�R����
	putchar('\n');
	int troopCount = getKeyInRange(0, troopMax);

	*outTarget = targetId;
	*outTroopCount = troopCount;
	return cmd;
}
// min�`max�̐�������͂�����
static int getKeyInRange(int min, int max)
{
	// ���������R�[�f�B���O���Ă��������B
	//  GetKey()�ŃL�[���͂��Amin�`max �̐����L�[��
	//  ���͂����܂ŌJ��Ԃ��܂�
	//  min�`max�̐����L�[�������ꂽ��A���̐��l��Ԃ��܂�
	unsigned char c;
	int num;
	do {
		c = (unsigned char)GetKey();
		num = c - '0';
	} while (num < min || max < num);
	return num;
}
// list�ɂ���L�[����͂�����
static char getKeyInList(const char* list)
{
	// ���������R�[�f�B���O���Ă��������B
	//  GetKey()�ŃL�[���͂��Alist������ɂ���L�[��
	//  ���͂����܂ŌJ��Ԃ��܂�
	//  list������ɂ���L�[�������ꂽ��A���̕�����Ԃ��܂�
	char c;
	do {
		c = GetKey();
	} while (strchr(list, c) == nullptr);
	return c;
}