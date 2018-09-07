#include <ESP8266WiFi.h>  
#include "ioControl.h"

const char *ssid = "sole";
const char *password = "Caracas212";
WiFiServer server (80);
int LED_V = 12;
int LED_A = 14;
int Boton = 4;
int contador = 0;
//volatile byte cuenta_fallas = 0;
bool estado = LOW;   
bool cosa = HIGH;//Definimos la variable que va a recoger el estado del LED
bool estado2 = LOW;                         //Definimos la variable que va a recoger el estado del LED
bool temp = true;

void setup() {
  // put your setup code here, to run once:

  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password); 
  Serial.begin(115200); // Para el debug
  pinMode(LED_V, OUTPUT);
  digitalWrite(LED_V, LOW);
  
  pinMode(LED_A, OUTPUT);
  digitalWrite(LED_A, LOW);
  server.begin();
  
}

void loop() {

   Serial.println(WiFi.softAPIP());
 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait for data from client to become available
  while(client.connected() && !client.available()){
    delay(1);
  }
  
  // Read the first line of HTTP request
  String req = client.readStringUntil('\r');
  
  // First line of HTTP request looks like "GET /path HTTP/1.1"
  // Retrieve the "/path" part by finding the spaces
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    return;
  }
  req = req.substring(addr_start + 1, addr_end);
  client.flush();
  
  String s;
  if (req == "/")
  {
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    s += file1;
  }

   
  
  
  else if (req.indexOf("LED1")!=-1)
  {
    if(req.indexOf("on")!=-1)
   
   {digitalWrite(LED_A,LOW);
    delay(200);
    digitalWrite(LED_V,HIGH);
    
       }
    else
    digitalWrite(LED_V,LOW);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    s += file1;
  }

  else if (req.indexOf("LED2")!=-1)
  {
    if(req.indexOf("on")!=-1)
    {
      digitalWrite(LED_V,LOW);
      delay(200);
      digitalWrite(LED_A,HIGH);
      
     //digitalWrite(LED_A,LOW);
     }
    else
    digitalWrite(LED_A,LOW);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    s += file1;
  }
  
  
 else if (req.indexOf("LED3")!=-1)
  {
    if(req.indexOf("on")!=-1)
    {digitalWrite(LED_A,LOW);
     digitalWrite(LED_V,LOW);
        }
    else
    {digitalWrite(LED_A,LOW);
     digitalWrite(LED_V,LOW);
    }
   
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    s += file1;
  }
  else
  {
    s = "HTTP/1.1 404 Not Found\r\n\r\n";
  }
  
  while(s.length()>2000)
  {
   String dummy = s.substring(0,2000);
   client.print(dummy);
   s.replace(dummy,"");
  }
  client.print(s);
}

