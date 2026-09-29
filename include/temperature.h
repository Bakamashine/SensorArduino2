#pragma once
#include <Arduino.h>
typedef long double ld;

class Temperature
{
private:
  // float _volt = 0.0F;
  ld _resist = 0;
  int _acp = 0;
  float _adcFilter = -1.0F;
  int16_t getTempFromTable(int rawAcp = 0);
  void sort(int16_t *array, size_t size);
  int16_t* removeMinMax(int16_t *array, size_t size);

public:
  int16_t getTemperature();
  static int getMaxT();
  static int getMinT();
  Temperature &setRes(int);
  Temperature &setAcp(int);
  int getAcp();
  ld getRes();
  static inline int16_t ntcTempAt(size_t i);
  static inline int32_t ntcResAt(size_t i);
};
