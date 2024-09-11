//====================================
//	3D�_���W����  �L�����N�^
//======================================
#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "Vector2.h"
#include "Direction.h"

typedef struct {
	Vector2 pos;      // ���W
	Direction dir;    // �����Ă������
} Character;

// �L����������
void InitCharacter(Character* ch, Vector2 pos, Direction dir);
// ��������
void TurnBackCharacter(Character* ch);
// ��������
void TurnLeftCharacter(Character* ch);
// �E������
void TurnRightCharacter(Character* ch);

#endif __CHARACTER_H
