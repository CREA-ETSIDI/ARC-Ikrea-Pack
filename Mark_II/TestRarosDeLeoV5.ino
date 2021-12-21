//#include <ShiftRegister74HC595.h>

#define CLK_T 50

//byte LED = 0;
byte LEDs[8][5] = {
  {0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001},
  {0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010},
  {0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100},
  {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000},
  {0b00000001, 0b10000000, 0b01000000, 0b00100000, 0b00010000},
  {0b00000010, 0b00000001, 0b10000000, 0b01000000, 0b00100000},
  {0b00000100, 0b00000010, 0b00000001, 0b10000000, 0b01000000},
  {0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b10000000}
  };
byte LEDp[5] = {8, 50, 15, 5, 1};

byte clk = 0b01000000;
byte estado = 0;
bool data_flag = 0;
bool clock_flag = 1;
byte contador = 0;

unsigned long t_0 = 0;
unsigned long t_1 = 0;
unsigned long t_2 = 0;
unsigned long t = 0;


void setup() 
{
  DDRD |= 0b01110000;
  PORTD |= 0b00100000;
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
    contador++;
    contador = contador>50?0:contador;
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
      //actualizaLED();
      data_flag = 1;
      t_2 = micros();
    }
    if((clk&0b01000000) != 0 && data_flag == 0)
    {
      for(byte i = 0; i < 5; i++)
      {
        //DATA = 4
        PORTD |= (((0x01<<estado)&LEDs[estado][i])>>estado)<<4;
        PORTD &= ~((((0x01<<estado)&~LEDs[estado][i]&(contador > LEDp[i]))>>estado)<<4);
      }
      estado++;
    }
  }
}
