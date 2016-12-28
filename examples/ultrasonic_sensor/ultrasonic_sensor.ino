
#include <NewPing.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

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
