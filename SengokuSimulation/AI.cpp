//======================================
//	�퍑�V�~�����[�V����  AI
//======================================
#include "AI.h"
#include "IntList.h"
#include "Troop.h"  // TROOP_XXXX
#include "CastleId.h"
#include "Utility.h"  // GetRand()

// �֐��v���g�^�C�v
static CastleId getMinTroopCastle(IntList* intList, Stage* stage);
static bool isFrontCastle(Stage* stage, CastleId caseltId);
static int cmpCastleByTroop(int a, int b);

static Stage* s_stage;

// NPC�^�[���̓���(�v�l)
Command InputNpcTurn(Stage* stage, Castle* castle, CastleId* outTarget, int* outTroopCount)
{
	LordId npcLord = GetCastleOwner(castle);
	int npcTroopCount = GetCastleTroopCount(castle);
	Command cmd = CMD_Cancel;

	IntList enemyCastleList[1];
	InitializeIntList(enemyCastleList, CASTLE_MAX);

	// �אڂ���G�̏�����X�e�B���O
	CastleId* connectedList = GetCastleConnectedList(castle);
	for (int i = 0; ; i++) {
		CastleId id = connectedList[i];
		if (id == CASTLE_NONE) break;
		if (GetCastleOwner(stage, id) != npcLord) {
			AddIntList(enemyCastleList, id);
		}
	}
	if (GetCountIntList(enemyCastleList) > 0) {
		// TroopCount�ŏ��̏���擾
		CastleId targetCastle = getMinTroopCastle(enemyCastleList, stage);

		// �U�ߍ��ޏ����`�F�b�N
		//  �E������̕��͕͂W���l�ȏ�ł��邩?
		//  �E������̕��͂�����������������đ����2�{�ȏォ?
		int tgtTroopCount = GetCastleTroopCount(stage, targetCastle);
		if (npcTroopCount >= TROOP_BASE
			|| npcTroopCount - 1 >= tgtTroopCount * 2) {

			int troopCount = npcTroopCount - 1;
			if (troopCount < 0) {
				troopCount = 0;
			}

			*outTarget = targetCastle;
			*outTroopCount = troopCount;
			cmd = CMD_Attack;
		}
	}
	else {
		// �אڂ���G�����Ȃ�
		IntList cnnctCastleList[1];
		IntList frontCastleList[1];
		InitializeIntList(cnnctCastleList, CASTLE_MAX);
		InitializeIntList(frontCastleList, CASTLE_MAX);
		// �O���̏�����X�e�B���O
		for (int i = 0; ; i++) {
			CastleId id = connectedList[i];
			if (id == CASTLE_NONE) break;
			if (isFrontCastle(stage, id)) {
				AddIntList(frontCastleList, id);
			}
			AddIntList(cnnctCastleList, id);
		}

		CastleId targetCastle;
		int sendTroopCount;
		if (GetCountIntList(frontCastleList) > 0) {
			targetCastle = getMinTroopCastle(frontCastleList, stage);
			sendTroopCount = TROOP_MAX - GetCastleTroopCount(stage, targetCastle);
			if (sendTroopCount > npcTroopCount) {
				// �O���̏�ɑ���Ȃ�A�S��
				sendTroopCount = npcTroopCount;
			}
		}
		else {
			targetCastle = getMinTroopCastle(cnnctCastleList, stage);
			sendTroopCount = TROOP_MAX - GetCastleTroopCount(stage, targetCastle);
			int tmp = npcTroopCount - (TROOP_BASE - 1);
			if (sendTroopCount > tmp) {
				// �O���łȂ��Ȃ�ABASE-1 ���c���āA������傫������
				sendTroopCount = tmp;
			}
		}
		if (sendTroopCount > 0) {
			*outTarget = targetCastle;
			*outTroopCount = sendTroopCount;
			cmd = CMD_Transit;
		}
		FinalizeIntList(cnnctCastleList);
		FinalizeIntList(frontCastleList);
	}
	FinalizeIntList(enemyCastleList);

	return cmd;
}
// CastleId���X�g���� Troop�ŏ����擾����
static CastleId getMinTroopCastle(IntList* intList, Stage* stage)
{
	// TroopCount�̏��������Ƀ\�[�g
	s_stage = stage;
	SortIntList(intList, cmpCastleByTroop);
	// TroopCount�ŏ��̐�����������
	int* array = GetArrayIntList(intList);
	int  count = GetCountIntList(intList);
	int minTroopCount = GetCastleTroopCount(stage, (CastleId)array[0]);
	int i = 1;
	for (; i < count; i++) {
		if (minTroopCount < GetCastleTroopCount(stage, (CastleId)array[i])) {
			break;
		}
	}
	// TroopCount�ŏ��̒����烉���_���ɑI��
	int idx = GetRand(i);
	return (CastleId)array[idx];
}
// �O���̏邩?
static bool isFrontCastle(Stage* stage, CastleId castleId)
{
	// �אڂɓG������ΑO���̏�ł���
	CastleId* connectedList = GetCastleConnectedList(stage, castleId);
	LordId owner = GetCastleOwner(stage, castleId);
	for (int i = 0; ; i++) {
		CastleId id = connectedList[i];
		if (id == CASTLE_NONE) break;
		if (GetCastleOwner(stage, id) != owner) {
			return true;
		}
	}
	return false;
}
// �\�[�g�̂��߂̔�r�֐�
static int cmpCastleByTroop(int a, int b)
{
	int troop_a = GetCastleTroopCount(s_stage, (CastleId)a);
	int troop_b = GetCastleTroopCount(s_stage, (CastleId)b);
	return troop_a - troop_b;
}