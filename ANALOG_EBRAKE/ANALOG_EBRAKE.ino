// Analog eBrake-Handbrake
// PIN A0 to 10k pot output - Throttle Axis
// Use with Arduino ProMicro.
// Tested and working in DiRT RALLY + ASSETTO CORSA
// by AMSTUDIO
// 20.1.2017

// NachoChef 10/5/2017
// Adding additional support for more buttons. More buttons = more juice.
// Additional button code based off the `Arduino - Switch` and `JoystickButton` library example.
// Verified working on Windows 7, wired with a separate 10k pullup resistor on each pin.

#include <Joystick.h>

const int eBrakePin = A0;

// 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16 are available digital pins
// just enter the pins you're using below and everything else is automatic
// note this probably isn't the most efficient way to do anything
int myPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16};
const int numPins = sizeof(myPins)/sizeof(int);
int btn_state[numPins];
int previous_state[numPins];

void setup()
{
   pinMode(eBrakePin, INPUT); 
   
   int i;
   for (i = 0; i < numPins; i++)
   {
      pinMode(myPins[i], INPUT_PULLUP);
      btn_state[i] = LOW;
      previous_state[i] = HIGH;
   }
   Joystick.begin();
}

void loop()
{
   // digital logic
   int i;
   for(i = 0; i < numPins; i++)
   {
      btn_state[i] = digitalRead(myPins[i]);
   
      if (btn_state[i] != previous_state[i])
      {
          Joystick.setButton(myPins[i], btn_state[i]);
          previous_state[i] = btn_state[i];
      }
   }
   
   // analog logic
   int pot = analogRead(A0);
   int mapped = map(pot,0,615,0,255); //615 cause my axis only travels slightly past halfway.
   {
      Joystick.setThrottle(mapped);
   }

   delay(50);
}
