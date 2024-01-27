#include "delay.h"
#include "systick_utils.h"


uint32_t millis(void)
{
	/* à compléter */
	int32_t start;

	BOARD_SystickStart(&start);
	return BOARD_SystickElapsedTime_us(&start)*1000;
}
void delayMicroseconds(int time)
{
	uint32_t tm = (uint32_t)time;
	BOARD_DELAY_ums(tm);
}

void delayMillis(int time)
{

	uint32_t tm = (uint32_t)time;
		BOARD_DELAY_ms(tm);
}

