#include "hal.h"
#include "ch.h"

static volatile uint8_t counter;

static void increase(EXTDriver *extp, expchannel_t channel) 
{
	(void)extp;
	(void)channel;
	
	chSysLockFromISR();
	counter++;
	if(counter == 1)
		palSetPad(GPIOA, 3);
	chSysUnlockFromISR();
}

static void decrease(EXTDriver *extp, expchannel_t channel) 
{
	(void)extp;
	(void)channel;
	chSysLockFromISR();
	
	if(counter > 0)
		counter--;
	
	if(counter == 0)
		palClearPad(GPIOA, 3);
	chSysUnlockFromISR();
}

static const EXTConfig extcfg = {
  {
   {EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOA, increase},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOA, decrease},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
  }
};

int main(void)
{
	halInit();
	chSysInit();
	
	counter = 0;
	palClearPad(GPIOA, 3);
	palSetPadMode(GPIOA, 3, PAL_MODE_OUTPUT_PUSHPULL);
	extStart(&EXTD1, &extcfg);
	extChannelEnable(&EXTD1, 0);
	extChannelEnable(&EXTD1, 2);
	
	/*while(!0)
		chThdSleepMilliseconds(500);*/
	
	return 0;
}
