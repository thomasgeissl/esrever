/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EsreverAudioProcessorEditor::EsreverAudioProcessorEditor (EsreverAudioProcessor& p) :
AudioProcessorEditor (&p),
processor (p),
_lengthSlider(std::make_unique<ParameterSlider>(*p._lengthParam)),
_wetSlider(std::make_unique<ParameterSlider>(*p._wetParam))
{
    addAndMakeVisible (_lengthSlider.get());
    _lengthSlider->setSliderStyle (Slider::Rotary);
    _lengthSlider->setTextValueSuffix(" ms");
    
    addAndMakeVisible (_wetSlider.get());
    _wetSlider->setSliderStyle (Slider::Rotary);
    
    _lengthLabel.attachToComponent (_lengthSlider.get(), true);
    _lengthLabel.setText("Length", dontSendNotification);

    
    _wetLabel.attachToComponent (_wetSlider.get(), true);
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
    g.setColour (getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.fillAll();
    
    Rectangle<int> r(getLocalBounds());
    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));
    int width = (float)(processor._playbackPosition)/processor._ping.getNumSamples() * r.getWidth();
    int height = 5;
    g.drawRect(0, r.getHeight()-height, width, height);
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
    repaint();
}
