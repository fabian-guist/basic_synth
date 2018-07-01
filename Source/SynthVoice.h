/*
  ==============================================================================

    SynthVoice.h
    Created: 14 May 2018 7:13:40pm
    Author:  Fabian Guist

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "../../Libraries/Maximilian/maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound* sound) override
    {
        //check if sound can be cast to SynthSound, if not return false
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void setAttack (float* attack)
    {
        env.setAttack((double)*attack);
    }
    
    void setDecay (float* decay)
    {
        env.setDecay((double)*decay);
    }
    
    void setSustain (float* sustain)
    {
        cout << *sustain << endl;
        env.setSustain((double)*sustain);
    }
    
    void setRelease (float* release)
    {
        env.setRelease((double)*release);
    }
    
    void setWaveform(float* waveFormIndex)
    {
        selectedWaveformIndex = *waveFormIndex;
    }
    
    void setMute(float* mute)
    {
        if(*mute == 1.f){
            isMute = true;
        }else{
            isMute = false;
        }
    }
    
    void setEnvActive(float* active)
    {
        if(*active == 1.f){
            envActive = true;
        }else{
            envActive = false;
        }
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        //correalation between key that i hit and frequency
        env.trigger = 1;
        
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    void stopNote(float velocity, bool allowTailOff) override
    {
        env.trigger = 0;
        allowTailOff = false;
        
        if(velocity == 0)
        {
            clearCurrentNote();
        }
    }
    
    void pitchWheelMoved(int newPitchWheelValue) override
    {
        
    }
    
    void controllerMoved(int controllerNumber, int newControllerValue) override
    {
        
    }
    
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override
    {
        setUpEnvelope(env);
        
        if(isMute == false){
            if(selectedWaveformIndex == 0)
            {
                playSineWave(outputBuffer, numSamples);
            }
            else if (selectedWaveformIndex == 1)
            {
                playSquareWave(outputBuffer, numSamples);
            }
            else if (selectedWaveformIndex == 2)
            {
                playTriangleWave(outputBuffer, numSamples);
            }
            else if (selectedWaveformIndex == 3)
            {
                playSawWave(outputBuffer, numSamples);
            }
            else if (selectedWaveformIndex == 4)
            {
                playNoiseWave(outputBuffer, numSamples);
            }
            else{
                playSineWave(outputBuffer, numSamples);
                
            }
        }
    }
    
    void playSineWave(AudioBuffer< float > &outputBuffer, int numSamples){
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.sinewave(frequency) * level;
            double theSound = env.adsr(theWave, env.trigger) * level;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, sample, theSound);
            }
        }
    }
    
    void playSquareWave(AudioBuffer< float > &outputBuffer, int numSamples){
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.square(frequency) * level;
            double theSound = env.adsr(theWave, env.trigger) * level;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, sample, theSound);
            }
        }
    }
    
    void playTriangleWave(AudioBuffer< float > &outputBuffer, int numSamples){
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.triangle(frequency) * level;
            double theSound = env.adsr(theWave, env.trigger) * level;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, sample, theSound);
            }
        }
    }
    
    void playSawWave(AudioBuffer< float > &outputBuffer, int numSamples){
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency) * level;
            double theSound = env.adsr(theWave, env.trigger) * level;
            //double filteredSound = filter1.lores(theSound, 100, 0.1);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, sample, theSound);
            }
        }
    }
    
    void playNoiseWave(AudioBuffer< float > &outputBuffer, int numSamples){
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.noise();
            double theSound = env.adsr(theWave, env.trigger) * level;
            //double filteredSound = filter1.lores(theSound, 100, 0.1);
            
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, sample, theSound);
            }
        }
    }
    
    void setUpEnvelope(maxiEnv &env){
        //env.setAttack(100);
        //env.setDecay(500);
        //env.setSustain(0.8);
        //env.setRelease(2000);
    }

private:
    Synthesiser mySynth;
    double level;
    double frequency;
    double selectedWaveformIndex = 0;
    maxiOsc osc1;
    maxiEnv env;
    maxiFilter filter1;
    
    bool isMute = false;
    bool envActive = false;

};
