/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EsreverAudioProcessor::EsreverAudioProcessor() :
_lengthParam (nullptr),
_wetParam (nullptr),
_recordPosition(0),
_playbackPosition(0),
_useFirstBuffer(true)
{
    
    addParameter (_lengthParam  = new AudioParameterInt ("length",  "Length", 50, 5000, 1000));
    addParameter (_wetParam = new AudioParameterFloat ("wet", "Wet", 0.0f, 1.0f, 0.5f));
    
    _firstSampleBuffer.setSize(2, (float)(_lengthParam->get())/1000*44100);
    _secondSampleBuffer.setSize(2, (float)(_lengthParam->get())/1000*44100);
    _firstSampleBuffer.clear();
    _secondSampleBuffer.clear();
}

EsreverAudioProcessor::~EsreverAudioProcessor()
{
}

//==============================================================================
const String EsreverAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EsreverAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EsreverAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double EsreverAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EsreverAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EsreverAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EsreverAudioProcessor::setCurrentProgram (int index)
{
}

const String EsreverAudioProcessor::getProgramName (int index)
{
    return String();
}

void EsreverAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EsreverAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void EsreverAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EsreverAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void EsreverAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    if(_lengthParam->get()*44.1 > _firstSampleBuffer.getNumSamples()+ 100 || _lengthParam->get()*44.1 < _firstSampleBuffer.getNumSamples()- 100){
        auto newBufferSize = _lengthParam->get()*44.1;
        _firstSampleBuffer.setSize(2, newBufferSize);
        _secondSampleBuffer.setSize(2, newBufferSize);
        _firstSampleBuffer.clear();
        _secondSampleBuffer.clear();
        return;
    }
    
    
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto numberOfSamples = buffer.getNumSamples();
    AudioSampleBuffer *sampleBuffer;
    AudioSampleBuffer *playBackBuffer;
    
    if(_useFirstBuffer){
        sampleBuffer = &_firstSampleBuffer;
        playBackBuffer = &_secondSampleBuffer;
        
    }else{
        sampleBuffer = &_secondSampleBuffer;
        playBackBuffer = &_firstSampleBuffer;
    }
    
    if(_recordPosition + numberOfSamples >= sampleBuffer->getNumSamples()){
        sampleBuffer->reverse(0, sampleBuffer->getNumSamples());
        auto swap = sampleBuffer;
        sampleBuffer = playBackBuffer;
        playBackBuffer = swap;
        _useFirstBuffer = !_useFirstBuffer;
        _playbackPosition = 0;
        _recordPosition = 0;
    }
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {

        sampleBuffer->copyFrom(channel, _recordPosition, buffer, channel, 0, numberOfSamples);
        const float* playBackData = playBackBuffer->getReadPointer(channel);
        float* channelData = buffer.getWritePointer (channel);

        for(int i = 0; i < numberOfSamples; i++){
            channelData[i] = (1-_wetParam->get()) * channelData[i] + _wetParam->get() * playBackData[_playbackPosition + i];
        }

//        buffer.copyFrom(channel, 0, *playBackBuffer, channel, _playbackPosition, numberOfSamples);
    }
    _recordPosition += numberOfSamples;
    _playbackPosition += numberOfSamples;
    
    
}

//==============================================================================
bool EsreverAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EsreverAudioProcessor::createEditor()
{
    return new EsreverAudioProcessorEditor (*this);
}

//==============================================================================
void EsreverAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EsreverAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EsreverAudioProcessor();
}
