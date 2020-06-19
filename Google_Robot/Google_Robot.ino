#include "Adafruit_MQTT_Client.h"
#include "Adafruit_MQTT.h"
#include <ESP8266WiFi.h>

WiFiClient client;

//-----------------Google assistant variables--------------------//
#define server_dns      "io.adafruit.com"
#define server_port  1883                   // use 8883 for SSL
#define key         "70435ac5e3db44dc968ddb9ce5d17c0a"   // Replace with your Project Auth Key
#define username_ada    ""            // Replace it with your username
#define ssid       ""             // Your SSID
#define password       ""        // Your password
//--------------------------------------------------------------//

//----------------------------------Ultrasonic sensor variables----------------------------------//

//------------------seed----------------//
int trigPin_seed = 3;
int echoPin_seed = 4;
long duration_seed = 0; 
int distance_seed = 0;
//----------------water_level-------------//
int trigPin_water_level = 5;
int echoPin_water_level = 6;
long duration_water_level = 0; 
int distance_water_level = 0;

//----------------------------------------------------------------------//

//----------------------ESP8266 is the MQTT cLIENT-------------------------//
Adafruit_MQTT_Client mqtt(&client, server_dns, server_port, username_ada, key);

//-------------------------------------Publishing the data on the server---------------------------------------//
Adafruit_MQTT_Publish ultrasonic_water = Adafruit_MQTT_Publish(&mqtt, username_ada "/feeds/waterlevel");
Adafruit_MQTT_Publish ultrasonic_seed = Adafruit_MQTT_Publish(&mqtt, username_ada "/feeds/seedlevel");

//---------------------------------Subscribing to commands-------------------------------//
Adafruit_MQTT_Subscribe Forward = Adafruit_MQTT_Subscribe(&mqtt, username_ada"/feeds/Forward"); // FeedName
Adafruit_MQTT_Subscribe Left = Adafruit_MQTT_Subscribe(&mqtt, username_ada "/feeds/Left");
Adafruit_MQTT_Subscribe Right = Adafruit_MQTT_Subscribe(&mqtt, username_ada "/feeds/Right");
Adafruit_MQTT_Subscribe Back = Adafruit_MQTT_Subscribe(&mqtt, username_ada "/feeds/Back");
Adafruit_MQTT_Subscribe Stop = Adafruit_MQTT_Subscribe(&mqtt, username_ada "/feeds/Stop");
Adafruit_MQTT_Subscribe *command;

void connect_mqtt_server();
int calculateDistance_seed();
int calculateDistance_water_level();

void setup() {
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());
 
  mqtt.subscribe(&Forward);
  mqtt.subscribe(&Left);
  mqtt.subscribe(&Right);
  mqtt.subscribe(&Back);
  mqtt.subscribe(&Stop);

  pinMode(2,OUTPUT);
  connect_mqtt_server();
}

void loop() 
{

  if (!mqtt.connected())
    connect_mqtt_server();
  
  while ((command = mqtt.readSubscription(20000))) 
  {
    if (command == &Forward) 
   {          
             Serial.print("Forward");
              //-----------------------------------seed level----------------------------------//
         /*     distance_seed = calculateDistance_seed();
              //----------------------------------water level---------------------------------//
              distance_water_level = calculateDistance_water_level();
   if ( (distance_seed > 10) && (distance_water_level >10))
             Serial.print("Forward");
   else
        if (distance_seed < 10)
            ultrasonic_seed.publish(distance_seed);
        else if (distance_water_level < 10)    
            ultrasonic_water.publish(distance_water_level); */
   }
    if (command == &Left) 
            Serial.print("Left");
    if (command == &Right) 
              Serial.print("Right");
    if (command == &Back) 
              Serial.print("Back");
    if (command == &Stop) 
            Serial.print("Stop");
  }
   
   //-----------------------------------seed level----------------------------------//
   distance_seed = calculateDistance(trigPin_seed);
   Serial.println(distance_seed);
   ultrasonic_seed.publish(distance_seed);
   //----------------------------------water level---------------------------------//
   distance_water_level = calculateDistance(trigPin_water_level);
   Serial.println(distance_water_level);
   ultrasonic_water.publish(distance_water_level);
   
   //------------------------------------------------------------------------------//
   
 
}

void connect_mqtt_server() 
{

  int8_t ret;
  uint8_t try_again = 5;
  
 if (mqtt.connected()) {
    return;
  }
 
  while ((ret = mqtt.connect()) != 0) { 
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    try_again--;
    if (try_again == 0) {
        while (1);
    }
  }
}

int calculateDistance(int Pin)
{
  digitalWrite(Pin,LOW);
  delayMicroseconds(2);
  digitalWrite(Pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(Pin,LOW);
  duration=pulseIn(Pin,HIGH);
  distance=duration*0.17;
  return distance;
}  

  
