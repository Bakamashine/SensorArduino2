#pragma once
#include <Arduino.h>
typedef struct
{
  int16_t temp_c;      
  uint32_t resistance; 
} NtcPoint;
class Temperature
{
private:
  float voltage = 0.0F;
  float resistance;

  int16_t getTempFromTable();

public:
  int16_t getTemperature();
  Temperature &setVolt(float);
  static int getMaxT();
  static int getMinT();
  Temperature &setRes(int);
  float getVolt();
  float getRes();
  static inline int16_t ntcTempAt(size_t i);
  static inline int32_t ntcResAt(size_t i);
};
