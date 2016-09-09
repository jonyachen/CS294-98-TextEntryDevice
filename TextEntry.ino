#if defined(ARDUINO)
SYSTEM_MODE(MANUAL);
#endif

//set pin numbers (constants)
const int ledPin = D7;      //input pin for LED
const int buttonPin = D0;   //input pin for pushbutton
const int enterPin = D1;    //input pinn for enter button

// Variables
int buttonState;            //the current reading from the input pin
int lastButtonState = HIGH; //the previous reading from the input pin
int enterState;            //the current reading from the input pin
int lastEnterState = HIGH; //the previous reading from the input pin

// Count of button presses
int count = 0;

long lastDebounceButtonTime = 0;  //last time the button was pressed
long lastDebounceEnterTime = 0;
long debounceDelay = 50;    //debounce time - increase if the output flickers

//to run once
void setup() {
  //pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(enterPin, INPUT_PULLUP);

  //sets up serial terminal
  Serial.begin(9600);
}

//runs repeatedly
void loop() {
  int reading = digitalRead(buttonPin); //reads the state of the button
  int enterReading = digitalRead(enterPin);

  //debouncing = check to see if you just pressed the button
  // (ie the input went from HIGH to LOW),  and you've waited
  // long enough since the last press to ignore any noise:

  //If the button state has changed, due to noise or pressing:
  if (reading != lastButtonState) {
    lastDebounceButtonTime = millis();     //reset the debouncing timer
  }
  
  if (enterReading != lastEnterState) {
    lastDebounceEnterTime = millis();
  }

  if ((millis() - lastDebounceButtonTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // if new button state is LOW, increment the count for button presses
      if (buttonState == LOW) {
        count++;
      }
    }
  }

    if ((millis() - lastDebounceEnterTime) > debounceDelay) {

    // if the button state has changed:
    if (enterReading != enterState) {
      enterState = enterReading;

      // if enter button is pressed
      if (enterState == LOW) {
        Serial.println(count); //print count of button pressed
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  lastEnterState = enterReading;
}
