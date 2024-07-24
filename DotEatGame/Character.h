#pragma once
//======================================
//	�h�b�g�C�[�g�Q�[���@Character
//======================================
#ifndef __CHARACTER_H
#define __CHARACTER_H
// �������ɃC���N���[�h�J�[�h(�J�n)���L�����Ă�������


#include "Vector2.h"

typedef enum {
	CHARA_PLAYER, // �v���[��
	CHARA_RANDOM, // �C�܂��ꃂ���X�^�[
	CHARA_CHASE,  // �ǂ����������X�^�[
	CHARA_AMBUSH, // ���胂���X�^�[
	CHARA_SIEGE,  // ���݌��������X�^�[
} Chara;

typedef struct {
	Chara    id;      // �N?
	Vector2  pos;     // ���W
	Vector2  lastPos; // �O��̍��W
} Character;

// �L�����N�^�[������
void InitCharacter(Character* ch, Chara id, Vector2 initPos);
// �L�����N�^�[�ړ�
void MoveCharacter(Character* ch, Vector2 pos);
// �L�����N�^�[�̌����x�N�^�[���擾����
Vector2 GetCharacterDir(Character* ch);

#endif // !__CHARACTER_H
// �������ɃC���N���[�h�J�[�h(�I��)���L�����Ă�������