#pragma once
//======================================
//	2D�x�N�^�[
//======================================
// �������ɃC���N���[�h�J�[�h(�J�n)���L�����Ă�������
#ifndef __VECTOR2_H
#define __VECTOR2_H


typedef struct {
	int x;
	int y;
} Vector2;

// �S����
typedef enum {
	DIR_UP,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_MAX,
} DIRECTION;

// �x�N�^�[���Z
void AddVector2(Vector2* a, Vector2* b);
// �S�����̃x�N�^�[�擾
Vector2 GetDirVector2(DIRECTION d);
// 2D�x�N�^�[�̉��Z
Vector2 Vector2Add(Vector2 a, Vector2 b);
// 2D�x�N�^�[�̌��Z
Vector2 Vector2Sub(Vector2 a, Vector2 b);
// 2D�x�N�^�[�̓���?
bool Vector2Equ(Vector2 a, Vector2 b);
#endif // !__VECTOR2_H

// �������ɃC���N���[�h�J�[�h(�I��)���L�����Ă�������