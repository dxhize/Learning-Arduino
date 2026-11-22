const int static_led_pin = 13;
const int pwm_led_pin = 9;
const int pot_val_pin = A1;
unsigned long prevmills = 0;

void setup()
{
    pinMode(static_led_pin, OUTPUT);
    pinMode(pwm_led_pin, OUTPUT);
    pinMode(pot_val_pin, INPUT);
}

void loop()
{
    unsigned long currentmillis = millis();
    if (currentmillis - prevmills >= 500)
    {
        prevmills = currentmillis;
    }
    if (currentmillis - prevmills < 100)    
    {
        digitalWrite(static_led_pin, HIGH);
    }
    else
    {
        digitalWrite(static_led_pin, LOW);
    }
    int potvalue = analogRead(pot_val_pin);
    int brightness = map(potvalue, 0,1023, 0, 255);
    analogWrite(pwm_led_pin, brightness);
}