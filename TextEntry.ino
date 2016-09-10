//CS294-98 IDD
//Homework 2: Text Entry Device
//Jonya Chen
//September 8, 2016

#if defined(ARDUINO)
SYSTEM_MODE(MANUAL);
#endif

//set pin numbers (constants)
const int rowPin = D0;   //input pin for row pushbutton
const int colPin = D1;   //input pin for column pushbutton
const int enterPin = D2; //input pin for enter button
const int spacePin = D3; //input pin for space button

// Variables
int rowState;            //the current reading from the row input pin
int lastRowState = HIGH; //the previous reading from the  row input pin
int colState;            //the current reading from the  row input pin
int lastColState = HIGH; //the previous reading from the  col input pin
int enterState;
int lastEnterState = HIGH;
int spaceState;
int lastSpaceState = HIGH;

// Count of button presses
int rowCount = 0;
int colCount = 0;

//character to print
char letter;

// Times for debouncing
long lastDebounceRowTime = 0;   //last time the row button was pressed
long lastDebounceColTime = 0;   //last time the col button was pressed
long lastDebounceEnterTime = 0; //last time the enter button was pressed
long lastDebounceSpaceTime = 0; //last time the enter button was pressed

long debounceDelay = 50;        //debounce time - increase if the press reading flickers

//to run once
void setup() {
  pinMode(rowPin, INPUT_PULLUP);
  pinMode(colPin, INPUT_PULLUP);
  pinMode(enterPin, INPUT_PULLUP);
  pinMode(spacePin, INPUT_PULLUP);

  //sets up serial terminal
  Serial.begin(9600);
}

//runs repeatedly
void loop() {
  int rowReading = digitalRead(rowPin);     //reads the state of the row button
  int colReading = digitalRead(colPin);     //reads the state of the col button
  int enterReading = digitalRead(enterPin); //reads the state of the enter button
  int spaceReading = digitalRead(spacePin); //reads the state of the space button

  //debouncing = check to see if you just pressed the button
  // (ie the input went from HIGH to LOW),  and you've waited
  // long enough since the last press to ignore any noise:

  //If the button state has changed, due to noise or pressing:
  if (rowReading != lastRowState) {
    lastDebounceRowTime = millis();     //reset the debouncing timer for row button
  }

  if (colReading != lastColState) {
    lastDebounceColTime = millis();     //reset the debouncing timer for column button
  }
  
  if (enterReading != lastEnterState) {
    lastDebounceEnterTime = millis();  //reset the debouncing timer for enter button
  }

  if (spaceReading != lastSpaceState) {
    lastDebounceSpaceTime = millis();  //reset the debouncing timer for space button
  }

  //debounce loop for row button
  if ((millis() - lastDebounceRowTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (rowReading != rowState) {
      rowState = rowReading;

      // if new button state is LOW, increment the count for row button presses
      if (rowState == LOW) {
        rowCount++;
      }
    }
  }

  
  //debounce loop for col button
  if ((millis() - lastDebounceColTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (colReading != colState) {
      colState = colReading;

      // if new button state is LOW, increment the count for col button presses
      if (colState == LOW) {
        colCount++;
      }
    }
  }

  //debounce loop for space button
  if ((millis() - lastDebounceSpaceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (spaceReading != spaceState) {
      spaceState = spaceReading;

      // if new button state is LOW, increment the count for space button presses
      if (spaceState == LOW) {
        Serial.print(" "); //prints a space character
      }
    }
  }

    //debounce loop for enter button
    if ((millis() - lastDebounceEnterTime) > debounceDelay) {

    // if the button state has changed:
    if (enterReading != enterState) {
      enterState = enterReading;

      // if enter button is pressed
      if (enterState == LOW) {
        //Serial.println(rowCount); //print count of row button pressed
        //Serial.println(colCount); //print count of col button pressed

        //determine letter
        switch (rowCount) {
          case 1: //row = 1
            if (colCount == 1) {
              letter = 'A';
            }
            else if (colCount == 2) {
              letter = 'B';
            }
            else if (colCount == 3) {
              letter = 'C';
            }
            else if (colCount == 4) {
              letter = 'D';
            }
            else if (colCount == 5) {
              letter = 'E';
            }
            else {
              letter = '#';
            }
            break;
          case 2: //row = 2
            if (colCount == 1) {
              letter = 'F';
            }
            else if (colCount == 2) {
              letter = 'G';
            }
            else if (colCount == 3) {
              letter = 'H';
            }
            else if (colCount == 4) {
              letter = 'I';
            }
            else if (colCount == 5) {
              letter = 'J';
            }
            else {
              letter = '#';
            }
            break;
          case 3: //row = 3
            if (colCount == 1) {
              letter = 'L';
            }
            else if (colCount == 2) {
              letter = 'M';
            }
            else if (colCount == 3) {
              letter = 'N';
            }
            else if (colCount == 4) {
              letter = 'O';
            }
            else if (colCount == 5) {
              letter = 'P';
            }
            else {
              letter = '#';
            }
            break;
          case 4: //row = 4
            if (colCount == 1) {
              letter = 'Q';
            }
            else if (colCount == 2) {
              letter = 'R';
            }
            else if (colCount == 3) {
              letter = 'S';
            }
            else if (colCount == 4) {
              letter = 'T';
            }
            else if (colCount == 5) {
              letter = 'U';
            }
            else {
              letter = '#';
            }
            break;
          case 5: //row = 5
            if (colCount == 1) {
              letter = 'V';
            }
            else if (colCount == 2) {
              letter = 'W';
            }
            else if (colCount == 3) {
              letter = 'X';
            }
            else if (colCount == 4) {
              letter = 'Y';
            }
            else if (colCount == 5) {
              letter = 'Z';
            }
            else {
              letter = '#';
            }
            break;
          default: 
            letter = '#';
          break;
        }

        Serial.print(letter); //print designated letter when button pressed  
        colCount = 0;
        rowCount = 0;      
      }
    }
  }

  // save the reading.  Next time through the loop, it'll be the last state of the button:
  lastRowState = rowReading;
  lastColState = colReading;
  lastEnterState = enterReading;
  lastSpaceState = spaceReading;
}
