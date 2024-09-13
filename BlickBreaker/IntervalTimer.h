#pragma once
//======================================
//      �C���^�[�o���^�C�}�[
//======================================
#ifndef __INTERVAL_TIMER_H
#define __INTERVAL_TIMER_H
#include <time.h>  // clock_t, clock()

typedef struct {
	clock_t interval;
	clock_t nextClock;
} IntervalTimer;

// �^�C�}�[�X�^�[�g
void StartTimer(IntervalTimer* timer, int fps);
// �C���^�[�o���o�߂���?
bool IsInterval(IntervalTimer* timer);

#endif // __INTERVAL_TIMER_H