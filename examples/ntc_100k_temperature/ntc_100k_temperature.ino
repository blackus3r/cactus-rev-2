//This is a simple example to read and convert the value of a 100K Ohm NTC Thermistor. 
//You can find the tutorial on http://derpade.de/
//@author Patrick Hausmann <privat@patrick-designs.de>

#include <math.h>

double convertRawToTemperature(int raw, bool celsius) 
{
 double temperatureInF;
 
 temperatureInF = log(10000.0*((1024.0/raw-1))); 
 temperatureInF = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperatureInF * temperatureInF ))* temperatureInF );
 temperatureInF = temperatureInF - 273.15;          
 
 if (celsius==false) temperatureInF = (temperatureInF * 9.0)/ 5.0 + 32.0; 
 
 return temperatureInF;
}

void setup() 
{
 Serial.begin(9600);
}

void loop() 
{             
  int rawTemperatur;
  double temperaturInF;
  double temperaturInC;   
           
  rawTemperatur = analogRead(A10);
        
  temperaturInF = convertRawToTemperature(rawTemperatur, false);   
  temperaturInC = convertRawToTemperature(rawTemperatur, true); 
  
  Serial.print("Temperature: ");
  Serial.print(temperaturInF);   
  Serial.print("° F; ");
  Serial.print(temperaturInC);   
  Serial.println("! C");
  delay(50);            
}
