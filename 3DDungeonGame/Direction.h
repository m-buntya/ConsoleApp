//======================================
//	3D�_���W���� �f�B���N�V����(����)
//======================================
#include "Direction.h"
#include <assert.h>

// �S�����̃x�N�^�[�擾
Vector2 GetDirVector2(Direction d)
{
	static Vector2 dirVector2[] = {
		{ 0,-1},  //DIR_NORTH
		{-1, 0},  //DIR_WEST
		{ 0, 1},  //DIR_SOUTH,
		{ 1, 0},  //DIR_EAST,
	};
	assert(0 <= d && d < DIR_MAX);
	return dirVector2[d];
}

// �f�B���N�V�������Z
Direction DirectionAdd(Direction dir, int add)
{
	// dir �� add(1,2,-1)�����Z�������ƁA
	// 0 �` DIR_MAX-1 �͈͓̔��Ɏ��߂܂�
	// ���������R�[�f�B���O���Ă�������
	//
}
// �f�B���N�V�����͈̓`�F�b�N
bool IsInDirection(Direction d)
{
	// d�� 0 �` DIR_MAX-1 �����ׂ܂�
	// ���������R�[�f�B���O���Ă�������
}
