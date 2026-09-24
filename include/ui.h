#pragma once
#include <stdint.h>
#include <U8g2lib.h>
#include "menuUi.h"

#define DEFAULT_SIZE 24

// compile-time check: T must be U8G2 or derived from it
// thanks you, ai
template <typename D, typename B>
struct isU8G2Derived
{
private:
  struct No
  {
  };
  struct Yes
  {
    No no[2];
  };
  static Yes test(B *)
  {
    return Yes();
  }
  static No test(...)
  {
    return No();
  }

public:
  static const bool value = sizeof(test(static_cast<D *>(0))) == sizeof(Yes);
};

template <typename T>
class UI : public T // U8G2
{
  static_assert(isU8G2Derived<T, U8G2>::value,
                "UI<T>: T must be a U8G2 display class");

private:
  float _temperature;
  float _resistance;
  int _errorCode = 0;
  int _acp;
  char tempText[DEFAULT_SIZE];
  // char hysteresisText[DEFAULT_SIZE];
  char acpText[DEFAULT_SIZE];
  char resText[DEFAULT_SIZE];
  // char userTempText[DEFAULT_SIZE];
  // char burnerText[DEFAULT_SIZE];

  // void setText(char*, size_t, const char*, ...);
  MenuUI *menuUI;
  void main();

public:
  UI();
  void initUI();
  ~UI()
  {
    delete menuUI;
  }
  UI &setTemperature(float);
  void draw();
  UI &setACP(int);
  UI &setRes(float);
  MenuUI &getMenuUI();
  void startWindow();
  int drawCentered(const char *, int padding_top = 0, int padding_bottom = 0, int padding_left = 0, int padding_right = 0);
};