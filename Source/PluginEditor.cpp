#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    osc1Group = new GroupComponent("Osc1", "Osc1");
    addAndMakeVisible(osc1Group);
    
    osc2Group = new GroupComponent("Osc2", "Osc2");
    addAndMakeVisible(osc2Group);
    
    evn1Group = new GroupComponent("Env1", "Env1");
    addAndMakeVisible(evn1Group);
    
    env2Group = new GroupComponent("Env2", "Env2");
    addAndMakeVisible(env2Group);
    
    setSize (300, 300);
    
    osc1AttackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1AttackSlider.setRange(0.1f, 500.0f);
    osc1AttackSlider.setValue(0.1f);
    osc1AttackSlider.addListener(this);
    osc1AttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc1AttackSlider);
    
    osc1AttackLabel.setText("A", dontSendNotification);
    addAndMakeVisible(osc1AttackLabel);
    
    osc1AttackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env1_attack", osc1AttackSlider);
    
    osc1DecaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1DecaySlider.setRange(0.1f, 1000.f);
    osc1DecaySlider.setValue(0.1f);
    osc1DecaySlider.addListener(this);
    osc1DecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc1DecaySlider);
    
    osc1DecayLabel.setText("D", dontSendNotification);
    addAndMakeVisible(osc1DecayLabel);
    
    osc1DecayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env1_decay", osc1DecaySlider);


    osc1SustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1SustainSlider.setRange(0.1f, 1000.f);
    osc1SustainSlider.setValue(0.1f);
    osc1SustainSlider.addListener(this);
    osc1SustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc1SustainSlider);
    
    osc1SustainLabel.setText("S", dontSendNotification);
    addAndMakeVisible(osc1SustainLabel);
    
    osc1SustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env1_sustain", osc1SustainSlider);

    
    osc1ReleaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc1ReleaseSlider.setRange(0.1f, 1000.f);
    osc1ReleaseSlider.setValue(0.1f);
    osc1ReleaseSlider.addListener(this);
    osc1ReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc1ReleaseSlider);
    
    osc1ReleaseLabel.setText("R", dontSendNotification);
    addAndMakeVisible(osc1ReleaseLabel);
    
    osc1ReleaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env1_release", osc1ReleaseSlider);

    
    /*-----------*/
    
    osc2AttackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2AttackSlider.setRange(0.1f, 500.0f);
    osc2AttackSlider.setValue(0.1f);
    osc2AttackSlider.addListener(this);
    osc2AttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc2AttackSlider);
    
    osc2AttackLabel.setText("A", dontSendNotification);
    addAndMakeVisible(osc2AttackLabel);
    
    osc2AttackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env2_attack", osc2AttackSlider);

    
    osc2DecaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2DecaySlider.setRange(0.1f, 500.0f);
    osc2DecaySlider.setValue(0.1f);
    osc2DecaySlider.addListener(this);
    osc2DecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc2DecaySlider);
    
    osc2DecayLabel.setText("D", dontSendNotification);
    addAndMakeVisible(osc2DecayLabel);
    
    osc2DecayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env2_decay", osc2DecaySlider);

    
    osc2SustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2SustainSlider.setRange(0.1f, 500.0f);
    osc2SustainSlider.setValue(0.1f);
    osc2SustainSlider.addListener(this);
    osc2SustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc2SustainSlider);
    
    osc2SustainLabel.setText("S", dontSendNotification);
    addAndMakeVisible(osc2SustainLabel);
    
    osc2SustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env2_sustain", osc2SustainSlider);

    
    osc2ReleaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    osc2ReleaseSlider.setRange(0.1f, 500.0f);
    osc2ReleaseSlider.setValue(0.1f);
    osc2ReleaseSlider.addListener(this);
    osc2ReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&osc2ReleaseSlider);
    
    osc2ReleaseLabel.setText("R", dontSendNotification);
    addAndMakeVisible(osc2ReleaseLabel);
    
    osc2ReleaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "env2_release", osc2ReleaseSlider);

    
    osc1WaveFormComboBox.addItem ("Sinus", 1);
    osc1WaveFormComboBox.addItem ("Square", 2);
    osc1WaveFormComboBox.addItem ("Triangle", 3);
    osc1WaveFormComboBox.addItem ("Saw", 4);
    osc1WaveFormComboBox.addItem ("Noise", 5);
   
    osc1WaveFormComboBox.setSelectedId (1);
    osc1WaveFormComboBox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (osc1WaveFormComboBox);
    
    osc1ComboBoxTree = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "osc1_waveform", osc1WaveFormComboBox);
    
    osc2WaveFormComboBox.addItem ("Sinus", 1);
    osc2WaveFormComboBox.addItem ("Square", 2);
    osc2WaveFormComboBox.addItem ("Triangle", 3);
    osc2WaveFormComboBox.addItem ("Saw", 4);
    osc2WaveFormComboBox.addItem ("Noise", 5);
    
    osc2WaveFormComboBox.setSelectedId (1);
    osc2WaveFormComboBox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (osc2WaveFormComboBox);
    
    osc2ComboBoxTree = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "osc2_waveform", osc2WaveFormComboBox);
    
    osc1MuteButton.setButtonText ("Mute");
    osc1MuteButton.setToggleState (false, dontSendNotification);
    osc1MuteButtonTree = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "osc1_mute", osc1MuteButton);
    
    addAndMakeVisible(osc1MuteButton);
    
    osc2MuteButton.setButtonText ("Mute");
    osc2MuteButton.setToggleState (false, dontSendNotification);
    osc2MuteButtonTree = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "osc2_mute", osc2MuteButton);
    
    addAndMakeVisible(osc2MuteButton);
}

void Slider::Listener::sliderValueChanged(Slider* slider)
{
    
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
    
}

//==============================================================================
void SynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    osc1Group->setBounds (5, 30, 140, 110);
    osc1WaveFormComboBox.setBounds (20, 60, 90, 18);
    osc1MuteButton.setBounds(20, 90, 90, 18);

    osc2Group->setBounds (155, 30, 140, 110);
    osc2WaveFormComboBox.setBounds (170, 60, 90, 18);
    osc2MuteButton.setBounds(170, 90, 90, 18);

    evn1Group->setBounds (5, 140, 140, 160);
    
    osc1AttackSlider.setBounds(10, 150, 40, 100);
    osc1DecaySlider.setBounds(40, 150, 40, 100);
    osc1SustainSlider.setBounds(70, 150, 40, 100);
    osc1ReleaseSlider.setBounds(100, 150, 40, 100);
    
    osc1AttackLabel.setBounds(20, 245, 20, 20);
    osc1DecayLabel.setBounds(50, 245, 20, 20);
    osc1SustainLabel.setBounds(80, 245, 20, 20);
    osc1ReleaseLabel.setBounds(110, 245, 20, 20);
    
    env1ActiveButton.setBounds(20, 270, 90, 18);

    env2Group->setBounds (155, 140, 140, 160);
    
    osc2AttackSlider.setBounds(160, 150, 40, 100);
    osc2DecaySlider.setBounds(190, 150, 40, 100);
    osc2SustainSlider.setBounds(220, 150, 40, 100);
    osc2ReleaseSlider.setBounds(250, 150, 40, 100);
    
    osc2AttackLabel.setBounds(170, 245, 20, 20);
    osc2DecayLabel.setBounds(200, 245, 20, 20);
    osc2SustainLabel.setBounds(230, 245, 20, 20);
    osc2ReleaseLabel.setBounds(260, 245, 20, 20);
    
    env2ActiveButton.setBounds(170, 270, 90, 18);

}

void SynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

}
