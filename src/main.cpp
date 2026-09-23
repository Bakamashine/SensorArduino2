#include <Arduino.h>
#include "constants.h"
#include "debugUi.h"
#include "temperature.h"

void sensorSetup();

DebugUI debugUI;
Temperature temp;

void setup()
{
  Serial.begin(BOD);

  sensorSetup();
}

void loop()
{
  int analRead = analogRead(SENSOR_PIN);
  float temperature = temp.setRes(analRead).getTemperature();
#ifdef DEBUG
  // Serial.println(temp.getVolt());
  // Serial.println(temp.getRes());
  // Serial.println(temperature);
  debugUI.fprintValue("Volt", temp.getVolt());
  debugUI.fprintValue("Resistance", temp.getRes());
  debugUI.fprintValue("Temperature", temperature);
#endif
}

void sensorSetup()
{
  pinMode(SENSOR_PIN, INPUT);
}