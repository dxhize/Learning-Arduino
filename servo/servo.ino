#include <Servo.h>

const int pwmservo_pin = 3;
const int pwm_led_pin = 5;
const int pot_pin = A0;
Servo s;

void setup()
{
    s.attach(pwmservo_pin);
    pinMode(pwmservo_pin, OUTPUT);
    pinMode(pwm_led_pin, OUTPUT);
    pinMode(pot_pin, INPUT);
}

void loop()
{
    int potent  = analogRead(pot_pin);
    int turn = map(potent, 0, 1023, 0,180);
    s.write(turn);
    int brighness = map(potent, 0,1023, 0,255);
    analogWrite(pwm_led_pin, brighness);
}