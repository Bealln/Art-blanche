#include <Stepper.h>
 
// change this to the number of steps on your motor
#define STEPSA 200
#define STEPSB 200


// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPSA,4,5,6,7);
Stepper stepper2(STEPSB,8,9,10,11);

void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(60); 
  stepper2.setSpeed(40); 
}

void loop()
{
  stepper.step(30);
  stepper.step(-30);
  stepper2.step(200);
  stepper2.step(10);
}
