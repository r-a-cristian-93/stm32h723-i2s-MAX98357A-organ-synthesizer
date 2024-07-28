#ifndef EKO_TIGER_P61_H
#define EKO_TIGET_P61_H

#ifdef __cplusplus
extern "C" {
#endif

#include "midi_router.h"
#include "led.h"

void eko_tiger_p61_setup();
void eko_tiger_p61_loop();

//bool timeOut(uint32_t& tim, uint32_t millis);
bool areAllEqual(const uint16_t* array);
void readSpi6();

extern uint32_t timBlink;
extern uint32_t timSpi;


//__attribute((always_inline)) inline
//bool timeOut(uint32_t& tim, uint32_t millis)
//{
//	uint32_t nowTicks = HAL_GetTick();
//
//	if (nowTicks - tim > millis)
//	{
//		tim = nowTicks;
//
//		return true;
//	}
//
//	return false;
//}

__attribute((always_inline)) inline
void eko_tiger_p61_loop()
{
	while (1)
	{
	    MIDI_ProcessIncomming();
	    MIDI_ProcessOutgoing();

//	    if (timeOut(timBlink,100)) {
//			ledToggle();
//		}
//
//		if (timeOut(timSpi, 1)) {
//			readSpi6();
//		}
	}
}


#ifdef __cplusplus
}
#endif

#endif
