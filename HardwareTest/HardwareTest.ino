#include <Arduino.h>
#include <OneButton.h>

#define NUM_BTNS 3
#define BTN0_PIN 8
#define BTN1_PIN 9
#define BTN2_PIN 10

#define NUM_POTS 2
#define POT0_PIN A0
#define POT1_PIN A1

const OneButton btns[NUM_BTNS];

char buffer[100];

const int potPins[] = {POT0_PIN, POT1_PIN};
int potValues[NUM_POTS];
int oldPotValues[NUM_POTS];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

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

  for(short i = 0; i < NUM_POTS; i++)
  {
    potValues[i] = analogRead(potPins[i]);

    if(abs(oldPotValues[i] - potValues[i]) > 1)
    {
      oldPotValues[i] = potValues[i];
      
      sprintf(buffer, "Pot %d: %d", i, potValues[i]);
      Serial.println(buffer);
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
  Serial.println("BTN0 pressed");
}

void BTN0_Released()
{
  Serial.println("BTN0 released");
}

void BTN1_Pressed()
{
  Serial.println("BTN1 pressed");
}

void BTN1_Released()
{
  Serial.println("BTN1 released");
}

void BTN2_Pressed()
{
  Serial.println("BTN2 pressed");
}

void BTN2_Released()
{
  Serial.println("BTN2 released");
}
