

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"
#include "ParamIDs.h"
#include "PluginEditor.h"
#include "RNBO_Types.h"

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Format the number to always display three digits like "0.01 %", "10.0 %", "100 %".
    const auto percentage = [] (auto value, auto)
    {
        constexpr auto unit = " %";
        auto v { value * 100.f };
        if (v < 10.0f)
            return juce::String { v, 2 } + unit;
        if (v < 100.0f)
            return juce::String { v, 1 } + unit;
        return juce::String { v } + unit;
    };

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::wet, 1 },
        "Wet",
        juce::NormalisableRange { 0.0f, 1.0f, 0.01f, 1.0f },
        0.5f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (percentage)));

    // Format the number to always display three digits like "10.0 Hz", "100 Hz".
    const auto Hz = [] (auto value, auto)
    {
        constexpr auto unit = " Hz";

        if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
            return juce::String { v, 1 } + unit;

        return juce::String { std::round (value) } + unit;
    };

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::freq, 1 },
        "Freq",
        juce::NormalisableRange { -100.0f, 100.0f, 0.01f, 1.0f },
        100.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (Hz)));
    // // Format the number to always display three digits like "10.0 ms", "100 ms".
    // const auto ms = [] (auto value, auto)
    // {
    //     constexpr auto unit = " ms";

    //     if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
    //         return juce::String { v, 1 } + unit;

    //     return juce::String { std::round (value) } + unit;
    // };

    // layout.add (std::make_unique<juce::AudioParameterFloat> (
    //     juce::ParameterID { param_ids::interval, 1 },
    //     "intv",
    //     juce::NormalisableRange { 10.0f, 500.0f, 0.01f, 0.405f },
    //     100.0f,
    //     juce::AudioParameterFloatAttributes().withStringFromValueFunction (ms)));

    // layout.add (
    //     std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { param_ids::pitch, 1 },
    //                                                  param_ids::pitch,
    //                                                  juce::NormalisableRange { -12.0f, 12.0f, 0.1f, 1.0f },
    //                                                  0.0f,
    //                                                  juce::AudioParameterFloatAttributes().withStringFromValueFunction (
    //                                                      [] (auto value, auto)
    //                                                      {
    //                                                          constexpr auto unit = " st";
    //                                                          return juce::String { value, 1 } + unit;
    //                                                      })));

    // layout.add (std::make_unique<juce::AudioParameterFloat> (
    //     juce::ParameterID { param_ids::grainPos, 1 },
    //     "pos",
    //     juce::NormalisableRange { 10.0f, 500.0f, 1.0f, 0.405f },
    //     100.0f,
    //     juce::AudioParameterFloatAttributes().withStringFromValueFunction (ms)));

    // layout.add (std::make_unique<juce::AudioParameterFloat> (
    //     juce::ParameterID { param_ids::grainSize, 1 },
    //     "size",
    //     juce::NormalisableRange { 10.0f, 500.0f, 0.01f, 0.405f },
    //     100.0f,
    //     juce::AudioParameterFloatAttributes().withStringFromValueFunction (ms)));

    // layout.add (std::make_unique<juce::AudioParameterFloat> (
    //     juce::ParameterID { param_ids::width, 1 },
    //     param_ids::width,
    //     juce::NormalisableRange { 0.0f, 100.0f, 0.01f, 1.0f },
    //     50.0,
    //     juce::AudioParameterFloatAttributes().withStringFromValueFunction (percentage)));

    // layout.add (std::make_unique<juce::AudioParameterFloat> (
    //     juce::ParameterID { param_ids::gain, 1 },
    //     "vol",
    //     juce::NormalisableRange { -36.0f, 12.0f, 0.1f, 2.4f },
    //     0.0f,
    //     juce::AudioParameterFloatAttributes().withStringFromValueFunction (
    //         [] (auto value, auto)
    //         {
    //             // Format the number to always display two digits like "0.1 dB", "10 dB".
    //             constexpr auto unit = " dB";

    //             if (auto v { std::round (value * 10.0f) / 10.0f }; -10.0f < v && v < 10.0f)
    //                 return juce::String { v, 1 } + unit;

    //             return juce::String { std::round (value) } + unit;
    //         })));

    return layout;
}

PluginProcessor::PluginProcessor()
    : AudioProcessor (BusesProperties()
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
    , apvts (*this, &undoManager, "Parameters", createParameterLayout())
{
    // for (RNBO::ParameterIndex i = 0; i < rnboObject.getNumParameters(); ++i)
    for (RNBO::ParameterIndex i = 0; i < 2; ++i)
    {
        RNBO::ParameterInfo info;
        rnboObject.getParameterInfo (i, &info);

        if (info.visible)
        {
            auto paramID = juce::String (rnboObject.getParameterId (i));
            // Each apvts parameter id and range must be the same as the rnbo param object's.
            // If you hit this assertion then you need to fix the incorrect id in param_ids.h.
            jassert (apvts.getParameter (paramID) != nullptr);

            // If you hit these assertions then you need to fix the incorrect apvts
            // parameter range in createParameterLayout().
            jassert (juce::approximatelyEqual (static_cast<float> (info.min), apvts.getParameterRange (paramID).start));
            jassert (juce::approximatelyEqual (static_cast<float> (info.max), apvts.getParameterRange (paramID).end));

            apvtsParamIdToRnboParamIndex[paramID] = i;

            apvts.addParameterListener (paramID, this);
            rnboObject.setParameterValue (i, apvts.getRawParameterValue (paramID)->load());
        }
    }
}

const juce::String PluginProcessor::getName() const { return JucePlugin_Name; }

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PluginProcessor::getTailLengthSeconds() const { return 0.0; }

int PluginProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram() { return 0; }

void PluginProcessor::setCurrentProgram (int index) { juce::ignoreUnused (index); }

const juce::String PluginProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rnboObject.prepareToProcess (sampleRate, static_cast<size_t> (samplesPerBlock));
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    rnboObject.process (buffer.getArrayOfWritePointers(),
                        static_cast<RNBO::Index> (buffer.getNumChannels()),
                        buffer.getArrayOfWritePointers(),
                        static_cast<RNBO::Index> (buffer.getNumChannels()),
                        static_cast<RNBO::Index> (buffer.getNumSamples()));
}

bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this, apvts, undoManager); // NOLINT
}

void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos (destData, true);
    apvts.state.writeToStream (mos);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (const auto tree = juce::ValueTree::readFromData (data, static_cast<size_t> (sizeInBytes)); tree.isValid())
        apvts.replaceState (tree);
}

void PluginProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    rnboObject.setParameterValue (apvtsParamIdToRnboParamIndex[parameterID], newValue);
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor(); // NOLINT
}
