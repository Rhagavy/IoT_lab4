// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

DeviceAddress deviceAddress;
//will store address as a string
String address;
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 


  //get device address
  DS18B20.getAddress(deviceAddress,0);
  //print address and store in string
  for(uint8_t i = 0; i<8; i++){
    address+=String(deviceAddress[i],HEX);
    //Serial.print(String(deviceAddress[i],HEX));
  }
  Serial.println("Found DS18b20 sensor with address: "+address);
}

//check if error message is printed already 
bool printedMessage = false;

void loop() { 

  float fTemp; 
  //check if sensor is connected
  if(DS18B20.getAddress(deviceAddress,0)!= 1){
    if(printedMessage == false){
      Serial.println("No DS18B2 temperture sensore are installed!");
      printedMessage = true;
    }

    return;
  }

  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 

  //check which temperature message to print
  if(fTemp<10){
     Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or Cold!"); 
  }else if(fTemp>10 && fTemp<15){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or Cool"); 
  }else if(fTemp>15 && fTemp<25){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or Perfect"); 
  }else if(fTemp>25 && fTemp<30){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or Warm"); 
  }else if (fTemp>30 && fTemp<35){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or Hot"); 
  } else{
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or Too Hot!"); 
  }
  printedMessage = false;

  // wait 2s (2000ms) before doing this again 
  delay(2000); 
} 