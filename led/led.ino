// Runs once when the board turns on or resets
void setup() {
  // Configure digital pin 13 as an output pin
  pinMode(13, OUTPUT); 
}

// Runs repeatedly in an infinite while(1) loop
void loop() {
  digitalWrite(13, HIGH); // Send 5V (Turn LED ON)
  delay(100);            // Pause for 1000 milliseconds (1 second)
  
  digitalWrite(13, LOW);  // Send 0V (Turn LED OFF)
  delay(100);            // Pause for 1 second
}
