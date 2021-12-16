/*
  Iron Man Core by Marce
  CREA Club de Robótica Electrónica y Automática
*/
#include <math.h>

// This section is only used in polarJojaluh
#define HALF_AMP (float)(TWO_PI*2/10) // Amplitude of half the angle in which LEDs will be on
#define DELAY (unsigned int)7 // Changes speed
#define VANG (float)0.05 // Angle added at the end of every loop. Can be considered constant

const static int nLeds = 10;
static float axisAngle, ledAngle;
static float angDist;
static int intensity;

void inline polarJojaluh(void);

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  
}

// the loop function runs over and over again forever
void loop() {
  polarJojaluh();
}

int intermitente(){
  for(int i=3; i<=12; i++){
    digitalWrite(i, HIGH);
  };
  delay(500);
  for(int i=3; i<=12; i++){
    digitalWrite(i, LOW);
  };
  delay(500);
}
int breath(){
  for(int i=0; i<=255; i=i+5){
    for(int j=2; j<=12; j++){
      analogWrite(j, i);
    };
    delay(50);
  };
  delay(400);
  for(int i=255; i>=0; i=i-5){
    for(int j=2; j<=12; j++){
      analogWrite(j, i);
    };
    delay(50);
  };
  delay(500);
}
int heart(){
  for(int i=0; i<=255; i=i+5){
    for(int j=3; j<=12; j++){
      analogWrite(j, i);
    };
    delay(5);
  };
  delay(200);
  for(int i=255; i>=0; i=i-5){
    for(int j=3; j<=12; j++){
      analogWrite(j, i);
    };
    delay(10);
  };
}
int rosco(){
  for(int i=3; i<=12; i++){
    digitalWrite(i,HIGH);
    delay(50);
  };
  for(int i=3; i<=12; i++){
    digitalWrite(i,LOW);
    delay(50);
  };
}
int solitario(){
  int vls[5] = {54,128,255,128,54};
  for (int i = 3; i<=12;i++){
    for (int j = 0; j<=4; j++){
      analogWrite(i,vls[j]);
      delay(100);
    }
    analogWrite(i,0);
  }
}

int jojalu(){
  int l[2][7]={{0,0,0,0,0,0,0},{0,75,150,255,150,75,0}};
  for(int i=3;i<=12;i++){
    for(int j=0;j<7;j++){
      l[0][j]=i+j;
      if (l[0][j]>12){
        l[0][j]=l[0][j] - 10;
      }
      for(int h=0;h<7;h++){
          analogWrite(l[0][h],l[1][h]);
          delay(2);
        }
      }
   }
}

void inline polarJojaluh(void) {
  for (int led = 0; led < nLeds; led++) {
    // We calculate the angle from the virtual rotatinng axis to it
    // There are two angles, anti- and clockwise, so we take the minimum
    ledAngle = static_cast<float>(led)/(nLeds+1) * TWO_PI;
    angDist = min(abs(ledAngle - axisAngle), abs(TWO_PI + ledAngle - axisAngle)); // Distance between angles should never be more than half circunference, so we compute the lower of the two possible angles
    if (angDist < HALF_AMP) // Set brightness only when it is near the amplitude defined
      intensity = static_cast<int>(255*(HALF_AMP-angDist)/HALF_AMP + 0.5); // The nearer to ledAngle, the brighter the LED
    else
      intensity = 0;
    analogWrite(led+3, intensity);
  }
  axisAngle += VANG;
  if (axisAngle > TWO_PI) // Reset angle to 0 every virtual axis loop
    axisAngle = 0;
  delay(DELAY);
}
