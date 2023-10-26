/*
  ==============================================================================

    SimpleDelay.h
    Created: 23 Oct 2023 10:58:05am
    Author:  HFM

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ProcessorBase.h"


class SimpleDelay : public ProcessorBase
{
public:
    SimpleDelay ();
    
    void process(const Context& context) override;
	void prepare(const dsp::ProcessSpec& specs) override;
	void reset() override;

	void setDelayTime (float delayTime);
    void setDelay (float samples);
    
private:
    dsp::ProcessSpec specs{ 0., 0, 0 };
    
	dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Linear> delayLine;
	dsp::DryWetMixer<float> dryWetMixer{ 1 };
};
