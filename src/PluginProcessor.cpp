

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"
#include "ParamIDs.h"
#include "PluginEditor.h"
#include "RNBO_Types.h"
#include "Units.h"

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::wet, 1 },
        "Wet",
        juce::NormalisableRange { 0.0f, 1.0f, 0.001f, 1.0f },
        0.5f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (units::percentage)));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::freq, 1 },
        "Freq",
        juce::NormalisableRange { -100.0f, 100.0f, 0.01f, 1.0f },
        100.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (units::Hz)));

    layout.add (
        std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { param_ids::ratio, 1 },
                                                     "Ratio",
                                                     juce::NormalisableRange { 1.0f, 32.0f, 0.01f, 1.0f },
                                                     0.0f,
                                                     juce::AudioParameterFloatAttributes().withStringFromValueFunction (
                                                         [] (auto value, auto)
                                                         {
                                                             constexpr auto unit = " x";
                                                             return juce::String { value, 2 } + unit;
                                                         })));

    layout.add (
        std::make_unique<juce::AudioParameterBool> (juce::ParameterID { param_ids::subharmonic, 1 }, "Sub", false));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::feedback, 1 },
        "Fb",
        juce::NormalisableRange { 0.0f, 0.999f, 0.001f, 1.0f },
        0.5f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (units::percentage)));

    layout.add (
        std::make_unique<juce::AudioParameterBool> (juce::ParameterID { param_ids::pitchHold, 1 }, "Hold", false));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { param_ids::pitchThresh, 1 },
                                                             "Thresh",
                                                             juce::NormalisableRange { 0.f, 1.f, 0.01f, 0.405f },
                                                             0.1f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::pitchEnv, 1 },
        param_ids::pitchEnv,
        juce::NormalisableRange { 0.f, 1000.0f, 0.01f, 0.405f },
        1.f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (units::ms)));

    layout.add (
        std::make_unique<juce::AudioParameterBool> (juce::ParameterID { param_ids::pitchFollow, 1 }, "Follow", false));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { param_ids::ampEnv, 1 },
        param_ids::ampEnv,
        juce::NormalisableRange { 0.f, 1000.0f, 0.01f, 0.405f },
        0.1f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction (units::ms)));

    layout.add (
        std::make_unique<juce::AudioParameterBool> (juce::ParameterID { param_ids::ampMod, 1 }, "AM", false));

    return layout;
}

PluginProcessor::PluginProcessor()
    : AudioProcessor (BusesProperties()
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
    , apvts (*this, &undoManager, "Parameters", createParameterLayout())
{
    // for (RNBO::ParameterIndex i = 0; i < rnboObject.getNumParameters(); ++i)
    for (RNBO::ParameterIndex i = 0; i < 11; ++i) // only retrieve first 11 exposed parameters from the main patch
    {
        RNBO::ParameterInfo info;
        rnboObject.getParameterInfo (i, &info);

        if (info.visible)
        {
            auto paramID = juce::String (rnboObject.getParameterId (i));
            std::cout << paramID << std::endl;
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
