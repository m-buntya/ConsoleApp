//======================================
//	�퍑�V�~�����[�V����  �N�\
//======================================
#include "Chronology.h"
#include <stdio.h>   // printf(),vsnprintf(),snprintf()
#include <stdlib.h>  // malloc(),free()
#include <stdarg.h>  // va_list
#include <string.h>  // strlen()

const int TEMP_SIZE = 256;

// ������
void InitializeChronology(Chronology* chro, int buffSize)
{
	chro->buff = (char*)malloc(buffSize);
	chro->temp = (char*)malloc(TEMP_SIZE);
	if (chro->buff == nullptr || chro->temp == nullptr) {
		puts("malloc���s");
		exit(1);
	}
	chro->buffSize = buffSize;
	ClearChronology(chro);
}
// ��n��
void FinalizeChronology(Chronology* chro)
{
	free(chro->buff);
	free(chro->temp);
	chro->buff = nullptr;
	chro->temp = nullptr;
	chro->buffSize = 0;
}
// �N���A
void ClearChronology(Chronology* chro)
{
	chro->buff[0] = '\0';
}
// �L�^����
void RecordChronology(Chronology* chro, const char* fmt, ...)
{
	//
	// temp �֕����񐶐�
	//
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(chro->temp, TEMP_SIZE, fmt, vl);
	va_end(vl);
	//
	//  buff �� temp ��ǉ�
	//
	int len = strlen(chro->buff);
	int buffSize = chro->buffSize - len;
	snprintf(chro->buff + len, buffSize, "%s", chro->temp);
}
// �\��
void PrintChronology(Chronology* chro)
{
	printf("%s", chro->buff);
}