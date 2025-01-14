

#include "EditorContent.h"
#include "../ParamIDs.h"

EditorContent::EditorContent (juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um)
    : wetDial (*apvts.getParameter (param_ids::wet), &um)
    , freqDial (*apvts.getParameter (param_ids::freq), &um)
    , ratioDial (*apvts.getParameter (param_ids::ratio), &um)
    , ampEnvDial (*apvts.getParameter (param_ids::ampEnv), &um)
    , feedbackDial (*apvts.getParameter (param_ids::feedback), &um)
    , pitchThreshDial (*apvts.getParameter (param_ids::pitchThresh), &um)
    , pitchEnvDial (*apvts.getParameter (param_ids::pitchEnv), &um)
{
    setWantsKeyboardFocus (true);
    setFocusContainerType (FocusContainerType::keyboardFocusContainer);

    // Set interval of values changed by arrow keys or shift + arrow keys.
    wetDial.setInterval (5.0f);
    wetDial.setFineInterval (1.0f);
    addAndMakeVisible (wetDial);
    freqDial.setInterval (5.0f);
    freqDial.setFineInterval (1.0f);
    addAndMakeVisible (freqDial);
    ratioDial.setInterval (5.0f);
    ratioDial.setFineInterval (1.0f);
    addAndMakeVisible (ratioDial);
    ampEnvDial.setInterval (5.0f);
    ampEnvDial.setFineInterval (1.0f);
    addAndMakeVisible (ampEnvDial);
    feedbackDial.setInterval (5.0f);
    feedbackDial.setFineInterval (1.0f);
    addAndMakeVisible (feedbackDial);
    pitchThreshDial.setInterval (5.0f);
    pitchThreshDial.setFineInterval (1.0f);
    addAndMakeVisible (pitchThreshDial);
    pitchEnvDial.setInterval (5.0f);
    pitchEnvDial.setFineInterval (1.0f);
    addAndMakeVisible (pitchEnvDial);
}

void EditorContent::resized()
{
    const auto topDialBounds = juce::Rectangle { 0, 30, 80, 95 };
    wetDial.setBounds (topDialBounds.withX (30));
    freqDial.setBounds (topDialBounds.withX (130));
    ratioDial.setBounds (topDialBounds.withX (230));
    ampEnvDial.setBounds (topDialBounds.withX (330));

    const auto bottomDialBounds = topDialBounds.withY (155);
    feedbackDial.setBounds (bottomDialBounds.withX (80));
    pitchThreshDial.setBounds (bottomDialBounds.withX (180));
    pitchEnvDial.setBounds (bottomDialBounds.withX (280));
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
