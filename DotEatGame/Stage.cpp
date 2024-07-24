//======================================
//	�h�b�g�C�[�g�Q�[���@Stage
//======================================
#include "Stage.h"
#include "Character.h"
#include "Utility.h"
#include <stdio.h>   // printf(),putchar()
#include <string.h>  // memcpy()
#include <assert.h>

// �֐��v���b�g�^�C�v
static const char* GetMazeAA(char c);

const int INIT_DISTANCE = -1;

const char defaultMaze[MAZE_HEIGHT][MAZE_WIDTH + 1] = {
	"#########o#########",
	"#ooooooo#o#ooooooo#",
	"#o###o#o#o#o#o###o#",
	"#o# #o#ooooo#o# #o#",
	"#o###o###o###o###o#",
	"#ooooooooooooooooo#",
	"#o###o###o###o###o#",
	"#ooo#o#ooooo#o#ooo#",
	"###o#o#o###o#o#o###",
	"oooooooo# #oooooooo",
	"###o#o#o###o#o#o###",
	"#ooo#o#ooooo#o#ooo#",
	"#o###o###o###o###o#",
	"#oooooooo oooooooo#",
	"#o###o###o###o###o#",
	"#o# #o#ooooo#o# #o#",
	"#o###o#o#o#o#o###o#",
	"#ooooooo#o#ooooooo#",
	"#########o#########"
};
// �X�e�[�W������
void InitializeStage(Stage* stage, Character* player)
{
	memcpy(stage->maze, defaultMaze, sizeof(stage->maze));
	stage->player = player;
	stage->monsterNum = 0;
	stage->chaser = nullptr;
	InitializeVector2List(&stage->v2list, V2LIST_SIZE);
	InitializeVector2List(&stage->v2temp, V2LIST_SIZE);
	//  
	// ���������R�[�f�B���O���Ă�������
	// stage->maze�� defaultMaze���R�s�[���܂��B(memcpy()���g���܂�
	// player �������܂�
	// monsterNum(�����X�^�[�̓o�^��)��0�ɂ��܂�
	// chaser �� nullptr�@�����܂�
	//  
	InitializeVector2List(&stage->v2list, V2LIST_SIZE);
	InitializeVector2List(&stage->v2temp, V2LIST_SIZE);
}
// �X�e�[�W��n��
void FinalizeStage(Stage* stage)
{
	FinalizeVector2List(&stage->v2list);
	FinalizeVector2List(&stage->v2temp);
}
// �����X�^�[�o�^
void RegistMonster(Stage* stage, Character* monster)
{
	assert(stage->monsterNum < MONSTER_SIZE);
	stage->monster[stage->monsterNum++] = monster;
	if (monster->id == CHARA_CHASE)
	{
		stage->chaser = monster;
	}
	//
	// ���������R�[�f�B���O���Ă��������B
	// stage��monster[] �� monster ��o�^���܂��B
	// �����A���ꂪCHARA_CHASE �Ȃ� stage��chaser �ɂ�������܂�
	//
}
// ���C�Y�`��
void DrawMaze(Stage* stage)
{
	Stage screen;
	memcpy(screen.maze, stage->maze, sizeof(screen.maze));

	// �L������Maze�ɏ�������
	Character* player = stage->player;
	SetMaze(&screen, player->pos.x, player->pos.y, player->id);
	for (int i = 0; i < stage->monsterNum; i++)
	{
		Character* monster = stage->monster[i];
		SetMaze(&screen, monster->pos.x, monster->pos.y, monster->id);
	}
	//
	// ���������R�[�f�B���O���Ă��������B
	// screen��maze�̃v���[���̈ʒu�Ƀv���[��id���������݂܂�
	// stage�̃����X�^�[�𑖍����܂�
	// screen��maze�̃��J�^�[�̈ʒu�Ƀ����X�^�[��id���������݂܂�
	// Maze��\��
	
	//
	ClearScreen();
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH ; x++)
		{
			char c = GetMaze(&screen, x, y);
			printf("%s", GetMazeAA(c));
		}
		putchar('\n');
	}
	//
	// ���������R�[�f�B���O���Ă�������
	// screen��maze�𑖍����܂��B(x,y)
	// maze(x,y)�̒l���� GetMazeAA()�ŕ�������擾���ĕ\�����܂��B
	//

	// �f�o�b�O
//	printf("player(%d,%d)\n", player->pos.x, player->pos.y);
//	for (int i = 0; i < stage->monsterNum; i++) {
//		Character* mon = stage->monster[i];
//		printf("monster-%d(%d,%d)\n", mon->id, mon->pos.x, mon->pos.y);
//	}
}
// �Q�[���I�[�o?
bool IsGameOver(Stage* stage)
{
	Character* player = stage->player;
	for (int i = 0; i < stage->monsterNum; i++)
	{
		Character* monster = stage->monster[i];
		if (Vector2Equ(monster->pos, player->pos))
		{
			return true;
		}
	}
	return false;
	//
	// ���������R�[�f�B���O���Ă�������
	// �����X�^�[�𑖍����܂��B
	// �����X�^�[�̈ʒu�ƃv���[���̈ʒu����v������A�Q�[���I�[�o�ł�(true)
	// ��v�����������I��������A�Q�[���I�[�o�ł͂���܂���(false)
	//
}
// �Q�[������(�h�b�g���H)?
bool IsComplete(Stage* stage)
{
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			if (GetMaze(stage, x, y) == MAZE_DOT)
			{
				return false;
			}
		}
	}
	return true;
	//
	// ���������R�[�f�B���O���Ă�������
	// maze�𑖍����܂�(x,y)
	// �h�b�g(MAZE_DOT)������΁A�Q�[�������ł͂���܂���(false)
	// �h�b�g�������炸�A�{�����I��������A�Q�[�������ł�(true)
	// 
}
// Maze(x,y)�擾
char GetMaze(Stage* stage, int x, int y)
{
	if (IsInMaze(x, y))
	{
		return stage->maze[y][x];
	}
	return MAZE_WALL;
	//
	// ���������R�[�f�B���O���Ă�������
	// maze�̃Q�b�^�[�֐�
	// IsInMaze()���m�F���āAmaze��(x,y)�ʒu�̓��e��Ԃ��܂�
	// IsInMaze()�O�Ȃ�AMAZE_WALL��Ԃ��܂��B
	//
}
// Maze(x,y)�Z�b�g
void SetMaze(Stage* stage, int x, int y, char c)
{
	if (IsInMaze(x, y))
	{
		stage->maze[y][x]=c;
	}
	//
	// ���������R�[�f�B���O���Ă�������
	// maze�̃Z�b�^�[�֐�
	// IsInMaze()���m�F���āAmaze��(x,y)�ʒu�� c���������݂܂�
	// IsInMaze()�O�Ȃ�A�Ȃɂ����܂���
	//
}

// Maze�̃A�X�L�[�A�[�g�擾
static const char* GetMazeAA(char c)
{
	switch (c) {
	default: assert(false);
	case MAZE_NONE: return "�@";
	case MAZE_WALL:return "��";
	case MAZE_DOT:return "�E";
	case MAZE_PLAYER:return "�Z";
	case MAZE_RANDOM:return "��";
	case MAZE_CHASE:return "��";
	case MAZE_AMBUSH:return "��";
	case MAZE_SIEGE:return "��";
	}
}
// MAZE�[�𒴂������W�̃��[�v����(�␳)
Vector2 GetLoopPosition(Vector2 pos)
{
	pos.x = (pos.x + MAZE_WIDTH) % MAZE_WIDTH;
	pos.y = (pos.y + MAZE_HEIGHT) % MAZE_HEIGHT;
	return pos;
}
// Maze���̈ʒu��?
bool IsInMaze(int x, int y)
{
	return 0 <= x && x < MAZE_WIDTH
		&& 0 <= y && y < MAZE_HEIGHT;
}