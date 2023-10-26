/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThreadingBasicsAudioProcessorEditor::ThreadingBasicsAudioProcessorEditor (ThreadingBasicsAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    using Fx = ThreadingBasicsAudioProcessor::FxType;
    
    addAndMakeVisible(fxBox);
    
    fxBox.addItem ("Simple Delay", (int)Fx::SimpleDelay);
    fxBox.addItem ("Simple Filter", (int)Fx::SimpleFilter);

    fxBox.onChange = [&](){
        auto fx = static_cast<Fx>(fxBox.getSelectedId ());
        audioProcessor.loadFx (fx);
    };
}

ThreadingBasicsAudioProcessorEditor::~ThreadingBasicsAudioProcessorEditor()
{
}

//==============================================================================
void ThreadingBasicsAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ThreadingBasicsAudioProcessorEditor::resized()
{
    fxBox.setBounds (getLocalBounds().withSizeKeepingCentre(200, 30));
}
