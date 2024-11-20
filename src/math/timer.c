#include "timer.h"

void picg_ha_timer_start(picg_ha_timer* timer) 
{
    timer->start = clock();
    timer->end   = 0.0;
}

double picg_ha_timer_gettime(picg_ha_timer* timer) 
{
    timer->end = clock();
    return (double)(timer->end - timer->start) / CLOCKS_PER_SEC;
}

void picg_ha_timer_reset(picg_ha_timer* timer) 
{
    timer->start = 0.f;
    timer->end = 0.f;
}