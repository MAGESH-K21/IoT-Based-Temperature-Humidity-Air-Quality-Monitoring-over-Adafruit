#include<ESP8266WiFi.h>
#include<Adafruit_MQTT_Client.h>
#include "MQ135.h" 
#include "DHT.h"
#define DHTPIN 4  
#define DHTTYPE DHT22
#define wifi "LAPTOP-EM3L65FK 5635"
#define password "harifree" 
#define server "io.adafruit.com"
#define port 1883
#define username "magesh_k"
#define key "aio_sJdf05E8Th3CjAY4di9sNLKbcrHO"
const int ANALOGPIN=0;
MQ135 gasSensor = MQ135(ANALOGPIN);
WiFiClient esp;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish feedg(&mqtt,username"/feeds/gas"); 
Adafruit_MQTT_Publish feedt(&mqtt,username"/feeds/temp"); 
Adafruit_MQTT_Publish feedh(&mqtt,username"/feeds/humidity"); 
void setup() 
{
Serial.begin(115200);
WiFi.begin(wifi,password);
dht.begin(); 
while (WiFi.status()!=WL_CONNECTED)
{delay(500);
Serial.print(".");
}
while(mqtt.connect())
{delay(500); 
Serial.print(".");
}
}
int timeSinceLastRead = 0;
void loop()
{if(mqtt.connected())
{float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) 
Serial.println("Failed to read from DHT sensor!");
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print("\n Sedinding the Humidity value");
if(feedh.publish(h))
Serial.println("Success");
else
Serial.println("Fail1");
Serial.print("\n Sedinding the temperature value");
if(feedt.publish(t))
Serial.println("Success");
else
Serial.println("Fail1");
float ppm = gasSensor.getPPM();
Serial.print("\n Sedinding the gas sensor value");
Serial.print(ppm);
Serial.printf("..."); 
if(feedg.publish(ppm))
Serial.println("Success");
else
Serial.println("Fail1");
delay(2000);  
  } 
}
