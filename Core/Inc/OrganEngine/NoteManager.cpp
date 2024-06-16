#include "NoteManager.h"


Note notesList[MAX_NOTES] = {Note{}};
//std::list<Note> notesList;
//std::mutex notesMutex;


void note_manager_initialize() {
	for (uint8_t noteIndex = 0; noteIndex < MAX_NOTES; noteIndex++)
	{
		notesList[noteIndex].midiNote = noteIndex;
	}
}
