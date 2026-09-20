
#include <LiquidCrystal_I2C.h>
#include <stdbool.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED 11
#define BUZ 3
#define BUT 2

bool button_state = 0;
bool previous_state = 0;

unsigned long previousTime = 0;
const unsigned long interval = 1000;

void setup() {

    pinMode(LED, OUTPUT);
    pinMode(BUT, INPUT_PULLUP);
    pinMode(BUZ, OUTPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    // Read initial button state
    previous_state = digitalRead(BUT);
}

void BrightnessLED(int reading) {

    // Convert ADC value (0-1023) to PWM value (0-255)
    int pwmValue = (reading * 255L) / 1023;
    int brightnessPercent = (pwmValue*100L)/255;
    analogWrite(LED, pwmValue);

    lcd.setCursor(0, 0);

    if (button_state) {
        lcd.print("MODE: A0       ");
    }
    else {
        lcd.print("MODE: A1       ");
    }

    lcd.setCursor(0, 1);
    lcd.print("LED B: ");
    lcd.print(brightnessPercent);
    lcd.print("       ");

    Serial.print("Mode: ");
    Serial.print(button_state ? "A0" : "A1");
    Serial.print(" | ADC: ");
    Serial.print(reading);
    Serial.print(" | LED_B: ");
    Serial.print(brightnessPercent);
    Serial.println("%/100%");
}

void loop() {


    bool current_state = digitalRead(BUT);

    // Detect LOW -> HIGH transition
    if (previous_state && !current_state) {

        button_state ^= 1;

        Serial.print("Mode changed to: ");
        Serial.println(button_state ? "A0" : "A1");
    }

    previous_state = current_state;


  

    int reading;

    if (button_state) {
        reading = analogRead(A0);
    }
    else {
        reading = analogRead(A1);
    }



    unsigned long currentTime = millis();

    if (currentTime - previousTime >= interval) {

        previousTime = currentTime;

        BrightnessLED(reading);
    }
}

