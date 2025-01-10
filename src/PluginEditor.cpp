

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "ui/MyColours.h"

PluginEditor::PluginEditor (PluginProcessor& p, juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um)
    : AudioProcessorEditor (&p)
    , undoManager (um)
    , editorContent (apvts, um)
{
    constexpr auto ratio = static_cast<double> (defaultWidth) / defaultHeight;
    setResizable (false, true);
    getConstrainer()->setFixedAspectRatio (ratio);
    getConstrainer()->setSizeLimits (defaultWidth / 2, defaultHeight / 2, defaultWidth * 2, defaultHeight * 2);
    setSize (defaultWidth, defaultHeight);
    editorContent.setSize (defaultWidth, defaultHeight);

    addAndMakeVisible (editorContent);
}

void PluginEditor::paint (juce::Graphics& g) { g.fillAll (MyColours::black); }

void PluginEditor::resized()
{
    const auto factor = static_cast<float> (getWidth()) / defaultWidth;
    editorContent.setTransform (juce::AffineTransform::scale (factor));
}

bool PluginEditor::keyPressed (const juce::KeyPress& k)
{
    if (k.isKeyCode ('Z') && k.getModifiers().isCommandDown())
    {
        if (k.getModifiers().isShiftDown())
            undoManager.redo();
        else
            undoManager.undo();

        return true;
    }

    return false;
}
