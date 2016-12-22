//This is a working example to open an url with the Cactus Rev 2. 
//You can find the tutorial on http://derpade.de/tutorial-cactus-rev-2-esp8266-flashen
//@author Patrick Hausmann <privat@patrick-designs.de>

int wifiConnected = 0;
int status;
String GET;

#define DEBUG 0 // Please set DEBUG = 0 when USB not connected

#define _baudrate 9600
#define wifi_pin 13

#define SSID ""
#define PASS ""
#define IP "derpade.de"

void setup() 
{
 pinMode (13, OUTPUT);
 digitalWrite (13, HIGH);
 delay(1000);

 Serial.begin( _baudrate );
 Serial1.begin( _baudrate );

 if(DEBUG) 
 {
    while(!Serial);
 }

 Serial1.println("AT+RST");
 delay(3000);
 Serial1.println("AT+CWMODE=1");
 delay(300);
 Serial1.println("AT+RST");
 delay(500);

}


void loop() {

 digitalWrite (13, HIGH);

 sendDebug("AT+CIFSR");
 delay(300);
 if (Serial1.find("192.168."))
 {
    Serial.println("IP Test: OK");
 }
 else
 {
    Serial.println("IP Test: Failed");
    wifiConnected=0;
 }

 if(!wifiConnected)
 {
    Serial1.println("AT");
    delay(1000);
    if(Serial1.find("OK"))
    {
       Serial.println("Module Test: OK");
       connectWifi();
       if (wifiConnected)
       {
          String cmd = "AT+CIPMUX=1";

          sendDebug( cmd );

          if( Serial1.find( "Error") )
          {
            Serial.print( "RECEIVED: Error" );
            return;
          }
        }
    }
        else Serial.println("Module Test: failed");
 }

 if(!wifiConnected) {
 delay(500);
 return;
 }
 status=0;

 String cmd = "AT+CIPSTART=4,\"TCP\",\"derpade.de\",80";

 sendDebug(cmd);
 int serverConnection = 0;

 for(int i = 0; i < 30; i++)
 {
    Serial.print(".");
    if(Serial1.find("OK"))
    {
        serverConnection = 1;
        break;
    }

    delay(1000);
 }

 if(serverConnection)
 {
     Serial.println("Got a connection!"); //debug message
 }
 else
 {
     Serial.println("Error: No connection.");
     sendDebug( "AT+CIPCLOSE=4" );
     return;
 }

 cmd = "GET /test.php HTTP/1.1\r\nHost: derpade.de\r\nConnection: close\r\n\r\n";
 Serial1.print( "AT+CIPSEND=4,");
 Serial1.print( cmd.length());
 Serial1.println("\r\n");


 //display command in serial monitor
 Serial.print("AT+CIPSEND=4,");
 Serial.println( cmd.length() );

 Serial.println("Waiting for prompt");
 int prompt = 0;
 for(int i = 0; i < 30; i++)
 {
    Serial.print(".");
    if(Serial1.find(">"))
    {
        prompt = 1;
        break;
    }

  delay(50);
 }

  if(prompt)
  {
    // The line is useless
    //Serial1.print(">");
    Serial1.print(cmd);
    Serial1.println("\r\n");
    Serial.print(cmd);
    sendDebug( "AT+CIPCLOSE=4" );
  }
  else
  {
    Serial.println("No '>' prompt!");
    sendDebug( "AT+CIPCLOSE=4" );
    return;
  }

  if( Serial1.find("OK") )
  {
    Serial.println( "RECEIVED: OK" );
  }
  else
  {
    Serial.println( "RECEIVED: Error");
  }
}


void sendDebug(String cmd)
{
 Serial.print("SEND: ");
 Serial.println(cmd);
 Serial1.println(cmd);
}

boolean connectWifi()
{
 String cmd="AT+CWJAP=\"";
 cmd+=SSID;
 cmd+="\",\"";
 cmd+=PASS;
 cmd+="\"";
 Serial.println(cmd);
 Serial1.println(cmd);

 for(int i = 0; i < 30; i++) {
 Serial.print(".");
 if(Serial1.find("OK"))
 {
    wifiConnected = 1;

    break;
 }

 delay(50);
 }

 Serial.println(
 wifiConnected ?
 "OK, Connected to WiFi." :
 "Can not connect to the WiFi."
 );

 return wifiConnected;
}
