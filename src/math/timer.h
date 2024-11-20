#pragma once
#include <time.h>

typedef struct {
    clock_t start;
    clock_t end;
} picg_ha_timer;

void picg_ha_timer_start(picg_ha_timer*);
double picg_ha_timer_gettime(picg_ha_timer*);
void picg_ha_timer_reset(picg_ha_timer*);
