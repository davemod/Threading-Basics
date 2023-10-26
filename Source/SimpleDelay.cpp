/*
  ==============================================================================

    SimpleDelay.cpp
    Created: 23 Oct 2023 10:58:05am
    Author:  HFM

  ==============================================================================
*/

#include "SimpleDelay.h"

SimpleDelay::SimpleDelay()
{
    dryWetMixer.setWetMixProportion(0.3f);
}

void SimpleDelay::process(const Context &context)
{
    delayLine.process(context);
    
    dryWetMixer.pushDrySamples(context.getInputBlock());
    dryWetMixer.mixWetSamples(context.getOutputBlock());
}

void SimpleDelay::prepare(const dsp::ProcessSpec &specs)
{
	delayLine.prepare(specs);
	dryWetMixer.prepare(specs);
    
    delayLine.setMaximumDelayInSamples (specs.sampleRate * 2.f);
    
    setDelay(48000.f);
}

void SimpleDelay::reset()
{
	delayLine.reset ();
	dryWetMixer.reset ();
}

void SimpleDelay::setDelayTime(float delayTime)
{
    jassertfalse;
}

void SimpleDelay::setDelay(float numSamples)
{
    delayLine.setDelay(numSamples);
}
