//======================================
//	�^�[�����o�g��
//======================================
#include "TurnBattle.h"
#include "Utility.h"
#include <stdio.h>  // printf()

// �֐��v���g�^�C�v
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense);

// �^�[���o�g���ݒ�
void SetTurnBattle(TurnBattle* btl, Character* player, Character* enemy)
{
	btl->player = player;
	btl->enemy = enemy;
}
// �C���g���u�`�����ꂽ!!�v�\��
void IntroTurnBattle(TurnBattle* btl)
{
	DrawBattleScreen(btl);
	printf("%s���@�����ꂽ!!\n", GetName(btl->enemy));
	WaitKey();
}
// �o�g���J�n
void StartTurnBattle(TurnBattle* btl)
{
	btl->turn = 1;
	StartCharacter(btl->player);
	StartCharacter(btl->enemy);
}
// �o�g����ʂ�`��
void DrawBattleScreen(TurnBattle* btl)
{
	ClearScreen();
	IndicatePlayer(btl->player);
	putchar('\n');
	IndicateEnemy(btl->enemy);
	putchar('\n');
}
// �v���[���̃^�[�����s
bool ExecPlayerTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->player, btl->enemy);
	if (IsDeadCharacter(btl->enemy)) {
		SetEraseAa(btl->enemy);
		DrawBattleScreen(btl);
		printf("%s���@��������!\n", GetName(btl->enemy));
		WaitKey();
		return true;
	}
	return IsEscapeCharacter(btl->player);
}
// �G�̃^�[�����s
bool ExecEnemyTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->enemy, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		printf("���Ȃ��́@���ɂ܂���\n");
		WaitKey();
		return true;
	}
	return false;
}
// �R�}���h���s(offense:�U���L���� defense:�h��L����)
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense)
{
	int dmg;
	switch (cmd) {
	case COMMAND_FIGHT:
		DrawBattleScreen(btl);
		printf("%s�́@��������!\n", GetName(offense));
		WaitKey();

		dmg = CalcDamage(offense);
		DamageCharacter(defense, dmg);
		DrawBattleScreen(btl);
		printf("%s�� %d�́@�_���[�W!\n", GetName(defense), dmg);
		WaitKey();

		break;
	case COMMAND_SPELL:
		if (CanSpellCharacter(offense) == false) {
			DrawBattleScreen(btl);
			printf("�l�o���@����Ȃ�!\n");
			WaitKey();
			break;
		}
		UseSpellCharacter(offense);
		DrawBattleScreen(btl);
		printf("%s�́@�q�[�����@�ƂȂ���!\n", GetName(offense));
		WaitKey();

		RecoverCharacter(offense);
		DrawBattleScreen(btl);
		printf("%s�̂������@�����ӂ�����!\n", GetName(offense));
		WaitKey();
		break;

	case COMMAND_ESCAPE:
		DrawBattleScreen(btl);
		printf("%s�́@�ɂ�������!\n", GetName(offense));
		WaitKey();
		SetEscapeCharacter(offense);
		break;
	}
}
// ���̃^�[����
void NextTurnBattle(TurnBattle* btl)
{
	btl->turn++;
}