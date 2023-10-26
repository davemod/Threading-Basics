/*
  ==============================================================================

    ProcessorSwitch.h
    Created: 23 Oct 2023 11:40:14am
    Author:  HFM

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ProcessorBase.h"
#include "SimpleDelay.h"
#include "SimpleFilter.h"

class ProcessorSwitch : public ProcessorBase
{
public:
	ProcessorSwitch ();

	void setNextProcessor (std::unique_ptr<ProcessorBase> processor);

	void process (const Context& context) override;
	void prepare (const dsp::ProcessSpec& specs) override;
	void reset () override;

private:
    dsp::ProcessSpec specs{ 0., 0, 0 };
	
	using ProcessorPtr = std::unique_ptr<ProcessorBase>;
	
	ProcessorPtr nextProcessor;
	ProcessorPtr currentProcessor;
	ProcessorPtr lastProcessor;
	
	Array<ProcessorPtr> garbage;
    
    void clearGarbage ();
	int garbageIndex{ 0 };
    
	// some really light weight lock used to switch pointers
	SpinLock switchLock;
	
	using ScopedLock = SpinLock::ScopedLockType;
	using ScopedTryLock = SpinLock::ScopedTryLockType;

	AudioBuffer<float> lastBuffer;
	AudioBuffer<float> currentBuffer;

	SmoothedValue<float> transitionGain{ 0.f };
	
	Atomic<bool> nextProcessorChanged;

	bool isCrossfading () const;
	void updateProcessorPointers ();
};
