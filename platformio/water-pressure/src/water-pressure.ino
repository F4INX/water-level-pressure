#include <LiquidCrystal_I2C.h>

const int cols = 16;
const int rows = 2;
LiquidCrystal_I2C lcd(0x27, cols, rows);  // Set the LCD address to 0x27 for a 16 chars and 2 line.

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
}
