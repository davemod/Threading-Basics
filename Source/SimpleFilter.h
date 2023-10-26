/*
  ==============================================================================

    SimpleFilter.h
    Created: 23 Oct 2023 10:58:19am
    Author:  HFM

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ProcessorBase.h"


class SimpleFilter : public ProcessorBase
{
public:
	SimpleFilter ();
	
	void process(const Context& context) override;
	void prepare(const dsp::ProcessSpec& specs) override;
	void reset() override;

	// void setFilterType (dsp::IIR::Coefficients<float>::FilterType filterType);
	void setFilterParams (float frequency, float resonance);

private:
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients <float>> filter;
	dsp::ProcessSpec specs{ 0., 0, 0 };

	Atomic<float> freq{ 1400.f };
	Atomic<float> reso{ 1.f };
	
	// call this on your audio thread
	void updateFilter();
};
