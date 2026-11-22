const int buttonpin = 2;
const int ledpin = 13;

int ledstate = LOW;
int confirmedbuttonstate = HIGH;
int lastRawreading = HIGH;

unsigned long lastbouncetime = 0;
const unsigned long debouncedelay = 50;

void setup()
{
    pinMode(buttonpin, INPUT_PULLUP);
    pinMode(ledpin, OUTPUT);
    digitalWrite(ledpin, ledstate);
}
void loop()
{
	int rawreading = digitalRead(buttonpin);

	if (rawreading != lastRawreading)
	{
		lastbouncetime = millis();
	}
	// if spring keeps bouncing, readings get changed.
	// lets check if the value remains steady during or after
	// the debounce time
	if (millis() - lastbouncetime >= debouncedelay)
	{
		if (rawreading != confirmedbuttonstate)
		{
			confirmedbuttonstate = rawreading;
		}

		if (confirmedbuttonstate == LOW)
		{
			ledstate = (ledstate == LOW) ? HIGH : LOW;
			digitalWrite(ledpin, ledstate);
		}
		
	}
	lastRawreading = rawreading;	
}
