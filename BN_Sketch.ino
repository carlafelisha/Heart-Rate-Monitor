
/*  
>>> Pulse Sensor purple wire goes to Analog Pin 0 <<<
Pulse Sensor sample aquisition and processing happens in the background via Timer 2 interrupt. 2mS sample rate.
PWM on pins 3 and 11 will not work when using this code, because we are using Timer 2!
The following variables are automatically updated:
Signal :    int that holds the analog signal data straight from the sensor. updated every 2mS.
IBI  :      int that holds the time interval between beats. 2mS resolution.
BPM  :      int that holds the heart rate value, derived every beat, from averaging previous 10 IBI values.
QS  :       boolean that is made true whenever Pulse is found and BPM is updated. User must reset.
Pulse :     boolean that is true when a heartbeat is sensed then false in time with pin13 LED going out.
*/

#include <LiquidCrystal.h>
#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0 (A0)
int blinkPin = 13;                // pin to blink led at each beat

// These variables are volatile because they are used in the interrupt service routine!
volatile int BPM;                   // int that holds the pulse rate. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

static int outputType = 2;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte heart[8] = {0b00000, 0b01010, 0b11111, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
byte smiley[8] = {0b00000, 0b00000, 0b01010, 0b00000, 0b00000, 0b10001, 0b01110, 0b00000};
byte frownie[8] = {0b00000, 0b00000, 0b01010, 0b00000, 0b00000, 0b00000, 0b01110, 0b10001};
byte armsDown[8] = {0b00100, 0b01010, 0b00100, 0b00100, 0b01110, 0b10101, 0b00100, 0b01010};
byte armsUp[8] = {0b00100, 0b01010, 0b00100, 0b10101, 0b01110, 0b00100, 0b00100, 0b01010};

void setup(){
  pinMode(blinkPin,OUTPUT);
  Serial.begin(115200);
  interruptSetup();
  lcd.begin(20, 4);
  lcd.createChar(0, heart);
  lcd.createChar(1, smiley);
  lcd.createChar(2, frownie);
  lcd.createChar(3, armsDown);
  lcd.createChar(4, armsUp);
}


void loop()
{
  serialOutput() ;
  if (QS == true){     // A Heartbeat Was Found
          serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
          QS = false;                      // reset the Quantified Self flag for next time
    }
  lcd.clear();
  for (int thisNum = 0; thisNum < 10; thisNum++)
  {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("WELCOME TO");
    lcd.setCursor(3, 1);
    lcd.print("HEARTBEAT HERO");
    delay(100);
    lcd.setCursor(9, 2);
    lcd.write((byte) 0);
    lcd.write((byte) 0);
    lcd.setCursor(0, 3);
    lcd.print("PUT FINGER ON SENSOR");
    delay(1000);
    lcd.setCursor(3, 2);
    lcd.print("TIME TO PLAY!");
    }
  delay(6000);
  lcd.clear();
  for (int n = 0; n < 9; n++)
    lcd.setCursor(5, 0);
    lcd.print("HEART RATE");
    lcd.setCursor(0, 1);
    lcd.print("BEATS/MIN (BPM): ");
    for (int N = 0; N < 10; N++)
    {  
      lcd.setCursor(17, 1);
      lcd.print(BPM);
      }
    lcd.setCursor(9, 2);
    lcd.write((byte) 0);
    lcd.write((byte) 0);
    delay(3000);
    if(BPM >= 40 && BPM <= 130)
    {
      lcd.setCursor(2, 2);
      lcd.print("You are healthy!");
      delay(2000);
      lcd.setCursor(2, 2);
      lcd.print("    Way to Go    ");
      lcd.setCursor(3, 3);
      lcd.print("Heartbeat Hero!");
      delay(3000);
      }
      if(BPM > 130)
      {
        lcd.setCursor(6, 2);
        lcd.print("Too High!");
        delay(2000);
        lcd.setCursor(4, 3);
        lcd.print("Take a break!");
        delay(3000);
        }
      if(BPM < 40)
      {
        lcd.setCursor(6, 2);
        lcd.print("Too Low!");
        delay(2000);
        lcd.setCursor(1, 3);
        lcd.print("Please see doctor!");
        delay(3000);
      }
    delay(2000);
  }