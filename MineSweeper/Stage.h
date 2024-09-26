#pragma once
//======================================
//	�}�C���X�B�[�p�[ �X�e�[�W
//======================================
#ifndef __STAGE_H
#define __STAGE_H

#include "Cell.h"

const int FIELD_WIDTH = 9;
const int FIELD_HEIGHT = 9;
// �{���̐ݒu��
const int BOMB_COUNT = 10;

typedef struct {
	Cell field[FIELD_HEIGHT][FIELD_WIDTH];
	int cursorX; // �J�[�\�����W
	int cursorY;
	bool isExplosion; // ��������!!
	bool isClear;  // �N���A����!!
} Stage;

// �X�e�[�W�̏�����
void InitializeStage(Stage* stage);
// �X�N���[���`��
void DrawScreen(Stage* stage);
// �אڃ{���̐����擾
int GetAdjacentBombsCount(Stage* stage, int x, int y);
// �����@�肷����
void AutoEraseMines(Stage* stage, int x, int y);
// �J�[�\���̃Z����flag�𔽓].
void FlipCursorFlag(Stage* stage);
// �J�[�\���̃Z�����J��(�I���t���O��Ԃ�)
bool OpenCursorCell(Stage* stage);
// �J�[�\���ړ�
void MoveCursor(Stage* stage, int addX, int addY);
// �t�B�[���h�̃Z�����擾����
Cell* GetFieldCell(Stage* stage, int x, int y);
// ������?
bool IsWin(Stage* stage);
// ������?
bool IsLose(Stage* stage);

#endif //  __STAGE_H
