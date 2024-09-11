#pragma once
#include <time.h>  // clock()

void Wait(int milliseconds)
{
    // クロック時間を取得し、待機する目標時間を設定
    clock_t start_time = clock();

    // 経過時間が指定されたミリ秒に達するまでループ
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}