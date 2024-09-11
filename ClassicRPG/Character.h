#pragma once
//======================================
//	�L�����N�^�[
//======================================
#ifndef __CHARACTER_H
#define __CHARACTER_H

struct Character {
	int hp;     // HP
	int maxHp;  // �ő�HP
	int mp;     // MP
	int maxMp;  // �ő�MP
	int attack; // �U����
	const char* name; // ���O
	const char* aa;   // �A�X�L�[�A�[�g
	bool isEscape;    // �����o�����t���O
	bool isEraseAa;   // �A�X�L�[�A�[�g�������t���O
};
// �L�����N�^�[�Z�b�g
void SetCharacter(Character* ch, int hp, int mp, int attack, const char* name, const char* aa);
// �L�����̐퓬�J�n
void StartCharacter(Character* ch);
// ���S��?
bool IsDeadCharacter(Character* ch);
// �_���[�W���󂯂�
void DamageCharacter(Character* ch, int damage);
// �񕜂���
void RecoverCharacter(Character* ch);
//  ���@���g���邩?
bool CanSpellCharacter(Character* ch);
// ���@���g��
void UseSpellCharacter(Character* ch);
// �v���[���\�����s��
void IndicatePlayer(Character* ch);
// �G�l�~�[�\�����s��
void IndicateEnemy(Character* ch);
// �U���͂��瑊��ɗ^����_���[�W���v�Z
int CalcDamage(Character* ch);
// ���O���擾
const char* GetName(Character* ch);
// �����o�������Z�b�g
void SetEscapeCharacter(Character* ch);
// �����o������?
bool IsEscapeCharacter(Character* ch);
// AA����
void SetEraseAa(Character* ch);
// �S�p�����[�^��
void RecoverAllStatus(Character* ch);

#endif // __CHARATER_H