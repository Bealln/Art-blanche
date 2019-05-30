#include <Stepper.h>
 
// change this to the number of steps on your motor
#define STEPSA 200
#define STEPSB 400
#define home_switch 9 // Pin 9 connected to Home Switch (MicroSwitch)
//bool doneFlag = false;
 
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's attached to

//StepperA is for the shoulder joint, stepperB for the elbow joint
Stepper stepperA(STEPSA,4,5,6,7);
Stepper stepperB(STEPSB,8,9,10,11);

const int buttonOn = 12; 
const int buttonHome = 2; // This is not working

int buttonOnState = 0; 
int buttonHomeState = 0; 

void setup()
{
  //Add on and off - if On continue if off stop the code
  Serial.begin(9600);
  Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  stepperA.setSpeed(30); 
  stepperB.setSpeed(30); 
  // initialize the pushbutton pin as an input:
  pinMode(buttonOn, INPUT);
  pinMode(buttonHome, INPUT);

  // Read file 
}


void loop()
{
  // read the state of the pushbutton value:
  buttonOnState = digitalRead(buttonOn);
  buttonHomeState = digitalRead(buttonHome);
  Serial.println("hello");
  Serial.println(buttonOnState);
  //Move as said in file 
   
  //stepperA.step(a);
  //stepperB.step(b);
  
  if (buttonOnState == HIGH) {
    stepperA.setSpeed(60); 
    stepperA.step(STEPSA);
    stepperB.step(STEPSB);
    // debounce:
    delay(150);
    //Add - Then stop the code
  }
 
}
