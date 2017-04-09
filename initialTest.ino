//Nokia 5110 Display Variables

#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

// LCD Writer

void lcdWrite(byte cmd){
  digitalWrite(DC,LOW);
  digitalWrite(CE,LOW);
  shiftOut(DIN,CLK,MSBFIRST,cmd);
  digitalWrite(CE,HIGH);
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

  
}

void loop() {

}
