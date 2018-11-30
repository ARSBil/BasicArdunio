#include <SoftwareSerial.h>

SoftwareSerial ESP8266(7,6);

String Network = "ARSBil"; 
String Password = "oa159753..oa";


void setup()
{

  Serial.begin(9600);
  
  ESP8266.begin(115200);
  ESP8266.println("AT+CIOBAUD=9600");
  readESP8266(4000);

  ESP8266.begin(9600);  
  InitESP8266();
  ConnectToWebsite();
}

void loop()
{
   while(ESP8266.available())
   {    
     Serial.println(ESP8266.readString());
   }  
   
}

/* Function to initialise ESP8266 */
void InitESP8266()
{  

  ESP8266.println("AT");
  readESP8266(2000);

  ESP8266.println("AT+CWMODE=3"); //Wifi mode
  readESP8266(5000);

  ESP8266.println("AT+CWJAP=\""+ Network + "\",\"" + Password +"\""); //connect wifi
  readESP8266(10000);

  ESP8266.println("AT+CIFSR"); // IP adress
  readESP8266(1000);

  ESP8266.println("AT+CIPMUX=1");  // multiple connections 
  readESP8266(1000);

}

/* Function to connect to the server */
void ConnectToWebsite()
{

  ESP8266.println("AT+CIPSTART=1,\"TCP\",\"www.arsbil.com\",80"); //connect to website
  readESP8266(10000);

  ESP8266.println("AT+CIPSEND=1,114"); 
  readESP8266(2000);

  String httpreq = "GET /index.php?ldata=233 HTTP/1.1";
  // Make a HTTP request:
  ESP8266.println(httpreq);
  readESP8266(10000);

  ESP8266.println("Host: www.arsbil.com");
  ESP8266.println("Connection: keep-alive");
  ESP8266.println("");   
  readESP8266(5000);

  Serial.println("\r\n");
}


//read and display message
void readESP8266(const int timeout)
{
  String reponse = "";
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(ESP8266.available())
    {
      char c = ESP8266.read();
      reponse+=c;
    }
  }
  Serial.print(reponse);   
}
