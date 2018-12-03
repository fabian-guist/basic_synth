#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "../../Libraries/Maximilian/maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice();

    bool canPlaySound(SynthesiserSound* sound) override;
    void setAttack (float* attack);
    void setDecay (float* decay);
    void setSustain (float* sustain);
    void setRelease (float* release);
    void setWaveform(float* waveFormIndex);
    void setMute(float* mute);
    void setEnvActive(float* active);
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void playSineWave(AudioBuffer< float > &outputBuffer, int numSamples);
    void playSquareWave(AudioBuffer< float > &outputBuffer, int numSamples);
    void playTriangleWave(AudioBuffer< float > &outputBuffer, int numSamples);
    void playSawWave(AudioBuffer< float > &outputBuffer, int numSamples);
    void playNoiseWave(AudioBuffer< float > &outputBuffer, int numSamples);


private:
    Synthesiser mySynth;
    double level;
    double frequency;
    double selectedWaveformIndex = 0;
    maxiOsc osc1;
    maxiEnv env;
    
    bool isMute = false;
    bool envActive = false;

};
