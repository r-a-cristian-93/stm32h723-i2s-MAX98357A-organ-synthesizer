#ifndef NOTE_H
#define NOTE_H

#include <cstdint>
#include <OrganEngine/Envelope.h>

struct Note
{
    uint8_t midiNote = 0;
    Envelope envelope;
    float phaseAccumulator[DRAWBARS_COUNT] = {0.0};
};

#endif