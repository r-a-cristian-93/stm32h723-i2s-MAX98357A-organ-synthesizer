#ifndef __SYNTH_H
#define __SYNTH_H

void initSynth();
void getSamples(void *pOutput, uint32_t startIndex, uint32_t endIndex);
void executeMidiMessage(uint8_t *buffer, uint8_t length);


#endif
