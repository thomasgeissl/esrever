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
    class ParameterSlider;
    ScopedPointer<ParameterSlider> _lengthSlider, _wetSlider;
    Label _lengthLabel, _wetLabel, _debugLabel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EsreverAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EsreverAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
