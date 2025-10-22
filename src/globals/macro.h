#pragma once
#include <stdio.h>

// C
#define picg_bool unsigned char
#define true 1
#define false 0

// code
#define PICG_DEBUG 1
#define PICG_QUIET_LOGGING 0

// error
#if PICG_QUIET_LOGGING 
    #define PICG_ERROR(msg) {}
    #define PICG_SUCC(msg, ...) {}
    #define PICG_LOG(msg, ...) {}
#else
    #define PICG_ERROR(msg) {printf("\e[1;31m Error in file \e[0;34m%s, function %s(), line %i. \e[0;37m Message: \e[1;31m", __FILE__, __func__, __LINE__); printf(msg); printf("\e[0;37m\n");}
    #define PICG_SUCC(msg, ...) {printf("\e[1;32m"); printf(msg, ##__VA_ARGS__); printf("\e[0;37m\n");}
    #define PICG_LOG(msg, ...) {printf("\e[0;37m"); printf(msg, ##__VA_ARGS__); printf("\e[0;37m\n");}
#endif

// Input
#define PICG_KEYS_STORED_COUNT 8