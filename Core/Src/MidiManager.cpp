/*
 * MidiManager.cpp
 *
 *  Created on: Jun 15, 2024
 *      Author: Bianca
 */

#include "MidiManager.h"

#include "usb_device.h"
#include "usbd_midi.h"

#include <OrganEngine/NoteManager.h>

//static uint8_t buffUsb[MIDI_BUFFER_LENGTH] = {0};
static uint8_t buffUsbCurrIndex = 0;
volatile static uint8_t buffUsbNextIndex = 0;

uint8_t cable, code, message, channel, messageByte1, messageByte2;


void USBD_MIDI_DataInHandler(uint8_t *usb_rx_buffer, uint8_t usb_rx_buffer_length)
{
  while (usb_rx_buffer_length && *usb_rx_buffer != 0x00)
  {
	cable = usb_rx_buffer[0] >> 4;
	code = usb_rx_buffer[0] & 0x0F;
	message = usb_rx_buffer[1] >> 4;
	channel = usb_rx_buffer[1] & 0x0F;
	messageByte1 = usb_rx_buffer[2];
	messageByte2 = usb_rx_buffer[3];
	usb_rx_buffer += 4;
	usb_rx_buffer_length -= 4;

	note_on(messageByte1);

  }
}

bool MIDI_HasUSBData(void)
{
  return buffUsbCurrIndex != buffUsbNextIndex;
}


void MIDI_ProcessUSBData(void)
{
  if (!message)
	return;

//  if (message = MIDI_MESSAGE_NOTE_ON)
	  note_on(messageByte1);

  buffUsbCurrIndex += 4;
}
