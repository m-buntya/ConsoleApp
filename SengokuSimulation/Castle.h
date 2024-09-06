#pragma once
//======================================
//	�퍑�V�~�����[�V����  ��
//======================================
#ifndef __CASTLE_H
#define __CASTLE_H
#include "LordId.h"
#include "CastleId.h"

const int CONNECTED_SIZE = 10;

typedef struct {
    const char* name;    // ���O
    LordId owner;        // ���
    int troopCount;      // ����
    CastleId connectedList[CONNECTED_SIZE]; // �ڑ����ꂽ��̃��X�g
    int  curx, cury;     // �`��ʒu
    const char* mapName; // �}�b�v��̖��O
} Castle;

extern Castle castles[];

// ��̖��O���擾
const char* GetCastleName(Castle* castle);
// ���ID���擾
LordId GetCastleOwner(Castle* castle);
// �������擾
int GetCastleTroopCount(Castle* castle);
// �ߗׂ̏郊�X�g���擾
CastleId* GetCastleConnectedList(Castle* castle);
// �`��X���W���擾
int GetCastleCurx(Castle* castle);
// �`��Y���W���擾
int GetCastleCury(Castle* castle);
// �}�b�v��̖��O���擾
const char* GetCastleMapName(Castle* castle);
// ������������
void SetCastleTroopCount(Castle* castle, int troopCount);
// �����Z�b�g
void SetCastleOwner(Castle* castle, LordId owner);
// �����ɉ��Z����
void AddCastleTroopCount(Castle* castle, int add);

#endif //  __CASTLE_H
