const int pushButton = 2;
const int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  if (buttonState == LOW)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  // print out the state of the button:
    // delay in between reads for stability
}
