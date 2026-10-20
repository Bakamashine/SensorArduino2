#include "error.h"

const char *Error::getErrorMessage(int code) {
  switch (code) {
    case 1:
      return "Error 1: Closing";
    case 2:
      return "Error 2: Break";
    case 3:
      return "Error 3: Burner is broken";
    default:
      return "No error";
  }
}