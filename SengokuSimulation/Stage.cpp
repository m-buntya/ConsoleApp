//======================================
//	�퍑�V�~�����[�V����  �X�e�[�W
//======================================
#include "Stage.h"
#include "Lord.h"
#include "Castle.h"
#include "Utility.h"
#include "Troop.h"
#include "UI.h"
#include "AI.h"
#include <stdio.h>  // printf(),putchar()
#include <stdlib.h> // calloc(),free(),exit()
#include <assert.h> // assert()
// �֐��v���g�^�C�v
static void printTurnOrder(Stage* stage, int turn);
static void ExecPlayerTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount);
static void ExecNpcTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount);
static void TransitTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount);
static void AttackTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount);
static void SiegeBattle(Stage* stage, LordId offenseLord, int offenseTroopCount, CastleId defenseCastle);
static int getCastleCount(Stage* stage, LordId lord);
static Castle* GetCastle(Stage* stage, CastleId id);
static LordId changeLordId(Stage* stage, LordId id);

// ������
void InitializeStage(Stage* stage, Castle castles[], int castlesSize, int startYear, Chronology* chro)
{
	stage->year = startYear;
	stage->chro = chro;
	stage->castles = (Castle*)calloc(castlesSize, sizeof(Castle));
	if (stage->castles == nullptr) {
		printf("calloc���s");
		exit(1);
	}
	for (int i = 0; i < castlesSize; i++) {
		stage->castles[i] = castles[i];  // �R�s�[
	}
	stage->castlesSize = castlesSize;
	stage->playerLord = LORD_NONE;
	stage->isHonnojiEvent = false;
}
// ��n��
void FinalizeStage(Stage* stage)
{
	free(stage->castles);
	stage->castles = nullptr;
}
// �X�^�[�g
void StartStage(Stage* stage)
{
	for (int i = 0; i < stage->castlesSize; i++) {
		SetCastleOwner(stage, (CastleId)i, (LordId)i);
		SetCastleTroopCount(stage, (CastleId)i, TROOP_BASE);
	}
}
// �v���[���喼�̃Z�b�g
void SetPlayerLord(Stage* stage, CastleId castleId)
{
	stage->playerLord = GetCastleOwner(stage, castleId);
}
// �C���g�����b�Z�[�W
void IntroStage(Stage* stage, CastleId playerCastle)
{
	printf("%s���܁A %s����@�Ă񂩂Ƃ�����\n�߂����܂��傤���I\n"
		, GetLordFirstName(stage, stage->playerLord)
		, GetCastleName(stage, playerCastle)
	);
	WaitKey();
}
// �X�N���[���`��
void DrawScreen(Stage* stage, DrawMode mode, int turn)
{
	ClearScreen();
	printf("%s",
		//0       1         2         3         4   
		//23456789012345678901234567890123456789012345678901234
		"1570�˂�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�`\n"      // 01
		"�@�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@0�đ�5�@�`\n"      // 02
		"�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`1�t��5�@�ɒB�@�`�`\n"      // 03
		"�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�`�㐙�@�@�@�@�@�`�`\n"      // 04
		"�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�@�@�@�@�@�@�@�@�`�`\n"      // 05
		"�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@2�U�P5�@�@�@�`�`\n"      // 06
		"�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�@���c�@�@�@�`�`�`\n"      // 07
		"�`�`�`�`�`�`�@�@�@�@�@�@�@5��5�@�@�@�@�@�@�@�@�`�`�`\n"      // 08
		"�`�`�`�`�@7�g�c5�@6���5�@�D�c�@4����5�@3���c5�@�`�`�`\n"      // 09
		"�`�`�`�@�@�ї��@�@�����@�@�@�@�@����@�@�k���`�`�`�`�`\n"      // 10
		"�`�`�@�`�`�`�`�`�`�`�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 11
		"�`�@�@�@�`�@8���L5�`�`�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 12
		"�`�@�@�@�`�`���@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 13
		"�`9����5�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 14
		"�`���Á`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 15
		"�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 16
		"\n");

	PrintCursor(1, 1); printf("%4d�˂�", stage->year);
	for (int i = 0; i < stage->castlesSize; i++) {
		// ���������R�[�f�B���O���Ă�������
		// (��ID)i ���� Castle* ���擾����
		// ��� curx, cury owner, troopCount, mapName ���擾���܂�
		// (curx,cury)�̈ʒu�� (id)(��̃}�b�v��)(troopCount�l) ��\�����܂�
		// (curx,cury+1)�̈ʒu�� (���̃}�b�v��) ��\�����܂�
		Castle* castle = GetCastle(stage, (CastleId)i);
		int curx = GetCastleCurx(castle);
		int cury = GetCastleCury(castle);
		LordId owner = GetCastleOwner(castle);
		int troopCount = GetCastleTroopCount(castle);
		const char* mapName = GetCastleMapName(castle);
		PrintCursor(curx, cury);
		printf("%d%s%d", i, mapName, troopCount);
		PrintCursor(curx, cury + 1);
		printf("%s", GetLordMapName(stage, owner));
	}
	PrintCursor(1, 18);
}
// �^�[���̏��Ԃ��V���b�t��
void MakeTurnOrder(Stage* stage)
{
	CastleId* turnOrder = stage->turnOrder;
	for (int i = 0; i < stage->castlesSize; i++) {
		turnOrder[i] = (CastleId)i;
	}
	// ���������R�[�f�B���O���Ă��������B
	// turnOrder�𑖍�(���[�v�ϐ�i)���āA
	// 0�`castleSize-1 �̗��� j ���o����
	// turnOrder[i] �� turnOrder[j] ���������܂�
	for (int i = 0; i < stage->castlesSize; i++)
	{
		int j = GetRand(stage->castlesSize);
		CastleId tmp = turnOrder[i];
		turnOrder[i] = turnOrder[j];
		turnOrder[j] = tmp;
	}
}
// �N�z��
void NextYear(Stage* stage)
{
	stage->year++;
	for (int i = 0; i < stage->castlesSize; i++) {
		Castle* castle = GetCastle(stage, (CastleId)i);
		int troopCount = GetCastleTroopCount(castle);
		if (troopCount < TROOP_BASE) {
			// ������ BASE��菬�Ȃ� ����
			AddCastleTroopCount(castle, +1);
		}
		else if (troopCount > TROOP_BASE) {
			// ������ BASE����Ȃ� ����
			AddCastleTroopCount(castle, -1);
		}
	}
}
// �u�{�\���̕ρv��?
bool IsHonnojiEvent(Stage* stage)
{
	return stage->year == 1582
		&& GetCastleOwner(stage, CASTLE_NIJO) == LORD_ODA;
}
// �u�{�\���̕ρv�t���O�Z�b�g
void SetHonnojiEvent(Stage* stage)
{
	stage->isHonnojiEvent = true;
}
// �^�[�����s
void ExecTurn(Stage* stage, int turn)
{
	CastleId currentCastle = stage->turnOrder[turn];
	Castle* castle = GetCastle(stage, currentCastle);
	LordId owner = GetCastleOwner(castle);

	DrawScreen(stage, DM_Turn, turn);
	printTurnOrder(stage, turn);
	printf("%s���́@%s�́@�Ђ傤���傤���イ�c\n"
		, GetLordFamilyName(owner)
		, GetCastleName(stage, currentCastle)
	);
	putchar('\n');

	CastleId targetCastle;
	int sendTroopCount;
	Command cmd;
	if (owner == stage->playerLord) {
		cmd = InputPlayerTurn(stage, castle, &targetCastle, &sendTroopCount);
		ExecPlayerTurn(stage, currentCastle, cmd, targetCastle, sendTroopCount);
	}
	else {
		cmd = InputNpcTurn(stage, castle, &targetCastle, &sendTroopCount);
		ExecNpcTurn(stage, currentCastle, cmd, targetCastle, sendTroopCount);
	}
}
// �v���[���^�[�������s
static void ExecPlayerTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount)
{
	Castle* castle = GetCastle(stage, currentCastle);
	switch (cmd) {
	case CMD_Cancel:
		printf("���񂮂���@�Ƃ��߂܂���\n");
		WaitKey();
		break;
	case CMD_Transit:
		TransitTroop(stage, castle, targetCastle, sendTroopCount);
		printf("%s�Ɂ@%d�ɂ�@���ǂ��@���܂���"
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		break;

	case CMD_Attack:
		printf("%s�Ɂ@%d�ɂ�Ł@������񂶂�`�I�I\n"
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		AttackTroop(stage, castle, targetCastle, sendTroopCount);
		break;
	}
}
// NPC�^�[�������s
static void ExecNpcTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount)
{
	Castle* castle = GetCastle(stage, currentCastle);
	LordId owner = GetCastleOwner(stage, currentCastle);
	switch (cmd) {
	case CMD_Cancel:
		//printf("���񂮂���@�Ƃ��߂܂���\n");
		//WaitKey();
		break;
	case CMD_Transit:
		TransitTroop(stage, castle, targetCastle, sendTroopCount);
		printf("%s����@%s�Ɂ@%d�ɂ�@���ǂ��@���܂���\n"
			, GetCastleName(stage, currentCastle)
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		break;

	case CMD_Attack:
		printf("%s�́@%s%s���@%s�Ɂ@���߂��݂܂����I\n"
			, GetCastleName(stage, currentCastle)
			, GetLordFamilyName(stage, owner)
			, GetLordFirstName(stage, owner)
			, GetCastleName(stage, targetCastle)
		);
		WaitKey();
		AttackTroop(stage, castle, targetCastle, sendTroopCount);
		break;
	}
}
// �ڑ�����
static void TransitTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount)
{
	AddCastleTroopCount(castle, -sendTroopCount);
	Castle* target = GetCastle(stage, targetCastle);
	AddCastleTroopCount(target, sendTroopCount);
}
// �h��(�U��)����
static void AttackTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount)
{
	AddCastleTroopCount(castle, -sendTroopCount);
	LordId offenseLord = GetCastleOwner(castle);
	SiegeBattle(stage, offenseLord, sendTroopCount, targetCastle);
}
// �v���[���̕���?
bool IsPlayerLose(Stage* stage)
{
	// �v���[���̏邪�����Ȃ����畉��!!
	return getCastleCount(stage, stage->playerLord) == 0;
}
// �v���[���̏���?
bool IsPlayerWin(Stage* stage)
{
	// �v���[���̏�Ŗ��܂����珟��
	return getCastleCount(stage, stage->playerLord) == stage->castlesSize;
}
// �^�[�����Ԃ��v�����g
static void printTurnOrder(Stage* stage, int turn)
{
	for (int i = 0; i < stage->castlesSize; i++) {
		const char* cur = (i == turn) ? "��" : "�@";
		CastleId id = (CastleId)stage->turnOrder[i];
		printf("%s%s", cur, GetCastleMapName(stage, id));
	}
	putchar('\n');
	putchar('\n');
}
// ��͐퓬���s��
static void SiegeBattle(Stage* stage, LordId offenseLord, int offenseTroopCount, CastleId defenseCastle)
{
	ClearScreen();
	printf("�` %s�́@���������`\n", GetCastleName(stage, defenseCastle));
	putchar('\n');
	LordId defenseLord = GetCastleOwner(stage, defenseCastle);
	int defenseTroopCount = GetCastleTroopCount(stage, defenseCastle);

	while (true) {
		printf("%s����i%4d�ɂ�j�@�w�@%s����i%4d�ɂ�j\n"
			, GetLordFamilyName(offenseLord)
			, offenseTroopCount * TROOP_UNIT
			, GetLordFamilyName(defenseLord)
			, defenseTroopCount * TROOP_UNIT
		);
		WaitKey();
		if (offenseTroopCount <= 0 || defenseTroopCount <= 0) {
			break;
		}

		int rnd = GetRand(3);
		if (rnd == 0) {
			defenseTroopCount--;
			SetCastleTroopCount(stage, defenseCastle, defenseTroopCount);
		}
		else {
			offenseTroopCount--;
		}
	}
	putchar('\n');

	if (defenseTroopCount <= 0) {
		// �h�䑤�̕���
		SetCastleOwner(stage, defenseCastle, offenseLord);
		SetCastleTroopCount(stage, defenseCastle, offenseTroopCount);

		printf("%s�@�炭���傤�I�I\n"
			, GetCastleName(stage, defenseCastle)
		);
		putchar('\n');

		printf("%s�́@ %s���́@���̂ƂȂ�܂�\n"
			, GetCastleName(stage, defenseCastle)
			, GetLordFamilyName(offenseLord)
		);
		WaitKey();

		if (getCastleCount(stage, defenseLord) <= 0) {
			RecordChronology(stage->chro
				, "%d�˂�@%s%s���@%s�Ł@%s%s���@�ق�ڂ�\n"
				, stage->year
				, GetLordFamilyName(stage, offenseLord)
				, GetLordFirstName(stage, offenseLord)
				, GetCastleName(stage, defenseCastle)
				, GetLordFamilyName(stage, defenseLord)
				, GetLordFirstName(stage, defenseLord)
			);
		}
	}
	else {
		// �U�����̕���
		printf("%s����@�����߂I�I\n"
			, GetLordFamilyName(stage, offenseLord)
		);
		putchar('\n');
		printf("%s���񂪁@%s���@�܂��肫��܂����I\n"
			, GetLordFamilyName(stage, defenseLord)
			, GetCastleName(stage, defenseCastle)
		);
		WaitKey();
	}
}
// �C�ӂ�owner�̏�𐔂���
static int getCastleCount(Stage* stage, LordId lord)
{
	// ���������R�[�f�B���O���Ă�������
	// stage->castles[] �𑖍����āA
	// owner ��lord �ł�����̂��J�E���g���܂�
	int castleCount = 0;
	for (int i = 0; i < stage->castlesSize; i++)
	{
		LordId owner = GetCastleOwner(stage, (CastleId)i);
		if (owner == lord)
		{
			castleCount++;
		}
	}
	return castleCount;
}
//---------------------------------------------------------
// ��̖��O�𓾂�
const char* GetCastleName(Stage* stage, CastleId id)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// GetCastleName()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	return GetCastleName(castle);
}
// ��̏����擾
LordId GetCastleOwner(Stage* stage, CastleId id)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// GetCastleOwner()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	return GetCastleOwner(castle);
}
// ��̏����Z�b�g
void SetCastleOwner(Stage* stage, CastleId id, LordId owner)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// SetCastleOwner()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	 SetCastleOwner(castle,owner);
	
}
// �����𓾂�
int GetCastleTroopCount(Stage* stage, CastleId id)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// GetCastleTroopCount()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	return GetCastleTroopCount(castle);
}
// �������Z�b�g
void SetCastleTroopCount(Stage* stage, CastleId id, int troopCount)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// SetCastleTroopCount()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	SetCastleTroopCount(castle,troopCount);
	
}
// ��̋ߗ׃��X�g���擾
CastleId* GetCastleConnectedList(Stage* stage, CastleId id)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// SetCastleConnectedList()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	return GetCastleConnectedList(castle);
}
// ��̃}�b�v�����擾
const char* GetCastleMapName(Stage* stage, CastleId id)
{
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���� 
	// GetCastleMapName()���Ăт܂�
	Castle* castle = GetCastle(stage, id);
	return GetCastleMapName(castle);
}
// id���� Castle* ���擾
static Castle* GetCastle(Stage* stage, CastleId id)
{
	assert(0 <= id && id < stage->castlesSize);
	// ���������R�[�f�B���O���Ă��������B
	// id => Castle�|�C���^�[�擾���܂� 
	assert(0 <= id && id < stage->castlesSize);
	return &stage->castles[id];
}
//--------------------------------------
// ���̖����擾
const char* GetLordFirstName(Stage* stage, LordId id)
{
	// ���������R�[�f�B���O���Ă�������
	// chnageLordId()�� id �ύX������A
	// GetLordFirstName()���Ăт܂�
	id = changeLordId(stage, id);
	return GetLordFirstName(id);
}
// ���̐����擾
const char* GetLordFamilyName(Stage* stage, LordId id)
{
	// ���������R�[�f�B���O���Ă�������
	// chnageLordId()�� id �ύX������A
	// GetLordFamilyName()���Ăт܂�
	id = changeLordId(stage, id);
	return GetLordFamilyName(id);
}
// ���̃}�b�v��̖��O���擾
const char* GetLordMapName(Stage* stage, LordId id)
{
	// ���������R�[�f�B���O���Ă�������
	// chnageLordId()�� id �ύX������A
	// GetLordMapName()���Ăт܂�
	id = changeLordId(stage, id);
	return GetLordMapName(id);
}
// ���ID�̕ύX
static LordId changeLordId(Stage* stage, LordId id)
{
	// �u�{�\���̕ρv��́A�D�c�M��=>�H�ďG�g
	// ���������R�[�f�B���O���Ă��������B
	// isHonnojiEvent�������Ă����� �D�c�M����id�Ȃ�>�H�ďG�g�ɕς��Ă�������
	if (id == LORD_ODA && stage->isHonnojiEvent)
	{
		id = LORD_HASHIBA;
	}
	return id;
}