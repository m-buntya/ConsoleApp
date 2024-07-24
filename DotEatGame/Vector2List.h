#pragma once
//======================================
//	Vector2List
//======================================
// �������ɃC���N���[�h�J�[�h(�J�n)���L�����Ă�������
#ifndef __VECTOR2LIST_H
#define __VECTOR2LIST_H
#include "Vector2.h"
typedef struct {
	int size;        // �z��T�C�Y
	int ptr;         // �i�[�|�C���^
	Vector2* array;  // �z��
} Vector2List;

// ������
void InitializeVector2List(Vector2List* list, int size);
// ��n��
void FinalizeVector2List(Vector2List* list);
// ���X�g�ɒǉ�
void AddVector2List(Vector2List* list, Vector2 pos);
// ���X�g�̗v�f���𓾂�
int GetCountVector2List(Vector2List* list);
// ���X�g�̗v�f�𓾂�
Vector2 GetVector2List(Vector2List* list, int idx);
// ���X�g���N���A
void ClearVector2List(Vector2List* list);
// ���X�g���R�s�[
void CopyVector2List(Vector2List* dst, Vector2List* src);
// ���X�g���v�����g����
void PrintVector2List(Vector2List* list);
#endif // !__VECTOR2LIST_H


// �������ɃC���N���[�h�J�[�h(�I��)���L�����Ă�������