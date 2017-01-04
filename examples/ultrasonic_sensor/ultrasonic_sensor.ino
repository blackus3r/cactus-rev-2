//This is a simple example to control a ultra sonic sensor.
//You can find the tutorial on http://derpade.de/
//@author Patrick Hausmann <privat@patrick-designs.de>

#include <NewPing.h>

#define TRIGGER_PIN  9  
#define ECHO_PIN     10 
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() 
{
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() 
{
  delay(30);                  
  unsigned int pingTime = sonar.ping(); 
  Serial.print("Ping: ");
  Serial.print(pingTime / US_ROUNDTRIP_CM);
  Serial.println(" cm");
}
