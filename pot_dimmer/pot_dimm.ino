const int potpin = A0;
const int pwmledpin = 9;

void setup()
{
	pinMode(pwmledpin,OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	//analogRead meausures 0V to 5V and 
	// converts it into a 10-bit integer 
	// between 0 to 1023 inclusive.
	int potvalue = analogRead(potpin);

	int brightness = map(potvalue, 0, 1023, 0, 255);
	analogWrite(pwmledpin, brightness);

	Serial.print("Dial Raw (0-1023): ");
	Serial.print(potvalue);

	Serial.print(" | LED PWM (0-255): ");
	Serial.println(brightness);
	delay(100);
}
