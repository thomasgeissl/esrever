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
    addAndMakeVisible (_lengthSlider = new ParameterSlider (*p._lengthParam));
    _lengthSlider->setSliderStyle (Slider::Rotary);
    _lengthSlider->setTextValueSuffix(" ms");
    
    addAndMakeVisible (_wetSlider = new ParameterSlider (*p._wetParam));
    _wetSlider->setSliderStyle (Slider::Rotary);
    
    _lengthLabel.attachToComponent (_lengthSlider, true);
    _lengthLabel.setText("Length", dontSendNotification);

    
    _wetLabel.attachToComponent (_wetSlider, true);
    _wetLabel.setText("Wet", dontSendNotification);
    
    
    setResizable(false, false);
    setSize(400, 200);
    startTimerHz (30);
    
    auto lookAndFeel = new LookAndFeel_V4();
    setLookAndFeel(lookAndFeel);
}

EsreverAudioProcessorEditor::~EsreverAudioProcessorEditor()
{
}

//==============================================================================
void EsreverAudioProcessorEditor::paint (Graphics& g)
{
    g.setColour (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll();
}

void EsreverAudioProcessorEditor::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (8));
    Rectangle<int> lengthArea(r.getX(), r.getY(), r.getWidth(), r.getHeight()/2);
    Rectangle<int> wetArea(r.getX(), r.getY()+r.getHeight()/2, r.getWidth(), r.getHeight()/2);
    
    _lengthSlider->setBounds(lengthArea.removeFromRight(lengthArea.getWidth()/4*3));
    _wetSlider->setBounds(wetArea.removeFromRight(wetArea.getWidth()/4*3));
}
void EsreverAudioProcessorEditor::timerCallback(){

}
