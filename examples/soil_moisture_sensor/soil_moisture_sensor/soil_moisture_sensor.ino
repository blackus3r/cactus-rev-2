//This is a simple Sketch for the Cactus Rev 2 to read the value from a soil moisture sensor. 
//You can find the tutorial on http://derpade.de/
//@author Patrick Hausmann <privat@patrick-designs.de>

int sensor_water = A3;
int baudrate = 9600;

void setup() 
{
  Serial.begin( baudrate );
  while(!Serial); //Waiting for Serial connection
}

void loop() 
{
  int value_water = analogRead(sensor_water); 
  String water = String((int)((((double)value_water/1023.0)*100.0)));//Convert Raw value to percentage. This is a generic calculation, depending on raw values from 0 to 1023. 
  Serial.print("Soil moisture: ");
  Serial.print(water);
  Serial.print("% Raw value: ");
  Serial.println( value_water );

  delay(3000);
}

