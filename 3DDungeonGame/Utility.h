//======================================
//	���[�e�B���e�B
//======================================
#ifndef __UTILITY_H
#define __UTILITY_H

extern const char* EscBLACK;
extern const char* EscRED;
extern const char* EscGREEN;
extern const char* EscYELLOW;
extern const char* EscBLUE;
extern const char* EscMAZENTA;
extern const char* EscCYAN;
extern const char* EscWHITE;
extern const char* EscDEFAULT;

extern const char* EscBgBLACK;
extern const char* EscBgRED;
extern const char* EscBgGREEN;
extern const char* EscBgYELLOW;
extern const char* EscBgBLUE;
extern const char* EscBgMAZENTA;
extern const char* EscBgCYAN;
extern const char* EscBgWHITE;
extern const char* EscBgDEFAULT;

enum Key {
	ARROW_UP = 0xe048,
	ARROW_LEFT = 0xe04b,
	ARROW_DOWN = 0xe050,
	ARROW_RIGHT = 0xe04d,
	DECIDE = 0x0d,
	ESC = 0x1b,
	SPACE = 0x20,
};
// ����������
void InitRand();
// 0�`max-1 �̈�l�����𓾂�
int GetRand(int max);
// �L�[���͂�҂�
void WaitKey();
// �L�[���͎擾
Key GetKey();
// �L�[���͂��肩?
bool KeyAvailable();
// �X�N���[������
void ClearScreen();
// �J�[�\���ʒu�Z�b�g
void PrintCursor(int curx, int cury);
// �J�[�\���ۑ�
void SaveCursor();
// �J�[�\������
void RestoreCursor();
// ���ԑ҂�(m�b)
void Sleep_mSec(int mSec);

#endif // __UTILITY_H
