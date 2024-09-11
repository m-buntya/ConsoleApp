#pragma once
//======================================
//	3D�_���W���� �f�B���N�V����(����)
//======================================
#ifndef __DIRECTION_H
#define __DIRECTION_H
#include "Vector2.h"

// �S����
// �}�b�v��ł́u�k���쓌�v�̈Ӗ�����
// �v���[������u�O����E�v�̈Ӗ��ɂ��g����
typedef enum {
	DIR_NORTH,  // �k(�O��)
	DIR_WEST,   // ��(����)
	DIR_SOUTH,  // ��(���)
	DIR_EAST,   // ��(�E��)
	DIR_MAX,
} Direction;

// �S�����̃x�N�^�[�擾
Vector2 GetDirVector2(Direction d);
// �f�B���N�V�����̉��Z
Direction DirectionAdd(Direction dir, int add);
// �f�B���N�V�����͈̓`�F�b�N
bool IsInDirection(Direction d);

#endif // __DIRECTION_H
