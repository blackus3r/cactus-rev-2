//This is a extended Sketch for the Cactus Rev 2 to read the value from a soil moisture sensor. With a anti oxidation functionality. 
//You can find the tutorial on http://derpade.de/
//@author Patrick Hausmann <privat@patrick-designs.de>

int soilMoisturePin1 = 4;
int soilMoisturePin2 = 3;
int soilMoisturePin3 = A3;
int baudrate = 9600;

void setup() 
{
  Serial.begin( baudrate );
  while(!Serial); //Waiting for Serial connection
}

int readSoilMoisture()
{
   int value; 
  
   pinMode(soilMoisturePin1, OUTPUT);
   pinMode(soilMoisturePin2, OUTPUT);

   digitalWrite(soilMoisturePin1, HIGH);
   digitalWrite(soilMoisturePin2, LOW);
   delay(500);

   value = analogRead(soilMoisturePin3);

   digitalWrite(soilMoisturePin2, HIGH);
   digitalWrite(soilMoisturePin1, LOW);
   delay(500);

   digitalWrite(soilMoisturePin2, LOW);
   return value;
}

void loop() 
{
  int value_water = readSoilMoisture(); 
  String water = String((int)((((double)value_water/1023.0)*100.0)));//Convert Raw value to percentage. This is a generic calculation, depending on raw values from 0 to 1023. 
  Serial.print("Soil moisture: ");
  Serial.print(water);
  Serial.print("% Raw value: ");
  Serial.println( value_water );

  delay(3000);
}

