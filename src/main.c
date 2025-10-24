#include "userprogram.h"
#include "globals/runtime.h"
#include <stdlib.h>

void error() 
{
    exit(-1);
}

int main() 
{

    if(program_init() != 0) 
    {
        PICG_ERROR("program_init() returned with an error!");
        error();
    }
    
    for(;;) 
    {
        if(program_update() != 0) 
        {
            PICG_ERROR("program_update() returned with an error!");
            error();
        }
        
        if(program_render() != 0) 
        {
            PICG_ERROR("program_render() returned with an error!");
            error();
        }
    }

    if(program_close() != 0) 
    {
        PICG_ERROR("program_close() returned with an error!");
        error();
    }

    return 0;
}