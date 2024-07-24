//======================================
//	���[�e�B���e�B
//======================================
#include "Utility.h" // eKey
#include <stdlib.h> // srand()
#include <time.h>  // time()
#include <windows.h> // GetStdHandle(),SetConsoleMode()
#include <stdio.h> // printf()
#include <conio.h> // _getch()

const char* EscBLACK = "\x1b[30m";
const char* EscRED = "\x1b[31m";
const char* EscGREEN = "\x1b[32m";
const char* EscYELLOW = "\x1b[33m";
const char* EscBLUE = "\x1b[34m";
const char* EscMAZENTA = "\x1b[35m";
const char* EscCYAN = "\x1b[36m";
const char* EscWHITE = "\x1b[37m";
const char* EscDEFAULT = "\x1b[39m";

// ����������
void InitRand()
{
	srand((unsigned int)time(NULL));
}
// 0�`max-1 �̈�l�����𓾂�
int GetRand(int max)
{
	int x = (rand() * max) / RAND_MAX;
	return x;
}
// �L�[���͂�҂�
void WaitKey()
{
	_getch();
}

// �L�[�擾
Key GetKey()
{
	int key = _getch();
	if (key == 0xe0) {
		int key2 = _getch();
		key = 0xe000 + key2;
	}
	return (Key)key;
}
// �L�[���͂��肩?
bool KeyAvailable()
{
	return _kbhit();
}
// �X�N���[������
void ClearScreen()
{
#if false
	// cmd.exe ���Ăяo���� cls ���s��
	system("cls");
#else
	static bool s_modeSet = false;

	// ��ʃ��[�h��؂�ւ��ăG�X�P�[�v�V�[�P���X���g����悤�ɂ���
	if (s_modeSet == false) {
		s_modeSet = true;
		HANDLE h = GetStdHandle(-11);
		SetConsoleMode(h, 0x07);
	}
	printf("\x1b[2J"	// ��ʃN���A
		"\x1b[0;0H");	// �J�[�\����0,0��
#endif
}
