
#include "midi_router.h"
//#include "usart.h"
#include "usb_device.h"
#include "usbd_midi.h"
#include "led.h"
#include <stdbool.h>

#include <OrganEngine/NoteManager.h>


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

    usb_rx_buffer_length -= 4;
  }
}

void processMessage(uint8_t data)
{
	ledToggle();
}

void MIDI_ProcessIncomming(void)
{
//  static uint8_t lastMessagesBytePerCable[MIDI_CABLES_NUMBER] = {0};
//  uint8_t *pLastMessageByte;
  uint8_t cable;
  uint8_t messageByte;
  uint8_t message;
  uint8_t param1;
  uint8_t param2;
//  void (*pSend)(uint8_t) = processMessage;

  if (buffUsbInCurrIndex == buffUsbInNextIndex)
    return;

//  note_on(64);

  cable = (buffUsbIn[buffUsbInCurrIndex] >> 4);
  messageByte = buffUsbIn[buffUsbInCurrIndex + 1];
  message = (messageByte >> 4);
  param1 = buffUsbIn[buffUsbInCurrIndex + 2];
  param2 = buffUsbIn[buffUsbInCurrIndex + 3];

//  switch (message) {
//	  case MIDI_MESSAGE_NOTE_ON:
//		  note_on(param1);
//		  break;
//	  case MIDI_MESSAGE_NOTE_OFF:
//		  note_off(param1);
//		  break;
//	  default:
//		  break;
//  }

  if (midiThrough) {
	  MIDI_addToUSBReport(cable, messageByte, param1, param2);
  }

  buffUsbInCurrIndex += 4;
}

#define MIDI_MSG_SIZE 4

void MIDI_addToUSBReport(uint8_t cable, uint8_t message, uint8_t param1, uint8_t param2)
{
  buffUsbOut[buffUsbOutNextIndex++] = (cable << 4) | (message >> 4);
  buffUsbOut[buffUsbOutNextIndex++] = (message);
  buffUsbOut[buffUsbOutNextIndex++] = (param1);
  buffUsbOut[buffUsbOutNextIndex++] = (param2);
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

