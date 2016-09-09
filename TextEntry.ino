#if defined(ARDUINO)
SYSTEM_MODE(MANUAL);
#endif

//set pin numbers (constants)
const int rowPin = D0;   //input pin for row pushbutton
const int colPin = D1;   //input pin for column pushbutton
const int enterPin = D2;    //input pinn for enter button

// Variables
int rowState;            //the current reading from the row input pin
int lastRowState = HIGH; //the previous reading from the  row input pin
int colState;            //the current reading from the  row input pin
int lastColState = HIGH; //the previous reading from the  col input pin
int enterState;
int lastEnterState = HIGH;

// Count of button presses
int rowCount = 0;
int colCount = 0;

// Times for debouncing
long lastDebounceRowTime = 0;   //last time the row button was pressed
long lastDebounceColTime = 0;   //last time the col button was pressed
long lastDebounceEnterTime = 0; //last time the enter button was pressed

long debounceDelay = 50;        //debounce time - increase if the press reading flickers

//to run once
void setup() {
  pinMode(rowPin, INPUT_PULLUP);
  pinMode(colPin, INPUT_PULLUP);
  pinMode(enterPin, INPUT_PULLUP);

  //sets up serial terminal
  Serial.begin(9600);
}

//runs repeatedly
void loop() {
  int rowReading = digitalRead(rowPin);     //reads the state of the row button
  int colReading = digitalRead(colPin);     //reads the state of the col button
  int enterReading = digitalRead(enterPin); //reads the state of the enter button

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

    //debounce loop for enter button
    if ((millis() - lastDebounceEnterTime) > debounceDelay) {

    // if the button state has changed:
    if (enterReading != enterState) {
      enterState = enterReading;

      // if enter button is pressed
      if (enterState == LOW) {
        Serial.println(rowCount); //print count of row button pressed
        Serial.println(colCount); //print count of col button pressed
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastRowState = rowReading;
  lastColState = colReading;
  lastEnterState = enterReading;
}
