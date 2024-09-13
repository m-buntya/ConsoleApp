#pragma once
//======================================
//	�u���b�N������ �X�e�[�W
//======================================
#ifndef __STAGE_H
#define __STAGE_H

const int FIELD_WIDTH = 14;
const int FIELD_HEIGHT = FIELD_WIDTH * 2;
const int PADDLE_WIDTH = 4;

// �t�B���[�h���e
typedef enum {
	FIELD_NONE,   // ���
	FIELD_BLOCK,  // �u���b�N
	FIELD_OUT,    // (�O��)
} Field;

// �X�e�[�W�\����
typedef struct {
	int ballX;        // �{�[���̈ʒu
	int ballY;
	int ballVelocityX; // �{�[���̑��x
	int ballVelocityY;
	int paddleX;       // �p�g��(���[)�̈ʒu
	int paddleY;
	Field field[FIELD_HEIGHT][FIELD_WIDTH];
} Stage;

// �`�惂�[�h
typedef enum {
	DM_READY,
	DM_GAME,
	DM_PAUSE,
	DM_CLEAR,
} DrawMode;

// ������
void InitializeStage(Stage* stage);
// �{�[���ʒu�����Z�b�g
void ResetBall(Stage* stage);
// �X�N���[���`��
void DrawScreen(Stage* stage, DrawMode mode);
// �{�[������������?
bool IsBallMiss(Stage* stage);
// �ʃN���A������?
bool IsClear(Stage* stage);
// �{�[���ړ�
void MoveBall(Stage* stage);
// �p�h���ړ�
void MovePaddle(Stage* stage, int addX);
// �t�B�[���h�̃Z�b�^�[
void SetField(Stage* stage, int x, int y, Field value);
// �t�B�[���h�̃Q�b�^�[
Field GetField(Stage* stage, int x, int y);

#endif // __STAGE_H