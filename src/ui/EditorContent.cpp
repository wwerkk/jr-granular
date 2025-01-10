

#include "EditorContent.h"
#include "../ParamIDs.h"

EditorContent::EditorContent (juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um)
    : intvDial (*apvts.getParameter (param_ids::interval), &um)
    , pitchDial (*apvts.getParameter (param_ids::pitch), &um)
    , sizeDial (*apvts.getParameter (param_ids::grainSize), &um)
    , posDial (*apvts.getParameter (param_ids::grainPos), &um)
    , widthDial (*apvts.getParameter (param_ids::width), &um)
    , mixDial (*apvts.getParameter (param_ids::mix), &um)
    , gainDial (*apvts.getParameter (param_ids::gain), &um)
{
    setWantsKeyboardFocus (true);
    setFocusContainerType (FocusContainerType::keyboardFocusContainer);

    // Set interval of values changed by arrow keys or shift + arrow keys.
    intvDial.setInterval (5.0f);
    intvDial.setFineInterval (1.0f);
    pitchDial.setInterval (1.0f);
    pitchDial.setFineInterval (0.1f);
    sizeDial.setInterval (5.0f);
    sizeDial.setFineInterval (1.0f);
    posDial.setInterval (5.0f);
    posDial.setFineInterval (1.0f);
    gainDial.setInterval (1.0f);
    gainDial.setFineInterval (0.1f);

    addAndMakeVisible (intvDial);
    addAndMakeVisible (pitchDial);
    addAndMakeVisible (sizeDial);
    addAndMakeVisible (posDial);
    addAndMakeVisible (widthDial);
    addAndMakeVisible (mixDial);
    addAndMakeVisible (gainDial);
}

void EditorContent::resized()
{
    const auto topDialBounds = juce::Rectangle { 0, 30, 80, 95 };
    intvDial.setBounds (topDialBounds.withX (30));
    pitchDial.setBounds (topDialBounds.withX (130));
    sizeDial.setBounds (topDialBounds.withX (230));
    posDial.setBounds (topDialBounds.withX (330));

    const auto bottomDialBounds = topDialBounds.withY (155);
    widthDial.setBounds (bottomDialBounds.withX (80));
    mixDial.setBounds (bottomDialBounds.withX (180));
    gainDial.setBounds (bottomDialBounds.withX (280));
}

bool EditorContent::keyPressed (const juce::KeyPress& k)
{
    if (k.isKeyCode (juce::KeyPress::tabKey) && hasKeyboardFocus (false))
    {
        intvDial.grabKeyboardFocus();
        return true;
    }

    return false;
}
