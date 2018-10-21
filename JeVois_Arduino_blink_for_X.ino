 // JeVois + Arduino blink for X - easy version
 // from: http://jevois.org/tutorials/UserArduinoBlink.html
 

// includes from LCD 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
char msgLCD[14]; //the string to print on the LCD

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
 
 // Pin for LED, blinks as we receive serial commands:
 #define LEDPIN 13
 
 // Serial port to use: on chips with USB (e.g., 32u4), that usually is Serial1.
 // On chips without USB, use Serial:
 #define SERIAL Serial
 
 // Buffer for received serial port bytes:
 #define INLEN 256
 char instr[INLEN + 1];
 
 // Our desired object: should be one of the 1000 ImageNet category names
 #define CATEGORY "computer_keyboard"
 
 void setup()
 {
   SERIAL.begin(115200);
   SERIAL.setTimeout(500);
  
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
   
  strcpy(msgLCD, "Starting12" );
  lcd.setCursor(0,0); // col 1 line 0
  lcd.print(msgLCD);
  delay(2000);
   
   //Serial.begin(9600);
   //Serial.print ("OOOohhhhha");
   
   pinMode(LEDPIN, OUTPUT);
   digitalWrite(LEDPIN, HIGH);
   
   
   
 }
 
 void loop()
 {
   // Read a line of data from JeVois:
   byte len = SERIAL.readBytesUntil('\n', instr, INLEN);
   char tmpStr[10];
   
   
   //Serial.print ("Len is: ");
   //Serial.print (len);
   //Serial.println (" EOL ");
 
   // Make sure the string is null-terminated:
   instr[len--] = '\0';
   
  strcpy(msgLCD, "len is " ); 
  itoa(len+1,tmpStr,10);
  strcat(msgLCD,tmpStr );
   
  //lcd.setCursor(0,1); // col 1 line 0
  //lcd.print(msgLCD );
  //delay(1000);
  
  //while (true)
  // {}
   
   
  if (instr[0]=='T' &&  instr[0]=='O') 
   
   strcpy(msgLCD, instr ); 
  else
    strcpy(msgLCD, "             " );
  
  lcd.setCursor(0,0); 
  lcd.print(msgLCD ); 
   
   
  
  
   
   // Cleanup any trailing whitespace:
   while (len >= 0 && instr[len] == ' ' || instr[len] == '\r' || instr[len] == '\n') instr[len--] = '\0';
   
   // If empty (including timeout), stop here:
   if (len < 0)
   {
     digitalWrite(LEDPIN, HIGH); // turn LED off (it has inverted logic)
     return;
   }
   
   // If the message is a match for our desired category, turn led on, otherwise off:
   if (strcmp(instr, "TO " CATEGORY) == 0) {
     
      
   
      lcd.setCursor(0,1); 
      lcd.print("KBD detected" );
   
     digitalWrite(LEDPIN, LOW); // turn LED on (it has inverted logic)
     delay(1000);
   }
   else {
     digitalWrite(LEDPIN, HIGH); // turn LED off
   
     lcd.setCursor(0,1); 
     lcd.print("            " );
     
     
   }
 }