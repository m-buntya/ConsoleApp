#pragma once
//======================================
//	�h�b�g�C�[�g�Q�[���@Stage
//======================================
// �������ɃC���N���[�h�J�[�h(�J�n)���L�����Ă�������
#ifndef __STAGE_H
#define __STAGE_H

#include "Character.h"
#include "Vector2List.h"

typedef enum {
	MAZE_NONE = ' ',   // ��
	MAZE_WALL = '#',   // ��
	MAZE_DOT = 'o',    // �h�b�g
	MAZE_PLAYER = CHARA_PLAYER, // �v���[��
	MAZE_RANDOM = CHARA_RANDOM, // �C�܂��ꃂ���X�^�[
	MAZE_CHASE = CHARA_CHASE,  // �ǂ����������X�^�[
	MAZE_AMBUSH = CHARA_AMBUSH, // ���胂���X�^�[
	MAZE_SIEGE = CHARA_SIEGE,  // ���݌��������X�^�[
} Maze;

const int MAZE_HEIGHT = 19;
const int MAZE_WIDTH = 19;
const int MONSTER_SIZE = 4;
const int V2LIST_SIZE = 20;

typedef struct {
	char maze[MAZE_HEIGHT][MAZE_WIDTH + 1];
	Character* player;
	Character* monster[MONSTER_SIZE];
	int monsterNum;
	// GetChasePosition() ���[�N
	Vector2List v2list;
	Vector2List v2temp;
	int distance[MAZE_HEIGHT][MAZE_WIDTH];
	Character* chaser;
} Stage;

// �X�e�[�W������
void InitializeStage(Stage* stage, Character* player);
// �X�e�[�W��n��
void FinalizeStage(Stage* stage);
// �����X�^�[�o�^
void RegistMonster(Stage* stage, Character* monster);
// Maze�`��
void DrawMaze(Stage* stage);
// �Q�[���I�[�o?
bool IsGameOver(Stage* stage);
// �Q�[���N���A?
bool IsComplete(Stage* stage);
// Maze�[�̃��[�v����
Vector2 GetLoopPosition(Vector2 pos);
// Maze���̈ʒu��?
bool IsInMaze(int x, int y);
// Maze(x,y)�擾
char GetMaze(Stage* stage, int x, int y);
// Maze(x,y)�Z�b�g
void SetMaze(Stage* stage, int x, int y, char c);

#endif // �������ɃC���N���[�h�J�[�h(�I��)���L�����Ă�������