#pragma once
//======================================
//	IntList
//======================================
#ifndef __INT_LIST_H
#define __INT_LIST_H
#include "Vector2.h"
typedef struct {
	int size;        // �z��T�C�Y
	int ptr;         // �i�[�|�C���^
	int* array;      // �z��
} IntList;

// ������
void InitializeIntList(IntList* list, int size);
// ��n��
void FinalizeIntList(IntList* list);
// ���X�g�ɒǉ�
void AddIntList(IntList* list, int value);
// ���X�g�̗v�f���𓾂�
int GetCountIntList(IntList* list);
// ���X�g�̗v�f�𓾂�
int GetIntList(IntList* list, int idx);
// ���X�g���N���A
void ClearIntList(IntList* list);
// ���X�g���R�s�[
void CopyIntList(IntList* dst, IntList* src);
// ���X�g���v�����g����
void PrintIntList(IntList* list);
#endif //  __INT_LIST_H