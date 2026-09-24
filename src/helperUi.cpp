#include "helperUi.h"
#include <stdarg.h>

void setText(char *buf, size_t size, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, size, fmt, args);
  va_end(args);
}

void setFloatText(char *buf, size_t size, const char *label, float v)
{
  if (v < 0)
    v = -v;
  int whole = (int)v;
  int frac = (int)(v * 100) % 100;

  setText(buf, size, "%s: %d.%02d", label, whole, frac);
}