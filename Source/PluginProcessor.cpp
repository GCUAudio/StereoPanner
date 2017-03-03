/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

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
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

StereoPannerAudioProcessor::~StereoPannerAudioProcessor()
{
}

//==============================================================================
const String StereoPannerAudioProcessor::getName() const
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

const String StereoPannerAudioProcessor::getProgramName (int index)
{
    return String();
}

void StereoPannerAudioProcessor::changeProgramName (int index, const String& newName)
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
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void StereoPannerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Retrieve the total number of samples in the buffer for this block
    const  int numSamples = buffer.getNumSamples();
    
    // channelDataL and channelDataR are pointers to arrays of length numSamples which // contain the audio for one channel. You repeat this for each channel
    float *channelDataL = buffer.getWritePointer(0);
    float *channelDataR = buffer.getWritePointer(1);
    
    // calculate p’
    float pDash = (panPosition + 1.0) / 2.0;
    
    // Loop runs from 0 to number of samples in the block
    for (int i = 0; i < numSamples; ++i) {
        
        // Simple linear panning algorithm where:
        channelDataL[i] = channelDataL[i] * (1.0 - pDash);
        channelDataR[i] = channelDataR[i] * pDash;
    }
}

//==============================================================================
bool StereoPannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoPannerAudioProcessor::createEditor()
{
    return new StereoPannerAudioProcessorEditor (*this);
}

//==============================================================================
void StereoPannerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StereoPannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoPannerAudioProcessor();
}
