#include "hal.h"
#include "ch.h"

int main(void)
{
	halInit();
	chSysInit();
	
	return 0;
}
