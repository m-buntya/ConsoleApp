//======================================
//	IntList
//======================================
#include "IntList.h"
#include <stdio.h>   // printf()
#include <stdlib.h>  // calloc(),free(),exit()
// ������
void InitializeIntList(IntList* list, int size)
{
	list->array = (int*)calloc(size, sizeof(int));
	if (list->array == nullptr) {
		printf("calloc���s\n");
		exit(1);
	}
	list->size = size;
	list->ptr = 0;
}
// ��n��
void FinalizeIntList(IntList* list)
{
	free(list->array);
	list->array = nullptr;
	list->size = 0;
	list->ptr = 0;
}
// ���X�g�ɒǉ�
void AddIntList(IntList* list, int value)
{
	if (list->ptr < list->size) {
		list->array[list->ptr++] = value;
	}
}
// ���X�g�̗v�f���𓾂�
int GetCountIntList(IntList* list)
{
	return list->ptr;
}
// ���X�g�̗v�f�𓾂�
int GetIntList(IntList* list, int idx)
{
	if (idx < list->ptr) {
		return list->array[idx];
	}
	return  -1;
}
// ���X�g���N���A����
void ClearIntList(IntList* list)
{
	list->ptr = 0;
}
// ���X�g���R�s�[����
void CopyIntList(IntList* dst, IntList* src)
{
	ClearIntList(dst);
	int count = GetCountIntList(src);
	for (int i = 0; i < count; i++) {
		int value = GetIntList(src, i);
		AddIntList(dst, value);
	}
}
void PrintIntList(IntList* list)
{
	printf("IntList(%d):", list->ptr);
	for (int i = 0; i < list->ptr; i++) {
		printf("%d ", list->array[i]);
	}
	putchar('\n');
}