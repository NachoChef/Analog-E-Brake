// Analog eBrake-Handbrake
// PIN A0 to 10k pot output - Throttle Axis
// Use with Arduino ProMicro.
// Tested and working in DiRT RALLY + ASSETTO CORSA
// by AMSTUDIO
// 20.1.2017


// Adding additional support for more buttons. More buttons = more juice.
// Additional button code based off the `Arduino - Switch` example.

// todo - Wire buttons, create array, get more juice.
#include <Joystick.h>

const int eBrakePin = A0;
const int btn1 = 2;
int btn1_state = HIGH;
int btn1_read;
int previous = LOW;
long time = 0;
long debounce = 200;

void setup()
{
   pinMode(eBrakePin, INPUT); 
   pinMode(btn1, PULL_UP);
   Joystick.begin();
}

void loop()
{
   // digital logic
   btn1_read = digitalRead(btn1);
   if (btn1_read == HIGH && previous == LOW && millis() - time > debounce) {
       if (state == HIGH)
         state = LOW;
       else
         state = HIGH;

       time = millis();   
       Joystick.sendState(btn1_state);
   }
   
   // analog logic
   int pot = analogRead(A0);
   int mapped = map(pot,0,1023,0,255);
   {
      Joystick.setThrottle(mapped);
   }
}
