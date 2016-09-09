#if defined(ARDUINO)
SYSTEM_MODE(MANUAL);
#endif

//set pin numbers (constants)
const int ledPin = D7;      //input pin for LED
const int buttonPin = D0;   //input pin for pushbutton

// Variables
int ledState = LOW;         //current state of the output pin
int buttonState;            //the current reading from the input pin
int lastButtonState = HIGH; //the previous reading from the input pin

long lastDebounceTime = 0;  //last time the output pin was toggled
long debounceDelay = 50;    //debounce time - increase if the output flickers


//to run once
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  //sets initial LED state
  digitalWrite(ledPin, ledState);

  //sets up serial terminal
  Serial.begin(9600);
}

//runs repeatedly
void loop() {
  int reading = digitalRead(buttonPin); //reads the state of the button

  //debouncing = check to see if you just pressed the button
  // (ie the input went from HIGH to LOW),  and you've waited
  // long enough since the last press to ignore any noise:

  //If the button state has changed, due to noise or pressing:
  if (reading != lastButtonState) {
    lastDebounceTime = millis();     //reset the debouncing timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW
      if (buttonState == LOW) {
        ledState = !ledState; //toggle LED
        Serial.print("pressed");
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
