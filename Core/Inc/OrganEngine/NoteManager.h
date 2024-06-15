#ifndef NOTE_MANAGER_H
#define NOTE_MANAGER_H

#include <list>
//#include <mutex>
#include <OrganEngine/Note.h>

extern std::list<Note> notesList;
//extern std::mutex notesMutex;


__attribute__((always_inline)) inline
void clearSilencedNotes()
{
//    const std::lock_guard<std::mutex> lock(notesMutex);

    for (auto it = notesList.begin(); it != notesList.end(); it++)
    {
        // Remove one by one in the order they were added
        if (it->envelope.getState() == ADSR_IDLE)
        {
            notesList.erase(it++);
            break;
        }
    }
}

__attribute__((always_inline)) inline
void note_on(uint8_t midiNote) {
//    const std::lock_guard<std::mutex> lock(notesMutex);

	clearSilencedNotes();

    notesList.emplace_back(Note{midiNote});
}

__attribute__((always_inline)) inline
void note_off(uint8_t midiNote) {
    // Call NoteOff on first occurence
//    const std::lock_guard<std::mutex> lock(notesMutex);
	uint32_t size = notesList.size();

	if (size > 10) {
		size++;
		size++;

	}

    for (Note &note : notesList)
    {
        if (note.midiNote == midiNote && note.envelope.getState() != ADSR_IDLE)
        {
            note.envelope.noteOff();
            break;
        }
    }
}

#endif
