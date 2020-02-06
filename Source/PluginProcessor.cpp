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
	// Adds the parameters to the AudioProcessor
	panPosition = new AudioParameterFloat("panPosition", "Pan Position", -1.0f, 1.0f, 0.0f); 
	constantPower = new AudioParameterBool("constantPower", "Constant Power", false); 
	addParameter(panPosition); 
	addParameter(constantPower);

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

const String StereoPannerAudioProcessor::getProgramName (int index)
{
    return {};
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

void StereoPannerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
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

	// Calculate out of for loop for efficiency
	const float PI = 3.14159265359f;
	float temp = panPosition->get() + 1.0f;
	float pDash = 0.0f;

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int i = 0; i < buffer.getNumSamples(); i++)
		{
			if (constantPower->get()) // If constant power is selected run code in these brackets
			{
				pDash = (temp * PI) / 4;

				if (channel == 0) // Left channel
				{
					channelData[i] = channelData[i] * cos(pDash);
				}
				else // Right channel (or any other channel)
				{
					channelData[i] = channelData[i] * sin(pDash);
				}
			}
			else // Otherwise run this code
			{
				pDash = temp / 2;

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
}

//==============================================================================
bool StereoPannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoPannerAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor(this);
}

//==============================================================================
void StereoPannerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	MemoryOutputStream stream(destData, true);
	stream.writeFloat(*panPosition);
	stream.writeBool(*constantPower);

}

void StereoPannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);
	*panPosition = stream.readFloat();
	*constantPower = stream.readBool();

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoPannerAudioProcessor();
}
