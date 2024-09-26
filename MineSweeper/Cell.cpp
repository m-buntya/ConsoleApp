//======================================
//	�}�C���X�B�[�p�[ �Z��
//======================================
#include "Cell.h"
// �Z�b�g�t�b�v(������)��Ԃɂ���
void SetupCell(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��bomb�� false �ɃZ�b�g���܂�
	// cell��hide�� true �ɃZ�b�g���܂�
	// cell��flag�� false �ɃZ�b�g���܂�
	// cell��adjacentBombs�� 0 �ɃZ�b�g���܂�
	cell->bomb = false;
	cell->hide = true;
	cell->flag = false;
	cell->adjacentBombs = 0;
}
// bomb��?
bool IsBomb(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��bomb��Ԃ��܂�
	return cell->bomb;
}
// bomb ���Z�b�g
void SetBomb(Cell* cell, bool value)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��bomb��value�������܂�
	cell->bomb = value;
}
// hide��?
bool IsHide(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��hide��Ԃ��܂�
	return cell->hide;
}
// hide ���Z�b�g
void SetHide(Cell* cell, bool value)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��hide��value�������܂�
	cell->hide = value;
}
// flag��?
bool IsFlag(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��flag��Ԃ��܂�
	return cell->flag;
}
// flag �𔽓]
void FlipFlag(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��flag�𔽓]���܂�
	cell->flag = !cell->flag;
}
// adjacentBombs���擾
int GetAdjacentBombs(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��adjacentBombs��Ԃ��܂�
	return cell->adjacentBombs;
}
// adjacentBombs���Z�b�g
void SetAdjacentBombs(Cell* cell, int value)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��adjacentBombs��value�������܂�
	cell->adjacentBombs = value;
}
// �J������
void OpenCell(Cell* cell)
{
	// ���������R�[�f�B���O���Ă�������
	// cell��hide��false�����܂�
	// cell��flag��false�����܂�
	cell->hide = false;
	cell->flag = false;
}