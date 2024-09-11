#pragma once
//======================================
//	�퍑�V�~�����[�V����  �X�e�[�W
//======================================
#ifndef __STAGE_H
#define __STAGE_H

#include "Castle.h"
#include "Lord.h"
#include "Chronology.h"

typedef enum {
	DM_Intro,    // �Q�[���J�n��
	DM_Turn,     // �^�[����
	DM_Event,    // �C�x���g������
	DM_GameOver, // �Q�[���I�[�o��
	DM_Ending,   // �G���f�B���O��
} DrawMode;

typedef struct {
	Castle* castles;
	int castlesSize;
	int year;             // �N
	LordId playerLord;    // �v���[���喼
	Chronology* chro;     // �N�\
	CastleId turnOrder[CASTLE_MAX];
	bool isHonnojiEvent;  // �{�\���̕ς�������?
} Stage;

// ������
void InitializeStage(Stage* stage, Castle chasles[], int castlesSize, int startYear, Chronology* chro);
// ��n��
void FinalizeStage(Stage* stage);
// �X�^�[�g
void StartStage(Stage* stage);
// �v���[���喼�̃Z�b�g
void SetPlayerLord(Stage* stage, CastleId playerCastle);
// �C���g�����b�Z�[�W
void IntroStage(Stage* stage, CastleId playerCastle);
// �X�N���[���`��
void DrawScreen(Stage* stage, DrawMode mode, int turn);
// �^�[���̏��Ԃ��V���b�t��
void MakeTurnOrder(Stage* stage);
// �N�z��
void NextYear(Stage* stage);
// �u�{�\���̕ρv��?
bool IsHonnojiEvent(Stage* stage);
// �u�{�\���̕ρv�t���O�Z�b�g
void SetHonnojiEvent(Stage* stage);
// �^�[�����s
void ExecTurn(Stage* stage, int turn);
// �v���[���̕���?
bool IsPlayerLose(Stage* stage);
// �v���[���̏���?
bool IsPlayerWin(Stage* stage);
//---------------------------------------------------------
// ��̖��O���擾
const char* GetCastleName(Stage* stage, CastleId castleId);
// ��̏����擾
LordId GetCastleOwner(Stage* stage, CastleId castleId);
// ��̏���ݒ�
void SetCastleOwner(Stage* stage, CastleId id, LordId owner);
// ��̕������擾
int GetCastleTroopCount(Stage* stage, CastleId id);
// �������Z�b�g
void SetCastleTroopCount(Stage* stage, CastleId id, int troopCount);
// ��̋ߗ׃��X�g���擾
CastleId* GetCastleConnectedList(Stage* stage, CastleId id);
// ��̃}�b�v�����擾
const char* GetCastleMapName(Stage* stage, CastleId id);
//---------------------------------------------------------
// ���̖����擾
const char* GetLordFirstName(Stage* stage, LordId id);
// ���̐����擾
const char* GetLordFamilyName(Stage* stage, LordId id);
// ���̃}�b�v��̖��O���擾
const char* GetLordMapName(Stage* stage, LordId id);

#endif // __STAGE_H