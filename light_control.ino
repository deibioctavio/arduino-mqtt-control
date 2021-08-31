#include <WiFi.h>
#include <PubSubClient.h>

#define BLUE_LIGHT 19
#define RED_LIGHT 21
#define GREEN_LIGHT 22
#define WHITE_LIGHT 23
#define UPLOAD_SPEED 115200
#define DEVICE_ID 1000001

#include "functions.h"
#include "mqtt.h"

//**************************************
//*********** MQTT CONFIG **************
//**************************************
char *global_mqtt_server = "ioticos.org";
int global_mqtt_port = 1883;
char *global_mqtt_user = "z1qz8W5S11PVq4r";
char *global_mqtt_pass = "tIIDdsg6ZTpLAmH";
char *global_root_topic_subscribe = "0WIrvRnAJpCzk3D";
char *global_root_topic_publish = "0WIrvRnAJpCzk3D";


//**************************************
//*********** WIFICONFIG ***************
//**************************************
char* global_ssid = "RCBFAMILY_E";
char* global_password =  "RCOLOMBIA2019";
 
void setup() {
  Serial.begin(UPLOAD_SPEED);
  pinMode(BLUE_LIGHT, OUTPUT);
  pinMode(RED_LIGHT, OUTPUT);
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(WHITE_LIGHT, OUTPUT);
  set_wifi_params(global_ssid, global_password);
  set_mqtt_params(global_mqtt_server, global_mqtt_port, global_mqtt_user, global_mqtt_pass, 
  global_root_topic_subscribe, global_root_topic_publish);
  setup_wifi();
  client.setServer(global_mqtt_server, global_mqtt_port);
  client.setCallback(callback);
}

void loop() {
  /*delay(1000);
  digitalWrite(BLUE_LIGHT, HIGH);
  Serial.print("B:ON ");
  delay(1000);
  digitalWrite(RED_LIGHT, HIGH);
  Serial.print("R:ON ");
  delay(1000);
  digitalWrite(GREEN_LIGHT, HIGH);
  Serial.print("G:ON ");
  delay(1000);
  digitalWrite(WHITE_LIGHT, HIGH);
  Serial.print("W:ON ");
  delay(1000);
  digitalWrite(WHITE_LIGHT, LOW);
  Serial.print("W:OFF ");
  delay(1000);
  digitalWrite(GREEN_LIGHT, LOW); 
  Serial.print("G:OFF ");
  delay(1000);
  digitalWrite(RED_LIGHT, LOW);
  Serial.print("R:OFF ");
  delay(1000);
  digitalWrite(BLUE_LIGHT, LOW);
  Serial.print("B:OFF ");*/

  if (!client.connected()) {
    reconnect();
  }

  if (client.connected()){
    /*String str = "La cuenta es -> " + String(count);
    str.toCharArray(msg,25);
    client.publish(root_topic_publish,msg);
    count++;
    delay(1000);*/
  }
  client.loop();
}



void wifi_scan(){
  Serial.println("wifi_scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");

  if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }

    Serial.println("wifi_scan done");
}
