//IDE settings: Tools/Board: arduino nano, Processor:atmega168, Programmer: arduinoISP

// ***** I2CSoilMoistureSensor *****
#include <I2CSoilMoistureSensor.h>
#include <Wire.h>
I2CSoilMoistureSensor sensor(0x20); // 44, vagy 20 a cím, szállított műszertől függően más és más lehet

void setup() {
 Wire.begin();
 Serial.begin(9600); 

 sensor.begin(); // reset sensor
 delay(1000); // give some time to boot up
 
 Serial.println("Talajnedvesség-érzékelő 1.0, 8 csatornás relépanellel");
 Serial.println("Filename: rainsensing_arduino_nano_8channel_relay.ino");
 Serial.println(" ");
 Serial.print("I2C Soil Moisture Sensor Address: ");
// Serial.println(sensor.getAddress(),HEX);
 
 Serial.println("1 mp-nkénti mérés folyamatban");
 
  pinMode(LED_BUILTIN, OUTPUT);

//  relay_init();//initialize the relay
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(9, 1);
    digitalWrite(10, 1);
    digitalWrite(11, 1);
}
 
void loop() {
  int sensorValue6 = 0;
  const int analogInPin = A0;

  while (sensor.isBusy()) delay(50); // available since FW 2.3

 // A talajnedvességmérő mérési tartományának 170 egysége átmappelésre történik kb. 1000 egységre

  int y = 1;
  while (y < 7) {
    
  delay(1000); 
  
  Serial.print("Measurement no");
  Serial.print(y);
  Serial.print(". = ");
  Serial.print(map(sensor.getCapacitance(), 300, 670, 0, 100)); 
  Serial.println("%");
 
  sensorValue6 = sensorValue6 + map(sensor.getCapacitance(), 300, 670, 0, 100); 
 
  y = y + 1;
  
 }
 
  sensorValue6 = sensorValue6/6; 
  
  Serial.print("sensorValue6 = " ); 
  Serial.print(sensorValue6); 
  Serial.println("%");

 delay(1000); 
 
//ha nedves idő van kikapcsolja a relét
if (sensorValue6 > 15){
    digitalWrite(4, 1); //OFF
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(9, 1);
    digitalWrite(10, 1);
    digitalWrite(11, 1);
  Serial.println("relék kikapcsolása, nedves idő van, felesleges az öntözés");
  }   
else if (sensorValue6 <= 15)
  {
    digitalWrite(4, 0); //ON
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    Serial.println("relék bekapcsolása, száraz idő van, mehet az öntözés");
  }
  sensor.sleep(); // available since FW 2.3
}
