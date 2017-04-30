#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"


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
const double currentThreshold = 2;
const float tempThreshold = 50;

const int toleranceTime = 1000;
//Creating the instances

DHT dht(tempPin, DHTTYPE);
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK,DIN,DC,CE,RST);



float getVoltage(){
  return analogRead(voltagePin)*5.0/1024*5.7/1.414;
}

const int sensorIn = A4;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module

double currVolt = 0;
double VRMS = 0;
double AmpsRMS = 0;

float getCurr(){

 currVolt = getVPP();
 VRMS = (currVolt/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 return AmpsRMS;
}

float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
}

float readTemp(){
  float t = dht.readTemperature();
  return t;

}

void setup(){
  Serial.begin(9600);
  pinMode(loadRelay,OUTPUT);
  pinMode(fanRelay,OUTPUT);
  digitalWrite(loadRelay,HIGH);
  digitalWrite(fanRelay,HIGH);
  display.begin();

  display.setContrast(50);


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10,15);
  display.println("Transformer");
  display.println("  Protection");
  display.display();
  delay(1000);
  display.clearDisplay();

}

float Voltage;
float Current;
float Temp;

bool stateOfLoad = HIGH;
bool stateOfFan = HIGH;

void loop(){
  Voltage = getVoltage();
  Current = getCurr();
  Temp = readTemp();
  display.clearDisplay();
  display.print("V:");
  display.println(Voltage);
  display.print("I:");

  display.println(Current);  
  display.print("T:");
  display.println(Temp);
  Serial.print(Voltage);
  Serial.print("\t");
  Serial.println(Current);
  

 
  if(Voltage>voltageThreshold){
    if(stateOfLoad == HIGH){
      stateOfLoad = LOW;
      delay(500);
      digitalWrite(loadRelay,LOW);
    }
    display.println("\nOvervoltage !");
    delay(500);
  }
  if(Current>currentThreshold){
    if(stateOfLoad == HIGH){
      stateOfLoad = LOW;
      delay(500);
      digitalWrite(loadRelay,LOW);
    }
    display.println("\nOvercurrent !");
    delay(500);
  }
  if(Temp>tempThreshold){
    if(stateOfFan == HIGH){
      stateOfFan = LOW;
      delay(500);
      digitalWrite(fanRelay,LOW);
    }
    display.println("\nOvertemperature !");
    delay(500);
  }
  if((Voltage<=voltageThreshold)&&(Current<=currentThreshold)&&(Temp<=tempThreshold)){
    display.println("\nStatus:OK");
  }
  display.display();
  if(Temp<=tempThreshold){
    digitalWrite(fanRelay,HIGH);
  }
  delay(20);


}
