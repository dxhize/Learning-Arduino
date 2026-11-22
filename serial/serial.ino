const int switchLedPin = 13;
const int pwmpin = 9;

void setup()
{
    pinMode(switchLedPin, OUTPUT);
    pinMode(pwmpin, OUTPUT);
    Serial.begin(9600);

    Serial.println("==Arduino Keyboard Controller==");
    Serial.println("Type '1' -> Pin 13 LED ON");
    Serial.println("Type '0' -> Pin 13 LED OFF");
    Serial.println("Type 'L' -> Pin 9 Speed/Brightness LOW (25%)");
    Serial.println("Type 'M' -> Pin 9 Speed/Brightness MEDIUM (50%)");
    Serial.println("Type 'H' -> Pin 9 Speed/Brightness HIGH (100%)");
}
void loop()
{
    if (Serial.available()> 0)
    {
        char cmd = Serial.read();

        switch (cmd)
        {
            case '1':
            digitalWrite(switchLedPin, HIGH);
            Serial.println("-> Pin 13: ON");
            break;

            case '0':
            digitalWrite(switchLedPin, LOW);
            Serial.println("-> Pin 13: OFF");
            break;

            case 'L':
            case 'l':
            {
                analogWrite(pwmpin, 64);
                Serial.println("Pin 9: LOW");
            }
            break;

            case 'M':
            case 'm':
                analogWrite(pwmpin, 127);
                Serial.println("Pin 9: MEDIUM");
                break;
            case 'h':
            case 'H':
                analogWrite(pwmpin, 255);
                Serial.println("Pin 9: HIGH");
                break;
            default:
                Serial.print("Unknown command: ");
                Serial.println(cmd);
                break;
        }
    }

}