#pragma once

typedef struct
{
  int16_t temp_c;      // температура, °C
  uint32_t resistance; // сопротивление, Ом
} NtcPoint;
class Temperature
{
private:
  float voltage = 0.0F;
  float resistance;

  int getTempFromTable();

public:
  int getTemperature();
  Temperature &setVolt(float);
  static int getMaxT();
  static int getMinT();
  Temperature &setRes(int);
  float getVolt();
  float getRes();
};
