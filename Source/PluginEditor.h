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
class SynthAudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override;
    void updateAssignSelf();
        
    void SetUpSlider(Slider& slider);



private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& processor;
    
    Slider osc1AttackSlider;
    Slider osc1DecaySlider;
    Slider osc1SustainSlider;
    Slider osc1ReleaseSlider;
    
    Slider osc2AttackSlider;
    Slider osc2DecaySlider;
    Slider osc2SustainSlider;
    Slider osc2ReleaseSlider;
    
    Label osc1AttackLabel;
    Label osc1DecayLabel;
    Label osc1SustainLabel;
    Label osc1ReleaseLabel;
    
    Label osc2AttackLabel;
    Label osc2DecayLabel;
    Label osc2SustainLabel;
    Label osc2ReleaseLabel;
        
    GroupComponent* osc1Group;
    GroupComponent* osc2Group;
    
    GroupComponent* evn1Group;
    GroupComponent* env2Group;
    
    ComboBox osc1WaveFormComboBox;
    ComboBox osc2WaveFormComboBox;
    
    ToggleButton osc1MuteButton;
    ToggleButton osc2MuteButton;
    
    ToggleButton env1ActiveButton;
    ToggleButton env2ActiveButton;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1AttackTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1DecayTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1SustainTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1ReleaseTree;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2AttackTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2DecayTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2SustainTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2ReleaseTree;

    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> osc1ComboBoxTree;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> osc2ComboBoxTree;
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> osc1MuteButtonTree;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> osc2MuteButtonTree;
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> env1ActiveButtonTree;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> env2ActiveButtonTree;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
