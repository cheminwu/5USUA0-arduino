#include "gym2go_GSM.h"
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>


const int RX = 8;
const int TX = 9;

//Network details
const char apn[]  = "TM";
const char user[] = "";
const char pass[] = "";

// MQTT details
const char* broker = "192.236.146.36";
const char* username = "guest_mqtt";
const char* password = "gym2go18";
const char* topicOut = "test";
const char* topicIn = "test";


SoftwareSerial SerialAT(RX,TX); // RX, TX
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);


String PK = "";


void publish(const char* topic, const char* message){
    mqtt.publish(topic, message);
}



String subscribePK(){
    return PK;
}



void gym2go_GSM_setup(){

    Serial.begin(9600);
    SerialAT.begin(9600);

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
    Serial.println("Connecting to MQTT Broker: " + String(broker));
    while(mqttConnect()==false) continue;
    Serial.println();
}

void gym2go_GSM_in_loop(){
  if(mqtt.connected())
  {
    mqtt.loop();
  }
}

boolean mqttConnect()
{
  if(!mqtt.connect("Gym2goGSM", username, password))
  {
    Serial.print(".");
    return false;
  }
  Serial.println("Connected to broker.");
  mqtt.subscribe("publicKey");
  mqtt.subscribe("test");
  publish("start", "0");
  return mqtt.connected();
}

void mqttCallback(char* topic, byte* payload, unsigned int len)
{
  Serial.print("Message receive: ");
  Serial.write(payload, len);
  if(topic == "publicKey"){
    PK = (char *)payload;
  }
  Serial.println();
}