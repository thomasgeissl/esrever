/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class EsreverAudioProcessorEditor  :
public AudioProcessorEditor,
public Timer
{
public:
    EsreverAudioProcessorEditor (EsreverAudioProcessor&);
    ~EsreverAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    class ParameterSlider :
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


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EsreverAudioProcessor& processor;
    std::unique_ptr<ParameterSlider> _lengthSlider, _wetSlider;
    Label _lengthLabel, _wetLabel, _debugLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EsreverAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
