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
      
}

void loop() {

}
