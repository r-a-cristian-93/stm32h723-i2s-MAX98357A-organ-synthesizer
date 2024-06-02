#define MINIAUDIO_IMPLEMENTATION
#include <iostream>
#include <cmath>
#include <bitset>
#include <list>
#include <nanomidi/decoder.h>
#include <nanomidi/msgprint.h>

#include "Common.h"
#include "Parameter.h"
#include "EnvelopeADSR.h"
#include "MidiManager.h"
#include "Note.h"

//set up array with sine values in signed 8-bit numbers
#define LUT_SIZE 1024
#define SAMPLE_RATE 65536
#define MIDI_NOTES 128

float sinTable[LUT_SIZE];
void initSineTable() {
  for (uint32_t i = 0; i < LUT_SIZE; ++i) {
    sinTable[i] = sin(M_2PI * i / LUT_SIZE);
  }
}

//setup frequencies/phase increments, (A4 is defined as 440Hz)
uint16_t phaseIncrement[MIDI_NOTES];
void initPhaseIncrement() {
  for (uint32_t i=0; i < MIDI_NOTES; i++){
	  uint8_t mul = (LUT_SIZE * LUT_SIZE) / SAMPLE_RATE;
	  phaseIncrement[i] = note_frequency[i][0] * mul;
//    phaseIncrement[i]= 110.0 * pow(2.0, ( (i-21) / 12.0)) * 65536.0 / (48000.0/512) + 0.5;
  }
}

void initSynth()
{
	initSineTable();
	initPhaseIncrement();
}

Parameter drawbar_amplitude[DRAWBARS_COUNT] = {Parameter()};
Parameter vibrato_amplitude{0.02, 0.002, 0.001, 0.1};
Parameter vibrato_frequency{0.8, 0.8, 0.01, 6.8, 0.8, 0.0001};

double g_time = 0.0;
double g_amplitude = 1.0;

std::list<Note> notes_list;

double organGenerateSample(Note& note, double time)
{
    double sample = 0;

    for (int drawbar_index = 0; drawbar_index < 1; drawbar_index++)
    {
    	uint16_t lutIndex = note.phase >> 6;

    	const float sinValue = sinTable[lutIndex];

        sample += sinValue * drawbar_amplitude[drawbar_index].current_value;
    }

    note.phase += phaseIncrement[note.value];

    return sample;
}

void generateSamples(void *pOutput, uint32_t startIndex, uint32_t endIndex)
{
    float *pOutputF32 = (float *)pOutput;

    for (uint32_t iFrame = startIndex; iFrame < endIndex; iFrame += 2)
    {
        double sample = 0;
        double noteSample = 0;

        // Update LFO
        update_parameter(vibrato_amplitude);
        update_parameter(vibrato_frequency);

        // Update drawbar amplitude
        for (int drawbar_index = 0; drawbar_index < DRAWBARS_COUNT; drawbar_index++)
        {
            update_parameter(drawbar_amplitude[drawbar_index]);
        }

		for (Note &note : notes_list)
		{
			// Generate sample for current note
			noteSample = organGenerateSample(note, g_time);

			// Apply envelope
			noteSample *= note.envelope.GetAmplitude(g_time);

			// Apply global amplitude
			noteSample *= g_amplitude;

			// Make room for more notes to be played simultaneously
			noteSample *= 0.01;

			// Add to current sample
			sample += noteSample;
		}

        // Limit volume so we won't blow up speakers
        if (sample > 1.0) sample = 1.0;
        if (sample < -1.0) sample = -1.0;

        // Add sample to left channel
        *pOutputF32++ = (uint16_t) (sample * 10000);
        // Add sample to right channel
        *pOutputF32++ = (uint16_t) (sample * 10000);

        // Advance time
        g_time += 1.0 / 48000;
    }
}

void clearSilencedNotes()
{
    std::list<Note>::iterator it = notes_list.begin();

    while (it != notes_list.end())
    {
        // Remove one by one in the order they were added
        if (it->envelope.GetAmplitude(g_time) <= 0 && !it->envelope.bNoteOn)
        {
            it = notes_list.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void getSamples(void *pOutput, uint32_t startIndex, uint32_t endIndex)
{
    clearSilencedNotes();
    generateSamples(pOutput, startIndex, endIndex);
}

void executeMidiMessage(uint8_t *buffer, uint8_t length)
{
    unsigned int nBytes = length;
    struct midi_istream istream;

    // Nanomidi does not read from std::vector so send the address of the first element
    midi_istream_from_buffer(&istream, &buffer[0], nBytes);
    struct midi_message *message = midi_decode(&istream);
    // print_msg(message);

    switch (message->type)
    {
        case MIDI_TYPE_NOTE_ON:
        {
            notes_list.push_back(
                Note{message->data.note_on.note, EnvelopeADSR(g_time)}
            );
        }
        break;

        case MIDI_TYPE_NOTE_OFF:
        {
            for (Note &note : notes_list)
            {
                if (note.value == message->data.note_off.note && note.envelope.bNoteOn)
                {
                    note.envelope.NoteOff(g_time);
                    break;
                }
            }
        }
        break;

        case MIDI_TYPE_CONTROL_CHANGE:
        {
            uint8_t controller = message->data.control_change.controller;
            uint8_t value = message->data.control_change.value;

            if (is_drawbar_controller(controller))
                set_parameter_value(
                    drawbar_amplitude[get_drawbar_id(controller)],
                    value / 127.0f
                );
            if (is_vibrato_controller(controller))
            {
                double vibrato_value;

                if (value == 0) vibrato_value = vibrato_frequency.min_value;
                else vibrato_value = vibrato_frequency.max_value;

                set_parameter_value(
                    vibrato_frequency,
                    vibrato_value
                );
            }
        }
		break;

        default:
        {
        	// DO NOTHING
        }
        break;
    }
}

