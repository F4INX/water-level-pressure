#include <LiquidCrystal_I2C.h>

const int cols = 16;
const int rows = 2;
LiquidCrystal_I2C lcd(0x27, cols, rows);  // Set the LCD address to 0x27 for a 16 chars and 2 line.

int sensor_pin = A0;

const float V_REF = 5.0;
const int R_BITS = 10.0;
const float ADC_STEPS = 1 << R_BITS;

void setup() {
  /* Serial */
  Serial.begin(9600);
  Serial.println("Start");
  /* LED */
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  /* LCD config */
  lcd.init();
  lcd.backlight();
  /* LCD write */
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("0123456789ABCDEF");
  lcd.setCursor(0,1);
  lcd.print("9876543210ABCDEF");
}

void loop() {
  int sensor_adc = analogRead(sensor_pin);
  float sensor_volt = (sensor_adc / ADC_STEPS) * V_REF;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(sensor_volt, 3);
  delay(1000);
}
