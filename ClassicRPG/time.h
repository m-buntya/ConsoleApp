#pragma once
#include <time.h>  // clock()

void Wait(int milliseconds)
{
    // �N���b�N���Ԃ��擾���A�ҋ@����ڕW���Ԃ�ݒ�
    clock_t start_time = clock();

    // �o�ߎ��Ԃ��w�肳�ꂽ�~���b�ɒB����܂Ń��[�v
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}