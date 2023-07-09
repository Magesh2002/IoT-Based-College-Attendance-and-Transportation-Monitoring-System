#include <LiquidCrystal.h>
#define CMDBUFFER_SIZE 32
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buzzer = 9;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
pinMode(buzzer, OUTPUT);
 lcd.begin(16, 2);
  lcd.print(" Finger Print");
  lcd.setCursor(0,1);
  lcd.print("  Attendance");
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
 
 serialEvent();
 
}

void serialEvent()
{
  static char cmdBuffer[CMDBUFFER_SIZE] = "";
  char c;
  while(Serial.available())
  {
    c = processCharInput(cmdBuffer, Serial.read());
    Serial.print(c);
    if (c == '\n')
    {
      Serial.println();
      //Full command received. Do your stuff here!      
      if (strcmp("No finger detected", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print(" Waiting For");
         lcd.setCursor(0,1);
         lcd.print("  Finger...");
      }else if (strcmp("Adafruit Fingerprint sensor enrollment", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("Fingerprint sensor");
         lcd.setCursor(0,1);
         lcd.print("  enrollment");
      }else if (strcmp("Found fingerprint sensor", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("Found Fingerprint");
         lcd.setCursor(0,1);
         lcd.print("  sensor");
      }else if (strcmp("Did not find fingerprint sensor", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("Did not find");
         lcd.setCursor(0,1);
         lcd.print("fingerprint sensor");
      }else if (strcmp("Please type in the ID # (from 1 to 127) you want to save this finger as...", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("Type in");
         lcd.setCursor(0,1);
         lcd.print("  ID");
      }else if (strcmp("Enrolling ID #", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("Enrolling");
         lcd.setCursor(0,1);
         lcd.print("  ID");
      }else if (strcmp("Stored!", cmdBuffer) == 0)
      {
         tone(buzzer, 1000); // Send 1KHz sound signal...
         delay(1000);        // ...for 1 sec
         noTone(buzzer);     // Stop sound...
         delay(1000);  
         lcd.begin(16, 2);
         lcd.print("Stored");
         lcd.setCursor(0,1);
         lcd.print("  ID");
      }else if (strcmp("Connecting", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("  Connecting");
         lcd.setCursor(0,1);
         lcd.print("  to WiFi");
      }else if (strcmp("Connected", cmdBuffer) == 0)
      {
         lcd.begin(16, 2);
         lcd.print("  Connected");
         lcd.setCursor(0,1);
         lcd.print("    to WiFi");
      }else if (strcmp("Found a print match!", cmdBuffer) == 0)
      {
         tone(buzzer, 1000); // Send 1KHz sound signal...
         delay(1000);        // ...for 1 sec
         noTone(buzzer);     // Stop sound...
         delay(1000);  
         lcd.begin(16, 2);
         lcd.print("  Logged");
         lcd.setCursor(0,1);
         lcd.print("    In");//Found a print match!
      }
      cmdBuffer[0] = 0;
    }
  }
  delay(1);
}

char processCharInput(char* cmdBuffer, const char c)
{
  //Store the character in the input buffer
  if (c >= 32 && c <= 126) //Ignore control characters and special ascii characters
  {
    if (strlen(cmdBuffer) < CMDBUFFER_SIZE)
    {
      strncat(cmdBuffer, &c, 1);   //Add it to the buffer
    }
    else  
    {  
      return '\n';
    }
  }
  else if ((c == 8 || c == 127) && cmdBuffer[0] != 0) //Backspace
  {

    cmdBuffer[strlen(cmdBuffer)-1] = 0;
  }

  return c;
}
