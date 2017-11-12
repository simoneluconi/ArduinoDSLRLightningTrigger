#include <Timer.h>

#define LED 1 //Built-in LED
#define SHUTTER_PIN 0 // Optocoupler pin
#define TRIGGER_PIN 1 // Light Sensor
#define TRESHHOLD 30

int triggered = 0;
int normLight = 0;

Timer t;

void setup()
{
  pinMode(TRIGGER_PIN, INPUT); //Define the trigger pin as an input
  pinMode(SHUTTER_PIN, OUTPUT); //Define the shutter pin as an output
  pinMode(LED, OUTPUT); //Define the led pin as an output
  digitalWrite(LED, HIGH); //Turn the ledd on
  digitalWrite(SHUTTER_PIN, LOW); //Set the shutter pin to low / off / no voltage
  t.every(2000, UpdateLight); //Check the normal light condition
  normLight = analogRead(TRIGGER_PIN); //Read the start light level
}

void loop()
{
  triggered = analogRead(TRIGGER_PIN);  //Read the output from the LDR
  if ((triggered - normLight) >= TRESHHOLD)  //If light is detected, trigger the camera
  {
    digitalWrite(LED, LOW); //Turn off the led
    digitalWrite(SHUTTER_PIN, HIGH); //Trigger camera
    delay(1000);
    digitalWrite(SHUTTER_PIN, LOW);  //Reset camera trigger output for next photo
    digitalWrite(LED, HIGH); //Turn on the led
  }

  t.update();
}

void UpdateLight()
{
  normLight = analogRead(TRIGGER_PIN); //Update the normal light level
}

