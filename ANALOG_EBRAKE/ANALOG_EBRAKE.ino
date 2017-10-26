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

// 10/26/2017
// Implemented the Bounce2 library for proper debouncing
// I'd like to note I'm not doing a typical array for the buttons in the search for low latency
// and it probably doesn't make much of a difference. Additionally leaving analog pins open for
// a future idea.

#include <Joystick.h>
#include <Bounce2.h>

const int eBrakePin = A0;

// 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16 are available 'strictly digital' pins
// just enter the pins you're using below and everything else is automatic
// note this probably isn't the most efficient way to do anything :)
// but I'm going for low latency rather than more buttons

int myPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16};


// The rest of the code is 'automatic'
const int numPins = sizeof(myPins)/sizeof(int);
Bounce debouncing[numPins];

void setup()
{
   // setting up the analog pin
   pinMode(eBrakePin, INPUT); 


   // setting up the digital pins with debouncing
   int i;
   for (i = 0; i < numPins; i++)
   {
      pinMode(myPins[i], INPUT_PULLUP);
      debouncing[i] = Bounce();
      debouncing[i].attach(myPins[i]);
      debouncing[i].interval(5);
   }
   Joystick.begin();
}

void loop()
{
   // reading and transmitting digital pin states with debouncing
   int i;
   for(i = 0; i < numPins; i++)
   {
      debouncing[i].update();
      Joystick.setButton(myPins[i], debouncing[i].read());
   }
   
   // analog logic
   //int pot = analogRead(A0);
   //int mapped = map(pot,0,1023,0,255); // you can adjust `1023` to however far your axis actually travels if it isn't full range
   {
      Joystick.setThrottle(map(analogRead(A0),0,1023,0,255));
   }
}
