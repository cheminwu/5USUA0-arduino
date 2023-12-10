#ifndef gym2go_GSM_H
#define gym2go_GSM_H
#include <Arduino.h>

#define TINY_GSM_MODEM_SIM800

void publish(String topic, String message);
String subscribePK();
String startTime();
void gym2go_GSM_setup();
void gym2go_GSM_in_loop();
boolean mqttConnect();
void mqttCallback(char* topic, byte* payload, unsigned int len);

#endif