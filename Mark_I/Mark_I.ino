/*
  Iron Man Core by Marce
  CREA Club de Robótica Electrónica y Automática
*/
#include <math.h>
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
  jojalu();
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
int senos(){
  
  }
int jojalu(){
  int l[2][5]={{0,0,0,0,0},{0,150,255,150,0}};
  for(int i=2;i<=12;i++){
    for(int j=0;j<5;j++){
      l[0][j]=i+j;
      if (l[0][j]>12){
        l[0][j]=l[0][j] - 11;
      }
      for(int h=0;h<5;h++){
        analogWrite(l[0][h],l[1][h]);
        delay(2);
      }
    }
  }
}
