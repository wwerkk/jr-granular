

#pragma once

#include "Dial.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class EditorContent final : public juce::Component
{
public:
    EditorContent (juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um);

    void resized() override;
    bool keyPressed (const juce::KeyPress& k) override;

private:
    Dial intvDial;
    Dial pitchDial;
    Dial sizeDial;
    Dial posDial;
    Dial widthDial;
    Dial mixDial;
    Dial gainDial;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorContent)
};
