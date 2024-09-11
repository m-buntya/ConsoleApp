#pragma once
//======================================
//	�X�e�[�W
//======================================
#ifndef __STAGE_H
#define __STAGE_H
#include "Map.h"
#include "Character.h"

const int ZAKO_SIZE = 10;

typedef struct {
	MapSpec* mapSpec;
	int playerX;
	int playerY;
	Character* player;
	Character* boss;
	Character* zako[ZAKO_SIZE];
	int zakoPtr;
} Stage;

// ������
void InitializeStage(Stage* stage, Character* player, Character* boss);
// �U�R�G��o�^
void RegistZako(Stage* stage, Character* zako);
// �}�b�v�ύX
void ChangeMap(Stage* stage, NextMap* next);
// �X�^�[�g�}�b�v�ɃG���g���[
void ChangeStartMap(Stage* stage);
// �}�b�v�`��
void DrawMap(Stage* stage);
// �U�R�o�g�����s
void BattleZako(Stage* stage);
// �{�X�o�g�����s
void BattleBoss(Stage* stage);
// �}�b�v�X�y�b�N�擾
MapSpec* GetMapSpec(Stage* stage);
// �v���[��X���W���擾
int GetPlayerX(Stage* stage);
// �v���[��Y���W���擾
int GetPlayerY(Stage* stage);
// �v���[�����W���Z�b�g
void SetPlayerPosition(Stage* stage, int playerX, int playerY);
// �v���[�����S?
bool IsPlayerDead(Stage* stage);
// �{�X���S?
bool IsBossDead(Stage* stage);

#endif //  __STAGE_H