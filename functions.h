char* str_state = "";
char* str_light_id = "";
char _msg[25];

void set_light(String,String);
void set_light_str(int);
void set_light_str(String light_id);

void transform_incoming_msg(String incoming_msg) {

  String device_id = "";
  String light_id = "";
  String state = "";
  int str_length = incoming_msg.length();
  char incoming_msg_c[str_length + 1];
  strcpy(incoming_msg_c, incoming_msg.c_str());
  int count = 0;
  
  char * partes = strtok(incoming_msg_c, "|");
  
   while( partes != NULL ) {
      //Serial.print("partes: " + String(partes));
      if(count == 0) {
        device_id = String(partes);
      } else if(count == 1) {
        light_id = String(partes);
      } else if (count == 2) {
        state = String(partes);
      }

      partes = strtok(NULL, "|");
      count++;
   }

   Serial.print("device_id: " + device_id);
   Serial.print("light_id: " + light_id);
   Serial.print("state: " + state);

   if(device_id.toInt() == DEVICE_ID)
    set_light(light_id,state);
}

void set_light(String  str_light_id, String str_state) {

  int state = LOW;
  
  if (str_state == "ON") {
    state = HIGH;
  }

  String str = String(str_light_id) + ":"+ String(state);
  digitalWrite(str_light_id.toInt(), state);
  Serial.print(str);
}

void set_light_str(String light_id){

  switch(light_id.toInt()) {
    case 19:
      str_light_id = "BLUE_LIGHT";
      break;

    case 21:
      str_light_id = "RED_LIGHT";
      break;

    case 22:
      str_light_id = "GREEN_LIGHT";
      break;

    case 23:
      str_light_id = "WHITE_LIGHT";
      break;
      
    default:
      str_light_id = "NO_LIGHT";
      break;
  }
}
