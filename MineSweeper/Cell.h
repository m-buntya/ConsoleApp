#pragma once
//======================================
//	�}�C���X�B�[�p�[ �Z��
//======================================
#ifndef __CELL_H
#define __CELL_H

typedef struct {
	bool bomb;          // �{�����u���Ă���
	bool hide;          // ���J��
	bool flag;          // �v���[���������t���O
	int adjacentBombs;  // �אڃ{���̐�
} Cell;

// Cell��������
void SetupCell(Cell* cell);
// bomb��?
bool IsBomb(Cell* cell);
// bomb���Z�b�g
void SetBomb(Cell* cell, bool value);
// mine ��?
bool IsHide(Cell* cell);
// mine���Z�b�g
void SetHide(Cell* cell, bool value);
// mine ��?
bool IsFlag(Cell* cell);
// mine���Z�b�g
void FlipFlag(Cell* cell);
// adjacentBombs���擾
int GetAdjacentBombs(Cell* cell);
// adjacentBombs���Z�b�g
void SetAdjacentBombs(Cell* cell, int value);
// �J������
void OpenCell(Cell* cell);

#endif //  __CELL_H