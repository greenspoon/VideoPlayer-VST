/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VideoPlayerAudioProcessorEditor  : public AudioProcessorEditor, private Timer, private Value::Listener
{
public:
    VideoPlayerAudioProcessorEditor (VideoPlayerAudioProcessor&);
    ~VideoPlayerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	

private:
	String videoPath;
    VideoPlayerAudioProcessor& processor;
	VideoComponent myVideoComponent;
	TextButton openFileButton;
	Label pathLabel;
	Label infoLabel;
	void openFile();
	void updateInfo();
	void timerCallback() override;
	void valueChanged(juce::Value &value) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VideoPlayerAudioProcessorEditor)
};
