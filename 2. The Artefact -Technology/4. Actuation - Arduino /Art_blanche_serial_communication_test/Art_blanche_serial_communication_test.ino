
// Test serial monitor is working through different LED commands and run motors
#include <Stepper.h>
#define STEPSA 200 //Nema23
#define STEPSB 400 //Nema17

const int button = 8;   //push button connected here  
const int led =  13; // led connected here   (blue led)
int buttonStatus = 0;  

const int button2 = 3;   //push button connected here   
const int led2 =  6; // led connected here  (yellow led) 
int buttonStatus2 = 0;  

const byte numChars = 32;

char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

     // variables to hold the parsed data
char stepsA[numChars] = {0};
char stepsB[numChars] = {0};

boolean newData = false;

Stepper stepper(STEPSA,8,9,10,11); //Make sure this is conected to the right motor
Stepper stepperB(STEPSB,4,5,6,7);

//============

void setup() {
    Serial.begin(9600);
    Serial.println("This demo expects 3 pieces of data - enter each of the motors velocity");
    Serial.println("Enter data in this style <-25,+25> ");
    //Serial.println();

    // Set up LED and buttons
    pinMode(led,HIGH);
    pinMode(button,LOW);
    pinMode(led2,HIGH);
    pinMode(button2,LOW);

    // set the speed of the motor to 30 RPMs
    stepper.setSpeed(30);
    stepperB.setSpeed(30);  
}

//============

void loop() {
    recvWithStartEndMarkers(); // run check on the format of the input
    if (newData == true) {
        
        //Blink blue LED if the data is received 
        digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(led, LOW); // turn it off (finish the blink) 
        
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        // checkData(); It would be a check to the input 
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
    Serial.print("Steps for motor A  ");
    Serial.println(stepsA);
    Serial.print("Steps for motor B ");
    Serial.println(stepsB);  
}

void runstepper()
{
  stepper.step(stepsA);
  stepperB.step(stepsB);
}
