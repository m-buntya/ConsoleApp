#pragma once
//======================================
//	�}�b�v
//======================================
#ifndef __MAP_H
#define __MAP_H

const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
const int SCREEN_WIDTH = 16;
const int SCREEN_HEIGHT = 12;

typedef char MapArray[MAP_HEIGHT][MAP_WIDTH + 1];

const char outOfMap = '*';

// �}�b�vID
typedef enum {
	MAP_FIELD,        // �t�B�[���h
	MAP_KING_CASTLE,  // ���l�̏�
	MAP_BOSS_CASTLE,  // �{�X�̏�
	MAP_NONE = -1,
} MapId;

// ���̃}�b�v�ƃG���g���[�ʒu
typedef struct {
	MapId nextId;
	int nextX, nextY;
} NextMap;

// �}�b�v�X�y�b�N
typedef struct {
	MapArray* array;        // �}�b�v
	char    outData;        // �}�b�v�O�̃f�[�^
	NextMap nextMap_Out;    // �}�b�v�o���Ƃ��̍s��
	NextMap nextMap_K;      // K ���񂾎��̍s��
	NextMap nextMap_B;      // B ���񂾎��̍s��
	bool isBattleEncount;   // �o�g���G���J�E���g���邩?
} MapSpec;

// �}�b�v�f�[�^���擾
char GetMapData(MapSpec* spec, int x, int y);
// id����}�b�v�X�y�b�N���擾
MapSpec* GetMapSpec(MapId id);
// �}�b�v�f�[�^��AA���擾
const char* GetMapAA(char c);
// �}�b�v���ɂ��邩?
bool IsInMap(int x, int y);
// �o�g���G���J�E���g���肩?
bool IsBattleEncount(MapSpec* spec);

#endif //  __MAP_H
