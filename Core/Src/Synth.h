#ifndef __SYNTH_H
#define __SYNTH_H


void dataCallback(void *pOutput, uint32_t frameCount);
void executeMidiMessage(uint8_t *buffer, uint8_t length);

#endif
