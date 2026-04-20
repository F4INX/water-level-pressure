#include <LiquidCrystal_I2C.h>

const int cols = 16;
const int rows = 2;
LiquidCrystal_I2C lcd(0x27, cols, rows);  // Set the LCD address to 0x27 for a 16 chars and 2 line.

int sensor_pin = A0;

const float V_BANDGAP = 1.1;

const float ZERO_V = 0.5;
const float FS_V = 4.5;
const float FS_DEPTH = 3.0;

int adc_read_bandgap() {
  // See https://forum.arduino.cc/t/measurement-of-bandgap-voltage/38215/4
  // REFS1 REFS0          --> 0 1, AVcc internal ref.
  // MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)
  ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
  delay(1);  // FIXME: check this delay again
  // Start a conversion
  ADCSRA |= _BV( ADSC );
  // Wait for it to complete
  while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
  return ADC;
}

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
  int bandgap_adc = adc_read_bandgap();
  float sensor_volt = (float(sensor_adc) / float(bandgap_adc)) * V_BANDGAP;
  float depth = (sensor_volt - ZERO_V) / (FS_V - ZERO_V) * FS_DEPTH;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(depth, 3);
  delay(1000);
}
