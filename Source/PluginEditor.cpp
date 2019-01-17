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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StereoPannerAudioProcessorEditor::StereoPannerAudioProcessorEditor ( StereoPannerAudioProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    sliderPanPosition.reset (new Slider ("new slider"));
    addAndMakeVisible (sliderPanPosition.get());
    sliderPanPosition->setRange (-1, 1, 0);
    sliderPanPosition->setSliderStyle (Slider::Rotary);
    sliderPanPosition->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderPanPosition->addListener (this);

    sliderPanPosition->setBounds (24, 24, 159, 168);

    togglePanningAlgorithm.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (togglePanningAlgorithm.get());
    togglePanningAlgorithm->setButtonText (TRANS("Constant Power"));
    togglePanningAlgorithm->addListener (this);

    togglePanningAlgorithm->setBounds (64, 216, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);//starts timer with interval of 200mS
    //[/Constructor]
}

StereoPannerAudioProcessorEditor::~StereoPannerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderPanPosition = nullptr;
    togglePanningAlgorithm = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StereoPannerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StereoPannerAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StereoPannerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderPanPosition.get())
    {
        //[UserSliderCode_sliderPanPosition] -- add your slider handling code here..
        processor.panPosition = sliderPanPosition->getValue();
        //[/UserSliderCode_sliderPanPosition]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void StereoPannerAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == togglePanningAlgorithm.get())
    {
        //[UserButtonCode_togglePanningAlgorithm] -- add your button handler code here..
        processor.constantPower = togglePanningAlgorithm->getToggleState();
        //[/UserButtonCode_togglePanningAlgorithm]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void StereoPannerAudioProcessorEditor::timerCallback()
{
    //exchange any data you want between UI elements and the Plugin "ourProcessor"
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StereoPannerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams=" StereoPannerAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor(p), processor(p)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000"/>
  <SLIDER name="new slider" id="6d5ba74f0492c1e4" memberName="sliderPanPosition"
          virtualName="" explicitFocusOrder="0" pos="24 24 159 168" min="-1.0"
          max="1.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="623ec6df99e7a96e" memberName="togglePanningAlgorithm"
                virtualName="" explicitFocusOrder="0" pos="64 216 150 24" buttonText="Constant Power"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
