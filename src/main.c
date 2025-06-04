#include "program.h"

int main() {

    program_init();

    for(;;) 
    {
        program_update();
        program_render();
    }

    program_close();

    return 0;
}