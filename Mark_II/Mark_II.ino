//#include <ShiftRegister74HC595.h>

#define CLK_T 50

int latchPin = 5;
int clkPin = 6;
int dataPin = 4;
byte LED = 0;
byte clk = 0b01000000;
byte estado = 0;
bool data_flag = 0;
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
}
void loop() 
{
  t = micros();
  
  //Reloj
  if(t - t_0 > CLK_T)
  {
    PORTD = (clk&0b00000001)?PORTD&clk:PORTD|clk;
    clk = ~clk;
    t_0 = micros();
    clock_flag = 1;
  }
  else if((t - t_0 >= CLK_T/2)*clock_flag)
  {
    clock_flag = 0;
    if((t - t_2) > (unsigned long)5000*CLK_T)
    {
      data_flag = 0;
      //Latch a LOW
      PORTD &= 0b11011111;
    }
    if(estado >= 8)
    {
      estado = 0;
      //Latch a HIGH
      PORTD |= 0b00100000;
      if(LED)
        LED = LED<<1;
      if(!LED)
        LED = 1;
      data_flag = 1;
      t_2 = micros();
    }
    if((clk&0b01000000) != 0 && data_flag == 0)
    { 
      //DATA = 4
      PORTD |= (((0x01<<estado)&LED)>>estado)<<4;
      PORTD &= ~((((0x01<<estado)&~LED)>>estado)<<4);
      estado++;
    }
  }
}
