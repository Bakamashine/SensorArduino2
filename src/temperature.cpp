#include <Arduino.h>
#include "temperature.h"
#include "helper.h"
#include "avr/pgmspace.h"
#include "settings.h"
#include "constants/constants.h"

#define MIN_T -10
#define MAX_T 110

#define ATTEMPTS 5

#define MAX_ACP 1023
#define VCC 5
#define RESISTOR_FROM_SENSOR 2000 // 2kOm

static const NtcPoint ntcTable[] PROGMEM = {
    // temperature | om
    {-34, 55400},
    {-33, 51760},
    {-32, 48100},
    {-31, 46700},
    {-30, 45300},
    {-29, 41200},
    {-28, 39300},
    {-27, 38200},
    {-26, 34800},
    {-25, 33600},
    {-24, 31300},
    {-23, 29700},
    {-22, 28200},
    {-21, 26400},
    {-20, 24900},
    {-19, 23900},
    {-18, 22800},
    {-17, 21400},
    {-16, 20600},
    {-15, 18760},
    {-14, 17910},
    {-13, 17080},
    {-12, 16700},
    {-11, 15705},
    {-10, 14710},
    {-9, 13900},
    {-8, 13310},
    {-7, 12780},
    {-6, 12300},
    {-5, 11590},
    {-4, 11060},
    {-3, 10280},
    {-2, 10000},
    {-1, 9360},
    {0, 9100},
    {1, 8655},
    {2, 8210},
    {3, 7740},
    {4, 7400},
    {5, 7000},
    {6, 6750},
    {7, 6500},
    {8, 6180},
    {9, 5830},
    {10, 5630},
    {11, 5260},
    {12, 4970},
    {13, 4735},
    {14, 4500},
    {15, 4340},
    {16, 4170},
    {17, 3980},
    {18, 3780},
    {19, 3680},
    {20, 3450},
    {21, 3270},
    {22, 3140},
    {23, 3010},
    {24, 2890},
    {25, 2760},
    {26, 2640},
    {27, 2530},
    {28, 2410},
    {29, 2300},
    {30, 2190},
    {31, 2100},
    {32, 2010},
    {33, 1949},
    {34, 1870},
    {35, 1790},
    {36, 1718},
    {37, 1642},
    {38, 1580},
    {39, 1519},
    {40, 1451},
    {41, 1396},
    {42, 1343},
    {43, 1291},
    {44, 1243},
    {45, 1195},
    {46, 1147},
    {47, 1103},
    {48, 1063},
    {49, 1022},
    {50, 982},
    {51, 942},
    {52, 902},
    {53, 870},
    {54, 839},
    {55, 808},
    {56, 775},
    {57, 746},
    {58, 720},
    {59, 696},
    {60, 673},
    {61, 649},
    {62, 624},
    {63, 601},
    {64, 579},
    {65, 557},
    {66, 537},
    {67, 518},
    {68, 500},
    {69, 482},
    {70, 464},
    {71, 448},
    {72, 433},
    {73, 419},
    {74, 406},
    {75, 394},
    {76, 382},
    {77, 369},
    {78, 357},
    {79, 345},
    {80, 333},
    {81, 322},
    {82, 311},
    {83, 300},
    {84, 290},
    {85, 281},
    {86, 272},
    {87, 263},
    {88, 255},
    {89, 246},
    {90, 238},
    {91, 230},
    {92, 222},
    {93, 215},
    {94, 208},
    {95, 201},
    {96, 195},
    {97, 189},
    {98, 183},
    {99, 178},
    {100, 174},
};
#define NTC_TABLE_SIZE (sizeof(ntcTable) / sizeof(ntcTable[0]))

int16_t Temperature::ntcTempAt(size_t i)
{
  return static_cast<int16_t>(pgm_read_word(&ntcTable[i].temp_c));
}
int32_t Temperature::ntcResAt(size_t i)
{
  return static_cast<int32_t>(pgm_read_dword(&ntcTable[i].resistance));
}

int16_t Temperature::getTemperature()
{
  int values[ATTEMPTS];
  for (int i = 0; i < ATTEMPTS; i++)
  {
    // setRes(analogRead(SENSOR_PIN));
    values[i] = getTempFromTable() + Settings::getCorrectInt();
  }
  return getAvarageValue(values, ATTEMPTS);
}

// Temperature &Temperature::setVolt(float voltage)
// {
//   this->_volt = voltage;
//   return *this;
// }

int Temperature::getMaxT()
{
  return MAX_T;
}

int Temperature::getMinT()
{
  return MIN_T;
}

// float Temperature::getVolt() { return _volt; }

Temperature &Temperature::setAcp(int acp)
{
  _acp = acp;
  return *this;
}

Temperature &Temperature::setRes(int acp)
{
  if (acp == 0)
  {
    _resist = 0;
    return *this;
  }
  _resist = RESISTOR_FROM_SENSOR * (float)acp / (MAX_ACP - acp);
  return *this;
}

int16_t Temperature::getTempFromTable()
{

  // get max or min value
  if (_resist >= ntcResAt(0))
    return ntcTempAt(0);
  if (_resist <= ntcResAt(NTC_TABLE_SIZE - 1))
    return ntcTempAt(NTC_TABLE_SIZE - 1);

  for (size_t i = 0; i + 1 < NTC_TABLE_SIZE; i++)
  {
    int16_t _temp = ntcTempAt(i);
    int32_t _res = ntcResAt(i);

    if (_resist > _res)
      continue;
    if (_resist < ntcResAt(i + 1))
      continue;

    //  rounding returning number
    float fraction = (float)(_res - _resist) /
                     (_res - ntcResAt(i + 1));
    return _temp +
           (int)(fraction * (ntcTempAt(i + 1) - _temp) + 0.5F);
  }
  return 0;
}

ld Temperature::getRes() { return _resist; }