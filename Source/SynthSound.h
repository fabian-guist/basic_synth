/*
  ==============================================================================

    SynthSound.h
    Created: 14 May 2018 7:13:32pm
    Author:  Fabian Guist

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber)
    {
        return true;
    }
    bool appliesToChannel(int midiChannel)
    {
        return true;
    }
};
