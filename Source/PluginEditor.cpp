/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class EsreverAudioProcessorEditor::ParameterSlider :
public Slider,
private Timer
{
public:
    ParameterSlider (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
    {
        setRange (0.0, 1.0, 0.0);
        startTimerHz (30);
        updateSliderPos();
    }
    
    void valueChanged() override
    {
        param.setValueNotifyingHost ((float) Slider::getValue());
    }
    
    void timerCallback() override       { updateSliderPos(); }
    
    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }
    
    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }
    
    AudioProcessorParameter& param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};

//==============================================================================
EsreverAudioProcessorEditor::EsreverAudioProcessorEditor (EsreverAudioProcessor& p) :
AudioProcessorEditor (&p),
processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // add some sliders..
    addAndMakeVisible (_lengthSlider = new ParameterSlider (*p._lengthParam));
    _lengthSlider->setSliderStyle (Slider::Rotary);
    
    addAndMakeVisible (_wetSlider = new ParameterSlider (*p._wetParam));
    _wetSlider->setSliderStyle (Slider::Rotary);
    
    // add some labels for the sliders..
    _lengthLabel.attachToComponent (_lengthSlider, false);
    _lengthLabel.setFont (Font (11.0f));
    _lengthLabel.setColour(Label::textColourId,Colours::black);

    
    _wetLabel.attachToComponent (_wetSlider, false);
    _wetLabel.setFont (Font (11.0f));
    _wetLabel.setColour(Label::textColourId,Colours::black);
    
    setResizable(true, true);
    setSize (400, 300);
    startTimerHz (30);
    
    setLookAndFeel(new LookAndFeel_V2());
}

EsreverAudioProcessorEditor::~EsreverAudioProcessorEditor()
{
}

//==============================================================================
void EsreverAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::whitesmoke);    
}

void EsreverAudioProcessorEditor::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (8));
    
    r.removeFromTop (30);
    Rectangle<int> sliderArea (r.removeFromTop (50));
    _lengthSlider->setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 2)));
    _wetSlider->setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
}
void EsreverAudioProcessorEditor::timerCallback(){

}
