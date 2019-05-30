
// Test serial monitor is working through different LED commands

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
char motor[numChars] = {0}; 
char symbol[numChars] = {0};
char steps = 0;

boolean newData = false;

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

}


//============

void showParsedData() {
    Serial.print("Motor ");
    Serial.println(motor);
    Serial.print("Symbol ");
    Serial.println(symbol);  
}
