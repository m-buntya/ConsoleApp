//======================================
//	2D�x�N�^�[
//======================================
#ifndef __VECTOR2_H
#define __VECTOR2_H

typedef struct {
	int x;
	int y;
} Vector2;

// �x�N�^�[���Z
void AddVector2(Vector2* a, Vector2* b);

// 2D�x�N�^�[�̉��Z
Vector2 Vector2Add(Vector2 a, Vector2 b);
// 2D�x�N�^�[�̌��Z
Vector2 Vector2Sub(Vector2 a, Vector2 b);
// 2D�x�N�^�[�̓���?
bool Vector2Equ(Vector2 a, Vector2 b);
// �x�b�N�[�Z�b�g
void SetVector2(Vector2* vec, int x, int y);

#endif // __VECTOR2_H