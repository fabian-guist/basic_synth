#include "SynthVoice.h"

SynthVoice::SynthVoice()
: SynthesiserVoice()
, selectedWaveformIndex(0)
, env()
, isMute(false)
, envActive(false)

{
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound) 
{
    //check if sound can be cast to SynthSound, if not return false
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::setAttack (float* attack)
{
    env.setAttack((double)*attack);
}

void SynthVoice::setDecay (float* decay)
{
    env.setDecay((double)*decay);
}

void SynthVoice::setSustain (float* sustain)
{
    env.setSustain((double)*sustain);
}

void SynthVoice::setRelease (float* release)
{
    env.setRelease((double)*release);
}

void SynthVoice::setWaveform(float* waveFormIndex)
{
    selectedWaveformIndex = *waveFormIndex;
}

void SynthVoice::setMute(float* mute)
{
    if(*mute == 1.f){
        isMute = true;
    }else{
        isMute = false;
    }
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{    
    //correalation between key that i hit and frequency
    env.trigger = 1;
    level = velocity;
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    env.trigger = 0;
    allowTailOff = false;
    
    if(velocity == 0)
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue){
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue){
    
}

void SynthVoice::renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) 
{
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

void SynthVoice::playSineWave(AudioBuffer< float > &outputBuffer, int numSamples){
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

void SynthVoice::playSquareWave(AudioBuffer< float > &outputBuffer, int numSamples){
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

void SynthVoice::playTriangleWave(AudioBuffer< float > &outputBuffer, int numSamples){
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

void SynthVoice::playSawWave(AudioBuffer< float > &outputBuffer, int numSamples){
    for (int sample = 0; sample < numSamples; ++sample)
    {
        double theWave = osc1.saw(frequency) * level;
        double theSound = env.adsr(theWave, env.trigger) * level;
        
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, sample, theSound);
        }
    }
}

void SynthVoice::playNoiseWave(AudioBuffer< float > &outputBuffer, int numSamples){
    for (int sample = 0; sample < numSamples; ++sample)
    {
        double theWave = osc1.noise();
        double theSound = env.adsr(theWave, env.trigger) * level;
        
        
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, sample, theSound);
        }
    }
}
