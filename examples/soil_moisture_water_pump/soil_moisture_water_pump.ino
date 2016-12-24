//This is a extended Sketch for the Cactus Rev 2 to read the value from a soil moisture sensorw ith a anti oxidation functionality and
//also to controll a water pump for watering a plant for example. 
//You can find the tutorial on http://derpade.de/
//@author Patrick Hausmann <privat@patrick-designs.de>

int soilMoisturePin1 = 4;
int soilMoisturePin2 = 3;
int soilMoisturePin3 = A3;
int baudrate = 9600;

//Transistor 'Base' pin or input pin of motor driver ic to Arduino PWM Digital Pin 3
const int motorPin = 9;

int Speed; //Variable to store Speed, by defaul 0 PWM
int flag;

void setup() 
{
  pinMode(motorPin, OUTPUT); //Set pin 3 as an OUTPUT
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

//Check if incoming data is available:
    if (water.toInt() < 20)
    {
      Serial.println("Too dry, we should water it.");
      Speed = 100;
      flag=0;
    }
    else 
    {
      Serial.println("Still wet, no need to water it.");
      Speed = 0;
    }

 
  if (Speed>=50 && Speed<=255)
  {
   
    analogWrite(motorPin, Speed);
      
      if (flag==0)
      { 
        Serial.print("Motor spinning with ");
        Serial.print(Speed);
        Serial.println(" PWM");
        flag=1;
      }
  }
  else if (Speed == 0) 
  {
    analogWrite(motorPin, Speed);
  }

  delay(3000);
}

