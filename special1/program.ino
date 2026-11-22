//pin init and key matrix and speaker tone array
{
const int mode_pin = 3;
const int speaker_pin = 4;
const int led_pin = 2;
const int transmitter_pin = 13;
const int res_pin = A1;
const int clr_pin = A0;

const int rowpins[] = {5,6,7,8,9};
const int colpins[] = {10,11,12};

const int tone[5][3] = {
    {262, 294, 330},
    {349, 392, 440},
    {494, 523, 587},
    {343, 467, 245},
    {0, 349, 0}
};

char keys[3][3] = {
    {'0','1','2'},
    {'3','4','5'},
    {'6','7','8'},
    {'-','9','+'}
};

char last_key = '\0';
}
// scans the rows and colums one by one with each combination and finds the active key. only runs 15 times in nesting
char matrix_scan(void)
{
    for (int r = 0; r<5; r++)
    {
        digitalWrite(rowpins[r], LOW);
        // here we turned off one row first
        // now we would check which column is low due to closed circuit
        for (int c = 0; c<3; c++)
        {
            if (digitalRead(colpins[c]) == LOW)
            {
                // if we recognised that a column is low, we use array and return the key
                // but we gotta turn the row up again first.
                digitalWrite(rowpins[r], HIGH);
                return keys[r][c];
            }
        }
        // turn on the row again which we turned off
        digitalWrite(rowpins[r], HIGH);
    }
    return '\0';
}
// actively calls matrix_scan twice to ensure mistake values due to spring bounce
char getkey(void)
{
    char current_key = matrix_scan();

    if (current_key != '\0' && last_key == '\0')
    {
        delay(20);
        if (matrix_scan() == current_key)
        {
        last_key = current_key;
        return current_key;
        }
    }
    if (current_key == '\0')
    {
        last_key = '\0';
    }
    return '\0';
}
// sends high and low voltages with a 2ms diff, for a given number (ex 0), it sends high and low the number of times as of number
// for 0 it sends a total 10 highs and 10 lows. 
void sendDigit(const unsigned int num)
{
    unsigned int blink;
    if (num == 0)
    {
        blink = 10;
    }
    else
    {
        blink = num;
    }
    for (unsigned int i = 0; i<blink; i++)
    {
        digitalWrite(transmitter_pin, HIGH);
        delay(2);
        digitalWrite(transmitter_pin, LOW);
    } digitalWrite(transmitter_pin, LOW);
    delay(5);
}
// for a given num, it sends the number in digits one by one by extracting them from behind
// gives a 40ms starting HIGH signal to let know the pin is gonna send data
void send_num(const int num)
{
    digitalWrite(transmitter_pin, HIGH);
    delay(40);
    digitalWrite(transmitter_pin, LOW);
    unsigned int x = num;
    for (int i = 0; i<4; i++)
    {
        sendDigit(x%10);
        x = x/10;
    }
}
// sets up speaker,led,mod,transmitter pins on output, res pin on inputpullup, rows on high and colums at high due to inputpullup
// sets up transmitter pin as low at start
void setup()
{
    pinMode(speaker_pin,OUTPUT);
    pinMode(led_pin, OUTPUT);
    pinMode(mode_pin, OUTPUT);
    pinMode(transmitter_pin, OUTPUT);
    // row pins would be kept on high
    pinMode(res_pin, INPUT_PULLUP);
    pinMode(clr_pin, INPUT_PULLUP);
    for (int r = 0; r<5; r++)
    {
        pinMode(rowpins[r], OUTPUT);
        digitalWrite(rowpins[r], HIGH);
    }
    for (int c = 0; c<3; c++)
    {
        pinMode(colpins[c], INPUT_PULLUP);
    }
    digitalWrite(transmitter_pin, LOW);
}


int nums[] = {0,0};
int numlen[] = {0,0};
int res; 
unsigned uint8_t state = 0;

void num_ext(const char num, const int signal)
{
    numlen[signal]++;
    nums[signal] = nums[signal]*10 + (num - '0');
}

void loop()
{
    char key = getkey();
    if (key != '\0')
    {
        if (state == 0)
        {
            if ((key != '-' || key != '+'))
            {
                num_ext(key, state);
            }
            else if ((key == '-' || key == '+') && numlen[state]>0)
            {   
                state = 1;
            }
        }
        if (state == 1)
        {
            if ((key != '-' || key != '+'))
            {
                num_ext(key, state);
            }
            else
            {
                res = nums[0] + nums[1];
            }
        }
    }
}
