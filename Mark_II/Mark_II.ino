#include <ShiftRegister74HC595.h>

#define LEDn 5

int latchPin = 5;
int clkPin = 6;
int dataPin = 4;
byte LEDs[LEDn] = {16, 8, 4, 2, 1};
byte LEDp[LEDn] = {20, 50, 15, 5, 1};
byte LED = 0;

unsigned long t = 0;
unsigned long t_0 = 0;
unsigned long t_1 = 0;
byte contador = 0;

void setup() 
{
  //Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clkPin, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() 
{
  t = micros();
  if(t - t_0 >= 10)
  {
    LED = 0;
    for(int i = 0; i < LEDn; i++)
    {
      if(contador < LEDp[i])
      {
        LED |= LEDs[i];
      }
    }
    contador++;
    contador = contador>50?0:contador;
    shiftLED();
    t_0 = micros();
  }

  if(t - t_1 >= 60000)
  {
    UpdateLEDs();
    t_1 = micros();
  }
}
void UpdateLEDs(){
  for(int i = 0; i < LEDn; i++)
  {
    if(LEDs[i])
    {
      LEDs[i] = LEDs[i] << 1;
    }
    if(!LEDs[i])
    {
      LEDs[i] = 1;
    }
  }
}
void conlibreria(){
  
}
void shiftLED()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clkPin, MSBFIRST, LED);
   digitalWrite(latchPin, HIGH);
}

void printBinary(byte inByte)
{
  for(int b = 7; b >= 1; b--)
  {
    Serial.print(bitRead(inByte, b));
  }
  Serial.println(bitRead(inByte, 0));
}
