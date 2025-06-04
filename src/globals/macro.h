#pragma once
#include <stdio.h>

// C
#define picg_bool unsigned int
#define true 1
#define false 0

// error
#define PICG_ERROR(msg) {printf("Error in file %s, function %s, line %i. Message: ", __FILE__, __func__, __LINE__); printf(msg); printf("\n");}

// code
#define PICG_DEBUG 1

// Input
#define PICG_KEYS_STORED_COUNT 8