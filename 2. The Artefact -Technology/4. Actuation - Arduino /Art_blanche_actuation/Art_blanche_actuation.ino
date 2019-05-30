// Example 5 - Receive with start- and end-markers combined with parsing
#include <Stepper.h>
#define STEPSA 200 //Nema23
#define STEPSB 400 //Nema17

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char stepsA[numChars] = {0};
char stepsB[numChars] = {0};


boolean newData = false;

Stepper stepper(STEPSA,8,9,10,11);//Make sure this is conected to the right motor
Stepper stepperB(STEPSB,4,5,6,7);

//============ 

void setup() {
    Serial.begin(9600);
    Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
    Serial.println("Enter data in this style <+20,-50> ");
    // set the speed of the motor to 30 RPMs
    stepper.setSpeed(30);
    stepperB.setSpeed(30);  
   
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        runstepper();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index
    
    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(stepsA, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL,",");      // get the second part - the string
    strcpy(stepsB, strtokIndx); // copy it to messageFromPC

}

//============

void showParsedData() {
    Serial.print("Steps for motor A ");
    Serial.println(stepsA);
    Serial.print("Steps for motor B ");
    Serial.println(stepsB);
}


void runstepper()
{
  stepper.step(stepsA);
  stepperB.step(stepsB);
}
