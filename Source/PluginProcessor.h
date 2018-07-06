/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/

class VideoPlayerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================

	AudioProcessorValueTreeState params;
	
    VideoPlayerAudioProcessor();
    ~VideoPlayerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
	

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	AudioPlayHead::CurrentPositionInfo lastPosInfo;
	
	
	Value videoPath;
	void savePath(String path);
private:
	
	bool updateCurrentTimeInfoFromHost (AudioPlayHead::CurrentPositionInfo& posInfo)
	{
		if (auto* ph = getPlayHead())
		{
			AudioPlayHead::CurrentPositionInfo newTime;
			
			if (ph->getCurrentPosition (newTime))
			{
				posInfo = newTime;  // Successfully got the current time from the host.
				return true;
			}
		}
		
		// If the host fails to provide the current time, we'll just reset our copy to a default.
		lastPosInfo.resetToDefault();
		
		return false;
	}
	
	
		
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VideoPlayerAudioProcessor)
};



