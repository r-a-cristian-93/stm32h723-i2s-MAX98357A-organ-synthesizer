
#include "midi_router.h"
//#include "usart.h"
#include "usb_device.h"
#include "usbd_midi.h"
#include "led.h"
#include <stdbool.h>

#include <OrganEngine/NoteManager.h>
#include <FmSynth/FmSynth.h>

#define USB_MIDI_MSG_LENGTH 4

extern USBD_HandleTypeDef hUsbDeviceHS;

static uint8_t buffUsbOut[MIDI_EPIN_SIZE] = {0};
static uint8_t buffUsbOutNextIndex = 0;

static uint8_t buffUsbIn[MIDI_BUFFER_LENGTH] = {0};
volatile static uint8_t buffUsbInNextIndex = 0;
static uint8_t buffUsbInCurrIndex = 0;

bool midiThrough = true;


void USBD_MIDI_DataInHandler(uint8_t *usb_rx_buffer, uint8_t usb_rx_buffer_length)
{
  while (usb_rx_buffer_length && *usb_rx_buffer != 0x00)
  {
    buffUsbIn[buffUsbInNextIndex++] = *usb_rx_buffer++;
    buffUsbIn[buffUsbInNextIndex++] = *usb_rx_buffer++;
    buffUsbIn[buffUsbInNextIndex++] = *usb_rx_buffer++;
    buffUsbIn[buffUsbInNextIndex++] = *usb_rx_buffer++;

    usb_rx_buffer_length -= USB_MIDI_MSG_LENGTH;
  }
}

uint8_t cable;
uint8_t messageByte;
uint8_t channel;
uint8_t message;
uint8_t param1;
uint8_t param2;

void MIDI_ProcessIncomming(void)
{
  if (buffUsbInCurrIndex == buffUsbInNextIndex)
	return;

  cable = (buffUsbIn[buffUsbInCurrIndex] >> 4);
  messageByte = buffUsbIn[buffUsbInCurrIndex + 1];
  channel = messageByte & 0b00001111;
  message = (messageByte >> 4);

  param1 = buffUsbIn[buffUsbInCurrIndex + 2];
  param2 = buffUsbIn[buffUsbInCurrIndex + 3];

  switch (message) {
	  case MIDI_MESSAGE_NOTE_ON:
		  fm_synth_note_on(param1, 1);
		  fm_synth_note_on(param1, 2);
		  fm_synth_note_on(param1, 3);
		  fm_synth_note_on(param1, 4);
//		  fm_synth_note_on(param1, 5);

		  note_on(param1);
		  break;
	  case MIDI_MESSAGE_NOTE_OFF:
		  fm_synth_note_off(param1, 1);
		  fm_synth_note_off(param1, 2);
		  fm_synth_note_off(param1, 3);
		  fm_synth_note_off(param1, 4);
//		  fm_synth_note_off(param1, 5);
		  note_off(param1);
		  break;
	  case MIDI_MESSAGE_CONTROL_CHANGE:
		  organ_oscillator_set_drawbar_amplitude(param1, param2);
		  break;
	  default:
		  break;
  }

  if (midiThrough) {
	  MIDI_send(cable, messageByte, param1, param2);
  }

  buffUsbInCurrIndex += USB_MIDI_MSG_LENGTH;
}

void MIDI_ProcessOutgoing(void)
{
	if (buffUsbOutNextIndex != 0)
	{
		if(USBD_MIDI_GetState(&hUsbDeviceHS) == MIDI_IDLE)
		{
			USBD_MIDI_SendReport(&hUsbDeviceHS, buffUsbOut, buffUsbOutNextIndex);
			buffUsbOutNextIndex = 0;
		}
	}
}

void MIDI_send(uint8_t cable, uint8_t message, uint8_t param1, uint8_t param2)
{
  buffUsbOut[buffUsbOutNextIndex++] = (cable << 4) | (message >> 4);
  buffUsbOut[buffUsbOutNextIndex++] = (message);
  buffUsbOut[buffUsbOutNextIndex++] = (param1);
  buffUsbOut[buffUsbOutNextIndex++] = (param2);
}

