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

Parameter drawbar_amplitude[DRAWBARS_COUNT] = {Parameter()};
Parameter vibrato_amplitude{0.002, 0.002, 0.001, 0.1};
Parameter vibrato_frequency{0.8, 0.8, 0.01, 6.8, 0.8, 0.0001};

double g_time = 0.0;
double g_amplitude = 1.0;

std::list<Note> notes_list;

double organGenerateSample(unsigned int note, double time)
{
    double sample = 0;

    for (int drawbar_index = 0; drawbar_index < DRAWBARS_COUNT; drawbar_index++)
    {
        sample +=
            sin(
                M_2PI * (note_frequency[note][drawbar_index]) * time
                + (vibrato_amplitude.current_value * note_frequency[note][drawbar_index] * sin(M_2PI * vibrato_frequency.current_value * time)) // vibrato
            )
                * drawbar_amplitude[drawbar_index].current_value;
    }
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

		for (Note const &note : notes_list)
		{
			// Generate sample for current note
			noteSample = organGenerateSample(note.value, g_time);

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

//
//void loop()
//{
//    ma_device_config config = ma_device_config_init(ma_device_type_playback);
//    config.playback.format = ma_format_f32; // Set to ma_format_unknown to use the device's native format.
//    config.playback.channels = 2;           // Set to 0 to use the device's native channel count.
//    config.sampleRate = 44100;              // Set to 0 to use the device's native sample rate.
//    config.dataCallback = dataCallback;     // This function will be called when miniaudio needs more data.
//    config.pUserData = NULL;                // Can be accessed from the device object (device.pUserData).
//
//     Wait for user input (you can adjust this as needed)
//    std::cout << "Press ESC to exit..." << std::endl;
//    while (true)
//    {
//        int input = getchar();
//
//        if (input == 27)
//            break;
//
//        switch (input)
//        {
//        case 'd':
//            increase_value(vibrato_amplitude);
//            break;
//        case 'c':
//            decrease_value(vibrato_amplitude);
//            break;
//        case 'f':
//            increase_value(vibrato_frequency);
//            break;
//        case 'v':
//            decrease_value(vibrato_frequency);
//            break;
//        }
//
//        for (int i = 0; i < DRAWBARS_COUNT; i++)
//            std::cout << (i + 1) << " " << drawbar_amplitude[i].current_value << " " << drawbar_amplitude[i].target_value << std::endl;
//
//        std::cout << std::endl;
//        std::cout << "VIBRATO_AMPLITUDE:  " << vibrato_amplitude.current_value << std::endl;
//        std::cout << "VIBRATO_FREQUENCY:  " << vibrato_frequency.current_value << std::endl;
//        std::cout << "NOTES_LIST:  " << notes_list.size() << std::endl;
//        std::cout << std::endl;
//    }
//
//}
