/* Nokia 1202 "hello world" style example.
 * May be used with framebuffer or non-framebuffer mode.
 * Framebuffer mode is selected by editing Nokia1202.h and
 * uncommenting the #define NOKIA1202_USE_FRAMEBUFFER line.
 */
#include <Nokia1202.h>
#include <ste2007.h>
#include <SPI.h>

Nokia1202 lcd(P2_0);

void setup() {
  pinMode(P2_5, OUTPUT);  // LCD's backlight (default pin for The 1202 boosterpack)
  digitalWrite(P2_5, HIGH);  // Backlight on full brightness
  
  SPI.begin();
  lcd.begin(true, 8);
  lcd.println("Nokia 1202");
  lcd.println("ADC test");
}


void loop() {
  unsigned int i;
  
  delay(1000);
  i = analogRead(A1);
  analogWrite(P2_5, i >> 2);  // Brightness changes with ADC value
  lcd.print("A1(P1_1): ");
  lcd.println(i);
}

