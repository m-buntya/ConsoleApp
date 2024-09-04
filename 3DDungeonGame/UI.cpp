//======================================
//	3D�_���W���� UI
//======================================
#include "Stage.h"
#include "Character.h"
#include "Utility.h"
#include <stdio.h>
// �֐��v���g�^�C�v
void MovePlayerForMap(Stage* stage, Key c);
void MovePlayerFor3D(Stage* stage, Key c);

bool MovePlayer(Stage* stage)
{
	Key c = GetKey();
	if (c == SPACE) {
		// stage->isForMap�t���O�𔽓]�����Ă�������
		// ���������R�[�f�B���O���Ă��������B
		stage->isForMap = !stage->isForMap;
	}
	else if (c == ESC) {
		return true;
	}
	else {
		if (stage->isForMap) {
			MovePlayerForMap(stage, c);
		}
		else {
			MovePlayerFor3D(stage, c);
		}
	}
	return false;
}
// ����@��`��
void DrawOperation(Stage* stage)
{
	puts("SPACE: change UI");
	puts("ESC : exit Game");
	if (stage->isForMap) {
		puts("��:�k�֌���/�k�֑O�i");
		puts("��:���֌���/���֑O�i");
		puts("��:���֌���/���֑O�i");
		puts("��:��֌���/��֑O�i");
	}
	else {
		puts("��:�O�ɐi��");
		puts("��:��������");
		puts("��:�E������");
		puts("��:��������");
	}
}

// �v���[���ړ�(ForMap)
void MovePlayerForMap(Stage* stage, Key c)
{
	Character* player = &stage->player;
	Direction d = DIR_MAX;
	switch (c) {
	case ARROW_UP:    d = DIR_NORTH; break;
	case ARROW_DOWN:  d = DIR_SOUTH; break;
	case ARROW_LEFT:  d = DIR_WEST; break;
	case ARROW_RIGHT: d = DIR_EAST; break;
		if (d < DIR_MAX) {
			if (player->dir != d) {
				player->dir = d;
			}
			else {
				if (GetMazeWall(stage, player->pos, player->dir) == false) {
					Vector2 dir = GetDirVector2(d);
					Vector2 newPos = Vector2Add(player->pos, dir);
					if (IsInsideMaze(newPos)) {
						player->pos = newPos;
					}
				}
			}
		}
	}
}
	// �v���[���ړ�(For3D)
	void MovePlayerFor3D(Stage * stage, Key c)
	{
		Character* player = &stage->player;
		switch (c) {
		case ARROW_UP:  // �O�i
		
			if (GetMazeWall(stage, player->pos, player->dir) == false) {
				Vector2 dir = GetDirVector2(player->dir);
				Vector2 newPos = Vector2Add(player->pos, dir);
				if (IsInsideMaze(newPos)) {
					player->pos = newPos;
				}
			}
			break;
		case ARROW_DOWN: // ��������
			// ���������R�[�f�B���O���Ă�������
			// Character�̊֐��𗘗p���܂�
			TurnBackCharacter(player);
			break;
		case ARROW_LEFT: // ��������
			// ���������R�[�f�B���O���Ă�������
			// Character�̊֐��𗘗p���܂�
			TurnLeftCharacter(player);
			break;
		case ARROW_RIGHT: // �E������
			// ���������R�[�f�B���O���Ă�������
			// Character�̊֐��𗘗p���܂�
			TurnRightCharacter(player);
			break;
		}
	}
