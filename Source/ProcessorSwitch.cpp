/*
  ==============================================================================

    ProcessorSwitch.cpp
    Created: 23 Oct 2023 11:40:14am
    Author:  HFM

  ==============================================================================
*/

#include "ProcessorSwitch.h"

ProcessorSwitch::ProcessorSwitch()
{

}

void ProcessorSwitch::setNextProcessor(std::unique_ptr<ProcessorBase> processor)
{
    /// @TODO – prepare processor
    
    /// @TODO – move processor to nextProcessor and set flag
	
    /// @TODO – maybe this is a good point to clear garbage from time to time
}

void ProcessorSwitch::process(const Context &context)
{
    // switching effects on audio processor, see updateProcessorPointers
    updateProcessorPointers ();

	using Block = dsp::AudioBlock<float>;
	using Buffer = AudioBuffer<float>;

	auto& inputBlock = context.getInputBlock ();
    auto& outputBlock = context.getOutputBlock ();

    const auto numSamples = (int)outputBlock.getNumSamples();

    Block currentBlock{ currentBuffer };
    currentBlock = currentBlock.getSubBlock(0, numSamples);
    currentBlock.clear ();
    
    Block lastBlock{ lastBuffer };
    lastBlock = lastBlock.getSubBlock(0, inputBlock.getNumSamples());
    lastBlock.clear ();
    
    /// @TODO –  process currentProcessor

    // if necessary fade from currentProcessor to nextProcessor
    if (isCrossfading ())
	{
        /// @TODO process lastProcessor

        /// @TODO fade between lastBlock and currentBlock by iterating over channels and samples.
    }
    else
    {
        // othewise just copy currentBlock to outputBlock
        outputBlock.copyFrom (currentBlock);
    }
}

void ProcessorSwitch::prepare(const dsp::ProcessSpec &specs)
{
    /// @TODO store specs and prepare transitionGain, lastBuffer, currentBuffer and, if not nullptr, next and currentProcessor
}

void ProcessorSwitch::reset()
{
}

void ProcessorSwitch::clearGarbage()
{
	JUCE_ASSERT_MESSAGE_THREAD
	garbage.clear ();
}

bool ProcessorSwitch::isCrossfading() const
{
	return transitionGain.isSmoothing();
}

void ProcessorSwitch::updateProcessorPointers()
{
    /** @TODO if nextProcessorChanged flag is set
        - gain lock
        - clear lastProcessors
        - update transitionGain so it starts a new transition from 0. to 1.
        - move currentProcessor to lastProcessor
        - move nextProcessor to currentProcessor
     */
}
