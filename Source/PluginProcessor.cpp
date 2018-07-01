/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <sstream>
#include <string>


//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree (*this, nullptr)
#endif
{
    NormalisableRange<float> envParam (0.f, 5000);
    NormalisableRange<float> sustainParam(0.f, 1);
    NormalisableRange<float> osc1WaveformParam(0, 5);
    NormalisableRange<float> osc2WaveformParam(0, 5);
    
    NormalisableRange<float> oscMuteParam(0, 1);
    
    tree.createAndAddParameter("env1_attack", "Env1_attack", "Env1_attack", envParam, 1000, nullptr, nullptr);
    tree.createAndAddParameter("env1_decay", "Env1_decay", "Env1_decay", envParam, 1000, nullptr, nullptr);
    tree.createAndAddParameter("env1_sustain", "Env1_sustain", "Env1_sustain", sustainParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("env1_release", "Env1_release", "Env1_release", envParam, 1000, nullptr, nullptr);

    tree.createAndAddParameter("env2_attack", "Env2_attack", "Env2_attack", envParam, 1000, nullptr, nullptr);
    tree.createAndAddParameter("env2_decay", "Env2_decay", "Env2_decay", envParam, 1000, nullptr, nullptr);
    tree.createAndAddParameter("env2_sustain", "Env2_sustain", "Env2_sustain", sustainParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("env2_release", "Env2_release", "Env2_release", envParam, 1000, nullptr, nullptr);

    
    tree.createAndAddParameter("osc1_waveform", "Osc1_waveform", "Osc1_waveform", osc1WaveformParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("osc2_waveform", "Osc2_waveform", "Osc2_waveform", osc2WaveformParam, 0, nullptr, nullptr);
    
    tree.createAndAddParameter("osc1_mute", "Osc1_mute", "Osc1_mute", oscMuteParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("osc2_mute", "Osc2_mute", "Osc2_mute", oscMuteParam, 1, nullptr, nullptr);
    
    tree.createAndAddParameter("env1_active", "Env1_active", "Env1_active", oscMuteParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("env2_active", "Env2_active", "Env2_active", oscMuteParam, 0, nullptr, nullptr);

    
    //Initialize Tree
    tree.state = ValueTree("SynthTree");
    
    //clear voices from last key press before new key press
    synth1.clearVoices();
    synth2.clearVoices();
    
    
    //give 5 voices
    for(int i = 0; i < 5; i++)
    {
        // new SynthesiserVoice()??
        synth1.addVoice(new SynthVoice());
        synth2.addVoice(new SynthVoice());
    }
    synth1.clearSounds();
    synth1.addSound(new SynthSound());
    
    synth2.clearSounds();
    synth2.addSound(new SynthSound());
}

SynthAudioProcessor::~SynthAudioProcessor()
{
}

//==============================================================================
const String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    //ignore unused Samples from last key that we pressed
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    synth1.setCurrentPlaybackSampleRate(lastSampleRate);
    synth2.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for(int i = 0; i < synth1.getNumVoices(); i++)
    {
        if((voice1 = dynamic_cast<SynthVoice*>(synth1.getVoice(i))))
        {
            voice1->setAttack(tree.getRawParameterValue("env1_attack"));
            voice1->setDecay(tree.getRawParameterValue("env1_decay"));
            voice1->setSustain(tree.getRawParameterValue("env1_sustain"));
            voice1->setRelease(tree.getRawParameterValue("env1_release"));

            voice1->setWaveform(tree.getRawParameterValue("osc1_waveform"));
            
            voice1->setMute(tree.getRawParameterValue("osc1_mute"));
            
            voice1->setEnvActive(tree.getRawParameterValue("env1_active"));
        }
    }

    for(int i = 0; i < synth2.getNumVoices(); i++)
    {
        if((voice2 = dynamic_cast<SynthVoice*>(synth2.getVoice(i))))
        {
            voice1->setAttack(tree.getRawParameterValue("env2_attack"));
            voice1->setDecay(tree.getRawParameterValue("env2_decay"));
            voice1->setSustain(tree.getRawParameterValue("env2_sustain"));
            voice1->setRelease(tree.getRawParameterValue("env2_release"));
            
            voice2->setWaveform(tree.getRawParameterValue("osc2_waveform"));
            
            voice2->setMute(tree.getRawParameterValue("osc2_mute"));
            
            voice2->setEnvActive(tree.getRawParameterValue("env2_active"));

        }
    }

    
    buffer.clear();
    synth1.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    synth2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}
