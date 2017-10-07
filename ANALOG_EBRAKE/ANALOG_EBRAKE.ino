// Analog eBrake-Handbrake
// PIN A0 to 10k pot output - Throttle Axis
// Use with Arduino ProMicro.
// Tested and working in DiRT RALLY + ASSETTO CORSA
// by AMSTUDIO
// 20.1.2017

// NachoChef 10/5/2017
// Adding additional support for more buttons. More buttons = more juice.
// Additional button code based off the `Arduino - Switch` example.

// todo - Wire buttons, create array, get more juice.
#include <Joystick.h>

const int eBrakePin = A0;

// 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16 are available digital pins
// just enter the pins you're using below and everything else is automatic
int myPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16};
const int numPins = sizeof(myPins);
int btn_state[numPins];
int btn_read[numPins];
int previous_state[numPins];

// this is to prevent multiple triggering for one press
// long time = 0;
// long debounce = 200;

void setup()
{
   pinMode(eBrakePin, INPUT); 
   
   int i;
   for (i = 0; i < numPins; i++)
   {
      pinMode(myPins[i], PULL_UP);
      btn_state[i] = LOW;
      previous_state[i] = HIGH;
   }
   Joystick.begin();
}

void loop()
{
   // digital logic
   int i;
   for(int i = 0; i < numPins; i++)
   {
      btn_read[i] = digitalRead(myPins[i]);
   
      
      // if (btn_read[i] == HIGH && previous[i] == LOW)
      if (btn_read[i] != previous_state[i])
      {
          if (btn_state[i] == HIGH)
            btn_state[i] = LOW;
          else
            btn_state[i] = HIGH;
         
          Joystick.setButton(myPins[i], btn_state[i]);
      }
   }
   
   // analog logic
   int pot = analogRead(A0);
   int mapped = map(pot,0,615,0,255); //615 cause my axis only travels slightly past halfway.
   {
      Joystick.setThrottle(mapped);
   }
}
