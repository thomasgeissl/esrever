/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class EsreverAudioProcessor  :
public AudioProcessor
{
public:
    //==============================================================================
    EsreverAudioProcessor();
    ~EsreverAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
    // Our parameters
    AudioParameterInt* _lengthParam;
    AudioParameterFloat* _fadeInLengthParam;
    AudioParameterFloat* _fadeOutLengthParam;
    AudioParameterFloat* _wetParam;

    int _recordPosition;
    int _playbackPosition;
    
    bool _useFirstBuffer;
    AudioSampleBuffer _firstSampleBuffer;
    AudioSampleBuffer _secondSampleBuffer;

    bool _playback;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EsreverAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
