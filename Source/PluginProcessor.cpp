/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThreadingBasicsAudioProcessor::ThreadingBasicsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ThreadingBasicsAudioProcessor::~ThreadingBasicsAudioProcessor()
{
}

//==============================================================================
const juce::String ThreadingBasicsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ThreadingBasicsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ThreadingBasicsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ThreadingBasicsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ThreadingBasicsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ThreadingBasicsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ThreadingBasicsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ThreadingBasicsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ThreadingBasicsAudioProcessor::getProgramName (int index)
{
    return {};
}

void ThreadingBasicsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ThreadingBasicsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	dsp::ProcessSpec spec;
	
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();
	
    outBuffer.setSize (spec.numChannels, spec.maximumBlockSize);
    outBuffer.clear ();
    
	processorSwitch.prepare(spec);
}

void ThreadingBasicsAudioProcessor::releaseResources()
{
	processorSwitch.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ThreadingBasicsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void ThreadingBasicsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	dsp::AudioBlock<float> block{ buffer };
    dsp::AudioBlock<float> outBlock{ dsp::AudioBlock<float> (outBuffer).getSubBlock(0, buffer.getNumSamples()) };
    outBlock.clear();
    
    processorSwitch.process(dsp::ProcessContextNonReplacing<float>(block, outBlock));
    
    buffer.clear ();
    block.copyFrom (outBlock);
}

//==============================================================================
bool ThreadingBasicsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ThreadingBasicsAudioProcessor::createEditor()
{
    return new ThreadingBasicsAudioProcessorEditor (*this);
}

//==============================================================================
void ThreadingBasicsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ThreadingBasicsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ThreadingBasicsAudioProcessor();
}

void ThreadingBasicsAudioProcessor::loadFx(FxType fx)
{
    switch (fx)
    {
        case FxType::SimpleDelay:
            processorSwitch.setNextProcessor(std::make_unique<SimpleDelay> ());
            break;
        case FxType::SimpleFilter:
            processorSwitch.setNextProcessor(std::make_unique<SimpleFilter> ());
            break;
        default:
            processorSwitch.setNextProcessor({});
            break;
    }
}
