

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class Dial final : public juce::Component
{
public:
    enum ColourIds : std::uint8_t
    {
        foregroundArcColourId,
        backgroundArcColourId,
        needleColourId,
        borderColourId,
    };

    explicit Dial (juce::RangedAudioParameter& param, juce::UndoManager* um = nullptr);
    ~Dial() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;
    void mouseDoubleClick (const juce::MouseEvent& e) override;

    bool keyPressed (const juce::KeyPress& k) override;

    void focusGained (FocusChangeType cause) override;
    void focusLost (FocusChangeType cause) override;

    float getValue() const;

    void setInterval (float newInterval) { interval = newInterval; }
    void setFineInterval (float newFineInterval) { fineInterval = newFineInterval; }

    void setTextBoxColour (juce::Colour newColour);
    void setLabelColour (juce::Colour newColour);

    void setLabelText (const juce::String& newLabelText);

private:
    void updateValue (float newValue);

    void drawDial (juce::Graphics& g);
    void createBorder (const juce::Rectangle<float>& bounds);

    juce::RangedAudioParameter& audioParam;
    juce::ParameterAttachment paramAttachment;

    float value {};

    static constexpr auto sensitivity { 0.01f };
    float interval { 1.0f };
    float fineInterval { 0.1f };

    static constexpr auto startAngle { juce::MathConstants<float>::pi + (juce::MathConstants<float>::pi / 6.0f) };
    static constexpr auto endAngle { (3.0f * juce::MathConstants<float>::pi)
                                     - (juce::MathConstants<float>::pi / 6.0f) };

    juce::Point<float> mousePosWhenLastDragged;
    juce::Rectangle<float> mainArea;
    juce::Path borderPath;
    static constexpr auto borderThickness { 1.5f };

    juce::Label label;

    class TextBox;
    std::unique_ptr<TextBox> textBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dial)
};
