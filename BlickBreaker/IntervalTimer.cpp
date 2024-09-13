//======================================
//      �C���^�[�o���^�C�}�[
//======================================
#include "IntervalTimer.h"
#include <time.h>  // clock()

// �^�C�}�[�X�^�[�g
void StartTimer(IntervalTimer* timer, int fps)
{
	timer->interval = 1000 / fps;
	timer->nextClock = clock() + timer->interval;
}
// �C���^�[�o���o�߂�����?
bool IsInterval(IntervalTimer* timer)
{
	clock_t nowClock = clock();
	if (nowClock >= timer->nextClock) {
		timer->nextClock = nowClock + timer->interval;
		return true;
	}
	return false;
}