/*
  ==============================================================================

    ProcessorBase.h
    Created: 23 Oct 2023 11:02:57am
    Author:  HFM

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ProcessorBase
{
public:
    virtual ~ProcessorBase () = default;
    
    using Context = dsp::ProcessContextNonReplacing<float>;
    
	virtual void process (const Context& context) = 0;
	virtual void prepare (const dsp::ProcessSpec& specs) = 0;
	virtual void reset () = 0;

private:
};
