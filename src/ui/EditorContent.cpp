

#include "EditorContent.h"
#include "../ParamIDs.h"

EditorContent::EditorContent (juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um)
    : wetDial (*apvts.getParameter (param_ids::wet), &um)
{
    setWantsKeyboardFocus (true);
    setFocusContainerType (FocusContainerType::keyboardFocusContainer);

    // Set interval of values changed by arrow keys or shift + arrow keys.
    wetDial.setInterval (5.0f);
    wetDial.setFineInterval (1.0f);
    addAndMakeVisible (wetDial);
}

void EditorContent::resized()
{
    const auto topDialBounds = juce::Rectangle { 0, 30, 80, 95 };
    wetDial.setBounds (topDialBounds.withX (30));
    // pitchDial.setBounds (topDialBounds.withX (130));
    // sizeDial.setBounds (topDialBounds.withX (230));
    // posDial.setBounds (topDialBounds.withX (330));

    // const auto bottomDialBounds = topDialBounds.withY (155);
    // widthDial.setBounds (bottomDialBounds.withX (80));
    // someDial.setBounds (bottomDialBounds.withX (180));
    // gainDial.setBounds (bottomDialBounds.withX (280));
}

bool EditorContent::keyPressed (const juce::KeyPress& k)
{
    if (k.isKeyCode (juce::KeyPress::tabKey) && hasKeyboardFocus (false))
    {
        wetDial.grabKeyboardFocus();
        return true;
    }

    return false;
}
