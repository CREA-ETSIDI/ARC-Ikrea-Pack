#include <ShiftRegister74HC595.h>

#define CLK_T 10000

int latchPin = 5;
int clkPin = 6;
int dataPin = 4;
byte LED = 0;
byte clk = 0b01000000;
byte estado = 0;
bool flag = 0;
bool clock_flag = 1;

unsigned long t_0 = 0;
unsigned long t_1 = 0;
unsigned long t_2 = 0;
unsigned long t = 0;


void setup() 
{
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clkPin, OUTPUT);
  digitalWrite(latchPin, HIGH);
  pinMode(7,OUTPUT);
}
void loop() 
{
  t = micros();
  PORTB &= 0xFF&(flag<<5);
  PORTB |= 0x00|(flag<<5);
  
  //Reloj
  if(t - t_0 > CLK_T)
  {
    //Inicio Reloj
    t_0 = micros();
    PORTD = (clk&0b00000001)?PORTD&clk:PORTD|clk;
    clk = ~clk;
    //Fin Reloj

    clock_flag = 1;
  }
  else if((t - t_0 >= CLK_T/2)*clock_flag)
  {
    Serial.println("A");
    clock_flag = 0;
    
    flag = ((t - t_2) > 500000)?0:flag;
    if(estado >= 8)
    {
      estado = 0;
      //Latch a HIGH
      PORTD |= 0b00100000;
      
      if(LED)
        LED = LED<<1;
      if(!LED)
        LED = 1;
      flag = 1;
      t_2 = micros();
    }
    if((clk&0b01000000) == 0 && flag == 0)
    {
      //LATCH a LOW
      PORTD &= 0b11011111;
            
      //DATA = 4
      PORTD |= (((0x01<<estado)&LED)>>estado)<<4;
      PORTD &= (((0xFE<<estado)&LED)>>estado)<<4;
      estado++;
      //Serial.println(estado);
    }
    //Serial.println((flag == 0)?'a':'b');
  }
}
void sinlibreria(){
  int i=0;
  
  /*
  if(LED)
  {
    LED = LED<<1;
  }
  if(!LED)
  {
    LED = 1;
  }
  */
  
  delay(1000);
}
void conlibreria(){
  
}
void shiftLED()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clkPin, MSBFIRST, LED);
   digitalWrite(latchPin, HIGH);
}
