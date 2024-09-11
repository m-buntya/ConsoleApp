//======================================
//	�L�����N�^�[
//======================================
#include "Character.h"
#include "Utility.h" // GetRand()
#include <string.h>  // strcpy()
#include <stdio.h>   // printf()
#include <stdlib.h>  // rand(), RAND_MAX

// �����̏���MP
static const int SPELL_COST = 3;

// �L�����N�^�[�Z�b�g
void SetCharacter(Character* ch, int hp, int mp, int attack, const char* name, const char* aa)
{
	ch->maxHp = hp;
	ch->maxMp = mp;
	ch->attack = attack;
	ch->name = name;
	ch->aa = aa;
}
// �L�����̐퓬�J�n
void StartCharacter(Character* ch)
{
	ch->hp = ch->maxHp;
	ch->mp = ch->maxMp;
	ch->isEscape = false;
	ch->isEraseAa = false;
}
// ���S��?
bool IsDeadCharacter(Character* ch)
{
	return ch->hp == 0;
}
// �_���[�W���󂯂�
void DamageCharacter(Character* ch, int damage)
{
	ch->hp -= damage;
	if (ch->hp < 0) {
		ch->hp = 0;
	}
}
// �񕜂���
void RecoverCharacter(Character* ch)
{
	ch->hp = ch->maxHp;
}
//  ���@���g���邩?
bool CanSpellCharacter(Character* ch)
{
	return ch->mp >= SPELL_COST;
}
// ���@���g��
void UseSpellCharacter(Character* ch)
{
	ch->mp -= SPELL_COST;
	if (ch->mp < 0) {
		ch->mp = 0;
	}
}
// �v���[���\�����s��
void IndicatePlayer(Character* ch)
{
	printf("%s\n", ch->name);
	printf("�g�o�F%3d�^%d�@�l�o�F%2d�^%d\n", ch->hp, ch->maxHp, ch->mp, ch->maxMp);
}
// �G�l�~�[�\�����s��
void IndicateEnemy(Character* ch)
{
	if (ch->isEraseAa == false) {
		printf("%s", ch->aa);
	}
	printf("�i�g�o�F%3d�^%d�j\n", ch->hp, ch->maxHp);
}
// �U���͂���^����_���[�W���v�Z
int CalcDamage(Character* ch)
{
	int dmg = GetRand(ch->attack) + 1;
	return dmg;
}
// ���O���擾
const char* GetName(Character* ch)
{
	return ch->name;
}
// �����o�������Z�b�g
void SetEscapeCharacter(Character* ch)
{
	ch->isEscape = true;
}
// �����o������?
bool IsEscapeCharacter(Character* ch)
{
	return ch->isEscape;
}
// �A�X�L�[�A�[�g�������Z�b�g
void SetEraseAa(Character* ch)
{
	ch->isEraseAa = true;
}
// �S�p�����[�^��
void RecoverAllStatus(Character* ch)
{
	ch->hp = ch->maxHp;
	ch->mp = ch->maxMp;
}