#include "../header/GenInit.h"
#include "../header/Graphics.h"
#include "../header/GBCPU.h"
#include "../header/Memory.h"


uchar sl,Mode,fps,frames;
ulong videoTicks;
clock_t t1;

void initGraphics(){
    sl = 0;

    videoTicks = 0;
    Mode = 0;
    fps = 0;
    frames = 0;
}

///Updates VideoBuffer with new scanline values. Prints frame when scanline resets. Deals with Background and Window
void NextGraphic()
{

	ulong elapsedTime;
	
		t1 = clock();
		if (clock() - t1 > 1000)
		{
			t1 = clock();
			printf("FPS: %d\n", fps);
			fps = 0;
		}

		elapsedTime = getCPUTicks() - videoTicks;
		
		switch (Mode)//2->3->0->1
		{
			case 0://h-blank 204
				if (elapsedTime > 203)
				{
					if ((readMem(0xFF40) & 0x80) != 0x80)//lcd off
					{
						videoTicks += 204;
						//Mode = 1;
						break;
					}

					sl++;
					if (sl >= Winh) //V-Blank start
					{
						writeMem(0xFF0F, readMem(0xFF0F) | 1);
						frames++;
						fps = fps + 1;
						Mode = 1;
					}
					else//Next Line
						Mode = 2;
						
					writeMem(0xFF44, sl);//update LCD Y-Coordinate
					videoTicks += 204;
				}
				break;
			case 1://v-blank 4560
				if ((readMem(0xFF40) & 0x80) == 0x80)//lcd on
				{
					if (elapsedTime > 455)
					{
						sl++;
						if (sl == Vy)
						{
							sl = 0;
							Mode = 2;
						}
						writeMem(0xFF44, sl);
						videoTicks += 456;
					}
				}
				break;
			case 2://transfer 80
				if (elapsedTime > 79)
				{
					videoTicks += 80;
					Mode = 3;
				}
				break;
			case 3://search 172
				if (elapsedTime > 171)
				{
					videoTicks += 172;
					Mode = 0;
				}
				break;
		}
		setLCDC((readMem(0xFF41) & 0xFC) | Mode); //change videomode
}

uchar getSL() {
	return sl;
}

uchar getfps() {
	return fps;
}

void clearfps(){
    fps = 0;
}
