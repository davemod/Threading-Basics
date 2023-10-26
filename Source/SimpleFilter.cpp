/*
  ==============================================================================

    SimpleFilter.cpp
    Created: 23 Oct 2023 10:58:19am
    Author:  HFM

  ==============================================================================
*/

#include "SimpleFilter.h"

SimpleFilter::SimpleFilter()
{
}

void SimpleFilter::process(const Context &context)
{
	updateFilter ();
	filter.process (context);
}

void SimpleFilter::prepare(const dsp::ProcessSpec &specs)
{
	this->specs = specs;
	filter.prepare(specs);
}

void SimpleFilter::reset()
{
	filter.reset ();
}

void SimpleFilter::setFilterParams(float frequency, float resonance)
{
	freq = frequency;
	reso = resonance;
}

void SimpleFilter::updateFilter ()
{
	*filter.state = *dsp::IIR::Coefficients<float>::makeLowPass (specs.sampleRate, freq.get (), reso.get ());
}
