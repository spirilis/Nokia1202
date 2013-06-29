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
  SPI.begin();
  lcd.begin(false, 8);
  lcd.puts("I like thiss.\n");
  lcd.setCursor(2, 1);
  lcd.puts("Hello world!\n");
}


unsigned int j;

void loop() {
  unsigned int i;
  
  delay(1000);
  i = millis();
  lcd.println(j); lcd.puts("next: ");
  j = millis() - i;
}

