//======================================
//	3D�_���W����  �X�e�[�W
//======================================
#ifndef __STAGE_H
#define __STAGE_H
#include "Character.h"
#include "Vector2.h"
#include "Direction.h"

const int MAZE_WIDTH = 8;
const int MAZE_HEIGHT = 8;
const int GOAL_X = MAZE_WIDTH - 1;
const int GOAL_Y = MAZE_HEIGHT - 1;

typedef struct {
	bool walls[DIR_MAX];
} TILE;

typedef struct {
	TILE maze[MAZE_HEIGHT][MAZE_WIDTH];
	Character player;
	Vector2 goal;
	bool isForMap;   // UI forMap or for3D
} Stage;

// �X�e�[�W������
void InitializeStage(Stage* stage);
// 3D�`��
void Draw3D(Stage* stage);
// ���H�}�b�v�`��
void DrawMap(Stage* stage);
// �v���[�����S�[��������?
bool IsGoalPlayer(Stage* stage);
// �w��ʒu�̎w������̕ǃZ�b�g
void SetMazeWall(Stage* stage, Vector2 pos, Direction dir, bool value);
// �w��ʒu�̎w������͕ǂ�?
bool GetMazeWall(Stage* stage, Vector2 pos, Direction dir);
// �ʒu�͖��H��?
bool IsInsideMaze(Vector2 pos);

#endif //  __STAGE_H