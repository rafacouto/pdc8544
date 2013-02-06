
#include <PDC8544.h>

// LCD connected to digital IO's 45,47,49,51,53
PDC8544 lcd(45,47,49,51,53);


void setup()
{
  lcd.init();
  lcd.clear();
  lcd.drawString("Hello world!");
}


void loop()
{
  // page 1
  lcd.gotoXY(0,2);
  lcd.drawString("This is a test");
  lcd.drawString("for drawing on");
  lcd.drawString("a PDC8544 over");
  lcd.drawString("Arduino.      ");
  delay(5000);  
  
  // page 2
  lcd.gotoXY(0,2);
  lcd.drawString("It uses a cool");
  lcd.drawString("library coded ");
  lcd.drawString("by Rafa Couto ");
  lcd.drawString("aka @caligari.");
  delay(5000);  
}
