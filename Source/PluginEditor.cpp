/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VideoPlayerAudioProcessorEditor::VideoPlayerAudioProcessorEditor (VideoPlayerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
	
	pathLabel.setText("...", dontSendNotification);
	
	openFileButton.setButtonText("Open file");
	openFileButton.onClick =  [this] {
		openFile();
	};
	
	addAndMakeVisible(infoLabel);
	addAndMakeVisible(myVideoComponent);
	addAndMakeVisible(openFileButton);
	addAndMakeVisible(pathLabel);
	startTimer(10);
	processor.videoPath.addListener(this);
	
}

VideoPlayerAudioProcessorEditor::~VideoPlayerAudioProcessorEditor()
{
}

//==============================================================================
void VideoPlayerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}


bool playedFromHost = false;

void VideoPlayerAudioProcessorEditor::updateInfo() {
	String timeAsString(processor.lastPosInfo.timeInSeconds);
	String videoTimeAsString(myVideoComponent.getPlayPosition());
	String isPlayingString = processor.lastPosInfo.isPlaying ? "true" : "false";
	
	infoLabel.setText("Time/VideoTime: " + timeAsString + " / " + videoTimeAsString + ", isPlaying: " + isPlayingString , sendNotification);
}

//UPDATE TIMER
void VideoPlayerAudioProcessorEditor::timerCallback()
{
	updateInfo();
	
	if (processor.lastPosInfo.isPlaying) {
		if (playedFromHost == false) {
			myVideoComponent.setPlayPosition(processor.lastPosInfo.timeInSeconds);
		}
		myVideoComponent.play();
		playedFromHost = true;
	} else {
		if (playedFromHost == true) {
			myVideoComponent.stop();
			playedFromHost = false;
		}
		
	}
	repaint();
}

void VideoPlayerAudioProcessorEditor::valueChanged(juce::Value &value) {
//	videoPath = value.toString();
}

void VideoPlayerAudioProcessorEditor::resized()
{
	
	myVideoComponent.setBounds(0, 0, getWidth(), getHeight() - 30);
	
	openFileButton.setBounds(0, myVideoComponent.getY() + myVideoComponent.getHeight(), 150, 25);
	
	pathLabel.setBounds(openFileButton.getWidth() + 5, openFileButton.getY(), getWidth(), 25);
	
	infoLabel.setBounds(0, 0, getWidth(), 30);
}

void VideoPlayerAudioProcessorEditor::openFile() {
	FileChooser fileChooser ("Choose Video File");
	if (fileChooser.browseForFileToOpen()) {
		File resultFile = fileChooser.getResult();
		if (!resultFile.isDirectory()) {
			processor.savePath(videoPath);
			videoPath = resultFile.getFullPathName();
			pathLabel.setText(videoPath, sendNotification);
			myVideoComponent.load(resultFile);
		}
	}
	
}
