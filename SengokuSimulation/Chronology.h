#pragma once
//======================================
//	�퍑�V�~�����[�V����  �N�\
//======================================
#ifndef __CHRONOLOGY_H
#define __CHRONOLOGY_H

typedef struct {
	int buffSize;
	char* buff;
	char* temp;
} Chronology;

// ������
void InitializeChronology(Chronology* chro, int buffSize);
// ��n��
void FinalizeChronology(Chronology* chro);
// �N���A
void ClearChronology(Chronology* chro);
// �L�^����
void RecordChronology(Chronology* chro, const char* fmt, ...);
// �v�����g����
void PrintChronology(Chronology* chro);

#endif // __CHRONOLOGY_H