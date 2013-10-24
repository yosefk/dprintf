#include "dprintf.h"
#include <fstream>

#define N 1024
dcell g_data[N];
dbuf g_dbuf = {g_data, g_data+N};

void dflush() {
  static std::ofstream out("dprintf.raw");
  out.write((char*)g_data, sizeof(dcell)*(g_dbuf.curr - g_data));
  out.flush();
  g_dbuf.curr = g_data;
}
