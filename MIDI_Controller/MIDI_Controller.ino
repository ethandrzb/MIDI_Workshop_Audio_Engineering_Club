#include <Arduino.h>
#include <MIDI.h>
#include <OneButton.h>

#define NUM_BTNS 3
#define BTN0_PIN 8
#define BTN1_PIN 9
#define BTN2_PIN 10

#define NUM_POTS 2
#define POT0_PIN A0
#define POT1_PIN A1

MIDI_CREATE_DEFAULT_INSTANCE();

const OneButton btns[NUM_BTNS];

char buffer[100];

const int potPins[] = {POT0_PIN, POT1_PIN};
int potValues[NUM_POTS];
int oldPotValues[NUM_POTS];

//#define DEBUG_SERIAL

void setup()
{
  // put your setup code here, to run once:
  #ifdef DEBUG_SERIAL
  Serial.begin(115200);
  #endif

  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Button setup
  btns[0].setup(BTN0_PIN, INPUT_PULLUP, true);
  btns[1].setup(BTN1_PIN, INPUT_PULLUP, true);
  btns[2].setup(BTN2_PIN, INPUT_PULLUP, true);

  btns[0].attachPress(&BTN0_Pressed);
  btns[0].attachLongPressStop(&BTN0_Released);
  btns[0].setPressTicks(20);

  btns[1].attachPress(&BTN1_Pressed);
  btns[1].attachLongPressStop(&BTN1_Released);
  btns[1].setPressTicks(20);

  btns[2].attachPress(&BTN2_Pressed);
  btns[2].attachLongPressStop(&BTN2_Released);
  btns[2].setPressTicks(20);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Update pots
  for(short i = 0; i < NUM_POTS; i++)
  {
    potValues[i] = analogRead(potPins[i]) >> 3;

    if(abs(oldPotValues[i] - potValues[i]) != 0)
    {
      #ifdef DEBUG_SERIAL
      sprintf(buffer, "Pot %d: %d", i, potValues[i]);
      Serial.println(buffer);
      #endif

      MIDI.sendControlChange(i + 1, potValues[i], 1);
      
      oldPotValues[i] = potValues[i];
    }
  }

  // Update buttons
  for(short i = 0; i < NUM_BTNS; i++)
  {
    btns[i].tick();
  }
}

void BTN0_Pressed()
{
  #ifdef DEBUG_SERIAL
  Serial.println("BTN0 pressed");
  #endif

  MIDI.sendNoteOn(60, 127, 1);
}

void BTN0_Released()
{
  #ifdef DEBUG_SERIAL
  Serial.println("BTN0 released");
  #endif

  MIDI.sendNoteOff(60, 127, 1);
}

void BTN1_Pressed()
{
  #ifdef DEBUG_SERIAL
  Serial.println("BTN1 pressed");
  #endif

  MIDI.sendNoteOn(63, 127, 1);
}

void BTN1_Released()
{
  #ifdef DEBUG_SERIAL
  Serial.println("BTN1 released");
  #endif

  MIDI.sendNoteOff(63, 127, 1);
}

void BTN2_Pressed()
{
  #ifdef DEBUG_SERIAL
  Serial.println("BTN2 pressed");
  #endif
  
  MIDI.sendNoteOn(67, 127, 1);
}

void BTN2_Released()
{
  #ifdef DEBUG_SERIAL
  Serial.println("BTN2 released");
  #endif

  MIDI.sendNoteOff(67, 127, 1);
}
