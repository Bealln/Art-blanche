
// Example 5 - Receive with start- and end-markers combined with parsing
#include <Stepper.h>
#define STEPSA 200
#define STEPSB 200

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char motor[numChars] = {0};
char symbol[numChars] = {0};
char steps = 0;
int integerFromPC = 0;
float floatFromPC = 0.0;

boolean newData = false;

Stepper stepper(STEPSA,4,5,6,7);
Stepper stepperB(STEPSB,8,9,10,11);

//============

void setup() {
    Serial.begin(9600);
    Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
    Serial.println("Enter data in this style <A, +, 25>  ");
    // set the speed of the motor to 30 RPMs
    stepper.setSpeed(30);
    stepperB.setSpeed(30);  
    Serial.println();
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
    strcpy(motor, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL,",");      // get the second part - the string
    strcpy(symbol, strtokIndx); // copy it to messageFromPC

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    integerFromPC = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
    Serial.print("Motor ");
    Serial.println(motor);
    Serial.print("Symbol ");
    Serial.println(symbol);
    Serial.print("Steps as integer ");
    Serial.println(integerFromPC);
    Serial.print("Steps as float ");
    Serial.println(floatFromPC);
}


void runstepper()
{
  stepper.step(integerFromPC);
  stepperB.step(symbol);
}
