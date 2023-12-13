#include "gym2go_GSM.h"
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>


const int RX = 10;
const int TX = 11;

//Network details
const char apn[]  = "TM";
const char user[] = "";
const char pass[] = "";

// MQTT details
const char* broker = "192.236.146.36";
const char* username = "guest_mqtt";
const char* password = "gym2go18";


SoftwareSerial SerialAT(RX,TX); // RX, TX
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);


String PK = "";
String time = "0";

void publish(String topic, String message){
    mqtt.publish(topic.c_str(), message.c_str());
}



String subscribePK(){
    return PK;
}

String startTime(){
    return time;
}


void gym2go_GSM_setup(){

    SerialAT.begin(9600);

    if(!SerialAT.available()){    
      // Serial.println("Serial not available.");
    }
    Serial.println("System start.");
    modem.restart();
    Serial.println("Modem: " + modem.getModemInfo());
    modem.simUnlock("1503");
    Serial.println("Searching for telco provider.");
    if(!modem.waitForNetwork())
    {
        Serial.println("fail");
        while(true);
    }
    Serial.println("Connected to telco.");
    Serial.println("Signal Quality: " + String(modem.getSignalQuality()));

    Serial.println("Connecting to GPRS network.");
    if (!modem.gprsConnect(apn, user, pass))
    {
        Serial.println("fail");
        while(true);
    }
    if (modem.isNetworkConnected()) { Serial.println("Network connected"); }
    Serial.println("Connected to GPRS: " + String(apn));

    mqtt.setServer(broker, 1883);
    mqtt.setCallback(mqttCallback);
    Serial.println("Connecting to MQTT Broker.");
    while(mqttConnect()==false) continue;
    Serial.println();
    delay(3000);
}

void gym2go_GSM_in_loop(){
  // if(mqtt.connected())
  // {
  //   // Serial.println("MQTT connected.");
  //   mqtt.loop();
  //   // Serial.println("loop.");

  // }else{
  //   Serial.println("reconnecting.");
  //    while(mqttConnect()==false) continue;
  // }
  mqtt.loop();
}

boolean mqttConnect()
{
  if(!mqtt.connect("Gym2goGSM", username, password))
  {
    Serial.print(".");
    return false;
  }
  Serial.println("Connected to broker.");
  mqtt.subscribe("key");
  mqtt.subscribe("time");
  Serial.println("MQTT topic 'publickey' subscribed.");
  Serial.println("MQTT topic 'time' subscribed.");
  mqtt.subscribe("test");
  Serial.println("MQTT topic 'test' subscribed.");

  publish("start", "0");
  Serial.println("MQTT topic 'start' published.");

  return mqtt.connected();
}

void mqttCallback(char* topic_, byte* payload, unsigned int len)
{
  String topic(topic_);
  // Serial.print("Message receive: ");
  // Serial.print(topic);
  // Serial.print(": ");
  // Serial.println(String((char *)payload));
  if(topic == "key"){
    PK = String((char *)payload).substring(0,16);
    //  Serial.print("set key: ");
    //  Serial.println(PK);
  }

  if(topic == "time"){
    // Serial.println("receive time");
    time = String((char *)payload);
    time = time.substring(0, time.indexOf("*"));
    // Serial.println(time);
    //  Serial.println(PK);
  }
  Serial.println();
}
