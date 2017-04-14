//Vishal Kumar In the house
#include "DHT.h"         
#include "font.h"

//Nokia 5110 Display Variables

#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

// DHT Variables

#define DHTPIN 2         
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);

// LCD Writer

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

float readTemp(){
  float t = dht.readTemperature();
  return t;
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
  
  //DHT Start
  dht.begin(); 

  //Display Data Input
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
  clearScreen();

}
char voltStr[8];
char currStr[8];
char tempStr[8];

void loop() {

  
  float voltage = analogRead(A4)*5.0/1024;
  lcdXY(0,1);
  lcdWrite("V");
  lcdXY(40,1); 
  lcdWrite(dtostrf(voltage,5,2,voltStr));
  lcdWrite(" V");

  float x = 0;
  lcdXY(0,2);
  lcdWrite("I");
  lcdXY(40,2); 
  lcdWrite(dtostrf(x,5,2,currStr));
  lcdWrite(" A");

  
  float temp = readTemp();
  lcdXY(0,3);
  lcdWrite("T");
  lcdXY(40,3); 
  lcdWrite(dtostrf(temp,5,2,tempStr));
  lcdWrite("`C");

  lcdXY(18,5);
  lcdWrite("Status:OK");
  
}
