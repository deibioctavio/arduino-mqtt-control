#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

//**************************************
//*********** MQTT CONFIG **************
//**************************************
char *mqtt_server = "";
int mqtt_port = 0;
char *mqtt_user = "";
char *mqtt_pass = "";
char *root_topic_subscribe = "";
char *root_topic_publish = "";


//**************************************
//*********** WIFICONFIG ***************
//**************************************
char* ssid = "";
char* password =  "";



//**************************************
//*********** GLOBALES   ***************
//**************************************
WiFiClient espClient;
PubSubClient client(espClient);
char msg[25];
long count=0;


//************************
//** F U N C I O N E S ***
//************************
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();

/*void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}*/

/*void loop() {
  
  if (!client.connected()) {
    reconnect();
  }

  if (client.connected()){
    String str = "La cuenta es -> " + String(count);
    str.toCharArray(msg,25);
    client.publish(root_topic_publish,msg);
    count++;
    delay(300);
  }
  client.loop();
}*/




//*****************************
//***    CONEXION WIFI      ***
//*****************************
void setup_wifi(){
  delay(10);
  // Nos conectamos a nuestra red Wifi
  Serial.println();
  Serial.print("Conectando a ssid: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a red WiFi!");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}



//*****************************
//***    CONEXION MQTT      ***
//*****************************

void reconnect() {

  while (!client.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    // Creamos un cliente ID
    String clientId = "IOTICOS_H_W_";
    clientId += String(random(0xffff), HEX);
    // Intentamos conectar
    if (client.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
      Serial.println("Conectado!");
      // Nos suscribimos
      if(client.subscribe(root_topic_subscribe)){
        Serial.println("Suscripcion ok");
      }else{
        Serial.println("fallo Suscripciión");
      }
    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(client.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");
      delay(5000);
    }
  }
}


//*****************************
//***       CALLBACK        ***
//*****************************

void callback(char* topic, byte* payload, unsigned int length){
  String incoming = "";
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  
  incoming.trim();
  Serial.println("Mensaje -> " + incoming);
  transform_incoming_msg(incoming);
}

void set_mqtt_params(char* _mqtt_server, int _mqtt_port, char* _mqtt_user, char* _mqtt_pass,
char* _root_topic_subscribe, char* _root_topic_publish) {
  mqtt_server = _mqtt_server;
  mqtt_port = _mqtt_port;
  mqtt_user = _mqtt_user;
  mqtt_pass = _mqtt_pass;
  root_topic_subscribe = _root_topic_subscribe;
  root_topic_publish = _root_topic_publish;
 }

 void set_wifi_params(char* _ssid, char* _password) {
  ssid = _ssid;
  password =  _password;
 }
