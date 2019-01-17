/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class StereoPannerAudioProcessorEditor  : public AudioProcessorEditor,
                                          public Timer,
                                          public Slider::Listener,
                                          public Button::Listener
{
public:
    //==============================================================================
    StereoPannerAudioProcessorEditor ( StereoPannerAudioProcessor& p);
    ~StereoPannerAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    StereoPannerAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> sliderPanPosition;
    std::unique_ptr<ToggleButton> togglePanningAlgorithm;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoPannerAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
