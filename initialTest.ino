#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h" 

//TODO:Test the entire Circuit

// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS)
// pin 12 - LCD reset (RST)


#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8


#define voltagePin A3
#define currentPin A4
#define tempPin 2

#define DHTTYPE DHT11

#define loadRelay 3
#define fanRelay 4

const float voltageThreshold = 17;
const float currentThreshold = 2;
const float tempThreshold = 50;

//Creating the instances

DHT dht(tempPin, DHTTYPE);
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK,DIN,DC,CE,RST);


float getVoltage(){
  return analogRead(voltagePin)*5.0/1024*5.7/1.414;
}

float getCurrent(){
  int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
  int RawValue= 0;
  int ACSoffset = 2500; 
  double Voltage = 0;
  double Amps = 0;
  RawValue = analogRead(currentPin);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  
  return Amps;
}

float readTemp(){
  float t = dht.readTemperature();
  return t;
}




void setup()   {
  Serial.begin(9600);

  display.begin();
  
  display.setContrast(50);


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10,15);
  display.println("Transformer");
  display.println("  Protection");
  display.display();
  delay(2000);
  display.clearDisplay();

}

void loop(){
  
  display.clearDisplay();
  display.print("V:");
  display.println(getVoltage());
  display.print("I:");
  display.println(getCurrent());
  display.print("T:");
  display.println(readTemp());
  if(analogRead(A4)>500){
    display.println("\nStatus:Not Okay");
  }
  else{
    display.println("\nStatus:OK");
  }
  display.display();
  delay(20);
  
}
