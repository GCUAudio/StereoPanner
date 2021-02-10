/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StereoPannerAudioProcessor::StereoPannerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
   // Adds the threshold parameter to the AudioProcessor
   panPosition = new juce::AudioParameterFloat("panPosition", "Pan Position", -1.0f, 1.0f, 0.0f); // (1)
   addParameter(panPosition); 

   algortihmChoice = new juce::AudioParameterChoice("algortihmChoice", "Choose panning", { "Linear", "Constant" }, 0);
   addParameter(algortihmChoice);
}

StereoPannerAudioProcessor::~StereoPannerAudioProcessor()
{
}

//==============================================================================
const juce::String StereoPannerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StereoPannerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoPannerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoPannerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StereoPannerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoPannerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoPannerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoPannerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StereoPannerAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoPannerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void StereoPannerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StereoPannerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoPannerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StereoPannerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // calculate p’
    float pDash = (panPosition->get() + 1.0f) / 2.0f;

    // User choice
    int choice = algortihmChoice->getIndex();

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (channel == 0) // Left channel
            {
                channelData[i] = channelData[i] * (1.0 - pDash);
            }
            else // Right channel (or any other channel)
            {
                channelData[i] = channelData[i] * pDash;
            }
        }
    }

}

//==============================================================================
bool StereoPannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StereoPannerAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void StereoPannerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    juce::MemoryOutputStream stream(destData, true);
    stream.writeFloat(*panPosition);

}

void StereoPannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    juce::MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);
    *panPosition = stream.readFloat();

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoPannerAudioProcessor();
}
