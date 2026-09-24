#pragma once

class Error
{
private:
  int code = 0;

public:
  Error();
  static const char *getErrorMessage(int code);
  void setErrorCodeAndStatus(int code);
};