#include "header/Graphics.h"
#include "header/GBCPU.h"
#include "header/Memory.h"
#include "header/IOs.h"



int main(void)
{
    printf("Init CPU\n");

    initCPU();
    initMem();
    initGraphics();
    running = 1;
    while (running)
    {
        OPSelect();
        NextGraphic();
        checkIO();
    }
    return 0;


}
