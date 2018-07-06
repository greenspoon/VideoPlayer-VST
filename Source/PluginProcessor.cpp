/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VideoPlayerAudioProcessor::VideoPlayerAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
					   ),
	params(*this, nullptr),
	videoPath("videoPath")

{
	
	Identifier videoPathID("videoPath");
	params.state.setProperty(videoPathID, var(""), nullptr);
	videoPath.referTo(params.state.getPropertyAsValue(videoPathID, nullptr));
	
}



VideoPlayerAudioProcessor::~VideoPlayerAudioProcessor()
{
}

void VideoPlayerAudioProcessor::savePath(juce::String path) {
	videoPath.setValue(path);
}

//==============================================================================
const String VideoPlayerAudioProcessor::getName() const
{
    return "Video Player";
}

bool VideoPlayerAudioProcessor::acceptsMidi() const
{
    return true;
}

bool VideoPlayerAudioProcessor::producesMidi() const
{
    return false;
}

bool VideoPlayerAudioProcessor::isMidiEffect() const
{
    return false;
}

double VideoPlayerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VideoPlayerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VideoPlayerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VideoPlayerAudioProcessor::setCurrentProgram (int index)
{
}

const String VideoPlayerAudioProcessor::getProgramName (int index)
{
    return {};
}

void VideoPlayerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VideoPlayerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void VideoPlayerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VideoPlayerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VideoPlayerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
	
	
	updateCurrentTimeInfoFromHost(lastPosInfo);
	
	
//	buffer.clear();
	
//	MidiBuffer processedMidi;
//	int time;
//	MidiMessage m;
	
//	for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//	{
//		if (m.isNoteOn())
//		{
//			uint8 newVel = (uint8)noteOnVel;
//			m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
//		}
//		else if (m.isNoteOff())
//		{
//		}
//		else if (m.isAftertouch())
//		{
//		}
//		else if (m.isPitchWheel())
//		{
//		}
//		processedMidi.addEvent (m, time);
//	}
}



//==============================================================================
bool VideoPlayerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VideoPlayerAudioProcessor::createEditor()
{
    return new VideoPlayerAudioProcessorEditor (*this);
}

//==============================================================================
void VideoPlayerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	MemoryOutputStream stream (destData, true);
	params.state.writeToStream (stream);
}

void VideoPlayerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	MemoryInputStream stream (data, sizeInBytes, false);
	params.state.readFromStream (stream);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VideoPlayerAudioProcessor();
}


