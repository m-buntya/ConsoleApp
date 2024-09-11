//======================================
//	3D�_���W����  �X�e�[�W
//======================================
#include "Stage.h"
#include "UI.h"
#include "Vector2List.h"
#include "IntList.h"
#include "Location.h"
#include "Utility.h"
#include <stdio.h>
#include <assert.h>
// �֐��v���g�^�C�v
static void GenerateMap(Stage* stage);
void DigWall(Stage* stage, Vector2 pos, Direction dir);
bool CanDigWall(Stage* stage, Vector2 pos, Direction dir);
void SetMazeWall(Stage* stage, Vector2 pos, Direction dir, bool value);
bool GetMazeWall(Stage* stage, Vector2 pos, Direction dir);
static void DrawMap_HorizontalWall(Stage* stage, int y, Direction dir);

// ������
void InitializeStage(Stage* stage)
{
	//GenerateMap(stage);                                                               �����s���@��O�݂����ȋ����m�F�@�R�����g�����Ƃ��Ƃ�
	InitCharacter(&stage->player, { 0,0 }, DIR_NORTH);
	SetVector2(&stage->goal, GOAL_X, GOAL_Y);
	stage->isForMap = false;
}
// �v���[�����S�[��������?
bool IsGoalPlayer(Stage* stage)
{
	// �v���[���̍��W���S�[���̍��W�ƈ�v���Ă����ׂ܂�
	// Vector2Equ()���g���܂�
	// ���������R�[�f�B���O���Ă�������
	return Vector2Equ(stage->player.pos, stage->goal);

}

// �}�b�v����
static void GenerateMap(Stage* stage)
{
	// Maze������(maze�����A�S�Ă�direction[]��true��)
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			Vector2 pos = { x,y };
			for (int d = 0; d < DIR_MAX; d++) {
				SetMazeWall(stage, pos, (Direction)d, true);
			}
		}
	}

	Vector2 curPos = { 0,0 };
	Vector2List toDigWallPos[1];
	IntList canDigDirection[1];
	InitializeVector2List(toDigWallPos, MAZE_WIDTH * MAZE_HEIGHT);
	InitializeIntList(canDigDirection, DIR_MAX);
	AddVector2List(toDigWallPos, curPos);

	while (true) {
		// curPos�̌@�����������X�e�B���O
		ClearIntList(canDigDirection);
		for (int d = 0; d < DIR_MAX; d++) {
			if (CanDigWall(stage, curPos, (Direction)d)) {
				AddIntList(canDigDirection, d);
			}
		}

		int count = GetCountIntList(canDigDirection);
		if (count > 0) {
			// ���X�g���烉���_���ɑI��ŁA�@��
			int idx = GetRand(count);
			Direction digDirection = (Direction)GetIntList(canDigDirection, idx);
			DigWall(stage, curPos, digDirection);
			// �@���������ɐi��
			Vector2 digVec = GetDirVector2(digDirection);
			curPos = Vector2Add(curPos, digVec);
			AddVector2List(toDigWallPos, curPos);
		}
		else {
			// �@���������Ȃ��Ƃ��A
			DelVector2List(toDigWallPos, 0);
			if (GetCountVector2List(toDigWallPos) <= 0) {
				break;
			}
			curPos = GetVector2List(toDigWallPos, 0);
		}
	}
}
// �}�b�v��`��
void DrawMap(Stage* stage)
{
	Character* player = &stage->player;

	for (int y = 0; y < MAZE_HEIGHT; y++) {
		DrawMap_HorizontalWall(stage, y, DIR_NORTH);

		for (int x = 0; x < MAZE_WIDTH; x++) {
			Vector2 pos = { x,y };
			const char* floor = "�@";
			if (Vector2Equ(pos, player->pos)) {
				static const char* directionAA[] = {
					"��",  // DIR_NORTH
					"��",  // DIR_WEST
					"��",  // DIR_SOUTH
					"��",  // DIR_EAST
				};
				floor = directionAA[player->dir];
			}
			else if (Vector2Equ(pos, stage->goal)) {
				floor = "�f";
			}
			const char* west = GetMazeWall(stage, pos, DIR_WEST) ? "|" : " ";
			const char* east = GetMazeWall(stage, pos, DIR_EAST) ? "|" : " ";
			printf("%s%s%s", west, floor, east);
		}
		putchar('\n');

		DrawMap_HorizontalWall(stage, y, DIR_SOUTH);
	}
}
// DIR_NORTH/DIR_SOUTH �̐����ǂ�`��
static void DrawMap_HorizontalWall(Stage* stage, int y, Direction dir)
{
	for (int x = 0; x < MAZE_WIDTH; x++) {
		const char* wall = GetMazeWall(stage, { x, y }, dir) ? "�\" : "�@";
		printf("+%s+", wall);
	}
	putchar('\n');
}

// �^��3D �`��
void Draw3D(Stage* stage)
{
	char screen[] =
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n"
		"         \n";
	// 
	//  �v���[���̎���(A�`E)�ɂ���
	//	+--+--+--+
	//  |�`|�b|�a|
	//  +--+--+--+
	//  |�c|��|�d|
	//  +--+--+--+
	Character* player = &stage->player;
	for (int i = 0; i < LOC_MAX; i++) {
		Vector2 loc = GetLocationVector2(player->dir, (Location)i);
		Vector2 pos = Vector2Add(player->pos, loc);
		if (IsInsideMaze(pos) == false) {
			continue;
		}

		for (int j = 0; j < DIR_MAX; j++) {
			// �v���[�����猩������
			// ��������(0,1,2,3) ���v���[����(0)�@���猩��� ��������(0,1,2,3)
			// ��������(0,1,2,3) ���v���[����(1)�@���猩��� ��������(3,0,1,2)
			// ��������(0,1,2,3) ���v���[����(2)�@���猩��� ��������(2,3,0,1) 
			// ��������(0,1,2,3) ���v���[����(3)�@���猩��� ��������(1,2,3,0)
			Direction dir = (Direction)((DIR_MAX + j - player->dir) % DIR_MAX);

			if (GetMazeWall(stage, pos, (Direction)j) == false) {
				continue;
			}
			const char* aa = GetLocationAA((Location)i, dir);
			if (aa == nullptr) {
				continue;
			}
			// aa[] �� screen[]�֋󔒈ȊO���R�s�[���܂��B
			// ���������R�[�f�B���O���Ă��������B
			// 
			for (int k = 0; k < sizeof(screen) - 1; k++) 
			{
				const char c = aa[k];
				if (c != ' ')
				{
					screen[k] = c;
				}
			}
		}
	}
	//
	// screen ��`��
	//
	for (int i = 0; i < sizeof(screen) - 1; i++) {
		char c = screen[i];
		switch (c) {
		case ' ': printf("�@"); break;
		case '#': printf("�@"); break;
		case '_': printf("�Q"); break;
		case '|': printf("�b"); break;
		case '/': printf("�^"); break;
		case 'L': printf("�_"); break;
		case '\n':
			printf("%c", c);
			break;
		default:
			printf("%2x\n", c);
			assert(false);
			break;
		}
	}
}
// maze��pos��dir �����Ɍ@��
void DigWall(Stage* stage, Vector2 pos, Direction dir)
{
	// maze�̊O�Ȃ�Ȃɂ����Ȃ�
	if (IsInsideMaze(pos) == false) {
		return;
	}
	SetMazeWall(stage, pos, dir, false);

	Vector2 dirVector2 = GetDirVector2(dir);
	Vector2 newPos = Vector2Add(pos, dirVector2);

	if (IsInsideMaze(newPos)) {
		// �k����A�������A�쁨�k�A������
		Direction dir2 = (Direction)((dir + 2) % DIR_MAX);
		SetMazeWall(stage, newPos, dir2, false);
	}
}
// maze��pos��dir�����Ɍ@��邩?
bool CanDigWall(Stage* stage, Vector2 pos, Direction dir)
{
	Vector2 dirVector2 = GetDirVector2(dir);
	Vector2 nextPos = Vector2Add(pos, dirVector2);
	if (IsInsideMaze(nextPos) == false) {
		return false;
	}

	for (int d = 0; d < DIR_MAX; d++) {
		if (GetMazeWall(stage, nextPos, (Direction)d) == false) {
			return false;
		}
	}
	return true;
}
// maze��pos��dir �Z�b�^�[
void SetMazeWall(Stage* stage, Vector2 pos, Direction dir, bool value)
{
	// pos��dir �͈̔̓`�F�b�N���s���āAok�Ȃ�value�������܂�
	// ���������R�[�f�B���O���Ă��������B
	if (IsInsideMaze(pos) && IsInDirection(dir))
	{
		stage->maze[pos.y][pos.x].walls[dir] = value;
	}
}
// maze��pos��dir �Q�b�^�[
bool GetMazeWall(Stage* stage, Vector2 pos, Direction dir)
{
	// pos��dir �͈̔̓`�F�b�N���s���āAok�Ȃ�l��Ԃ��܂�
	// �����łȂ���� false��Ԃ��܂�
	// ���������R�[�f�B���O���Ă��������B
	if (IsInsideMaze(pos) && IsInDirection(dir))
	{
		return stage->maze[pos.y][pos.x].walls[dir];
	}
	return false;
}
// ���W��maze����?
bool IsInsideMaze(Vector2 pos)
{
	// pos.x �� 0 �` MAZE_WIDTH-1�@����
	// pos.y �� 0 �` MAZE_HEIGHT-1 ���𒲂ׂ܂�
	// ���������R�[�f�B���O���Ă��������B
	return 0 <= pos.x && pos.x < MAZE_WIDTH && 0 <= pos.y < MAZE_HEIGHT;
}