
//Nokia 5110 Display Variables
#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

// LCD Writer

#include "font.h"

void lcdWriteData(byte dat){
  digitalWrite(DC,HIGH);
  digitalWrite(CE,LOW);
  shiftOut(DIN,CLK,MSBFIRST,dat);
  digitalWrite(CE,HIGH);
}


void lcdWriteCmd(byte cmd){
  digitalWrite(DC,LOW);
  digitalWrite(CE,LOW);
  shiftOut(DIN,CLK,MSBFIRST,cmd);
  digitalWrite(CE,HIGH);
}

void lcdWriteChar(char ch){
  for(int i=0;i<5;i++){
    lcdWriteData(ASCII[ch - 0x20][i]);
  }
  lcdWriteData(0x00);
}

void lcdWrite(char *chs){
  while(*chs){
    lcdWriteChar(*chs++);
  }
}

void clearScreen(){
  for(int i = 0; i<504;i++){
    lcdWriteData(0x00);
  }
}

void lcdXY(int x, int y){
  lcdWriteCmd(0x80 | x);
  lcdWriteCmd(0x40 | y);
}
void setup() {
  //Setting Pin Modes of Display
  pinMode(RST,OUTPUT);
  pinMode(CE,OUTPUT);
  pinMode(DC,OUTPUT);
  pinMode(DIN,OUTPUT);
  pinMode(CLK,OUTPUT);
  digitalWrite(RST,LOW);
  digitalWrite(RST,HIGH);
  

  lcdWriteCmd(0x21);
  lcdWriteCmd(0xB8);
  lcdWriteCmd(0x04);
  lcdWriteCmd(0x14);
  lcdWriteCmd(0x20);
  lcdWriteCmd(0x0C);

  clearScreen();
  
  lcdXY(15,2);
  lcdWrite("Transformer");
  lcdXY(16,3);
  lcdWrite("Protection");
  delay(5000);
  

}
char voltStr[8];
void loop() {
  float voltage = analogRead(A4)*(13.0/1024);
  lcdXY(0,2);
  lcdWrite("Voltage");
  lcdXY(49,2); 
  lcdWrite(dtostrf(voltage,5,2,voltStr));
  lcdWrite("V");
  if(voltage>11){
    lcdXY(20,3);
    lcdWrite("Danger!");
  }
  else{
    lcdXY(20,3);
    clearScreen();
  }
}
