#ifndef DPRINTF_H_
#define DPRINTF_H_

#include <stdint.h>

typedef int32_t dcell;

struct dbuf {
  dcell* curr;
  dcell* finish;
};

extern dbuf g_dbuf;

inline dcell tocell(int x) { return x; }
inline dcell tocell(const char* p) { return (dcell)p; }
inline dcell tocell(float x) { union { int n; float f; } nf; nf.f = x; return nf.n; }
inline dcell tocell(double x) { return tocell((float)x); }

inline void dwrite(dcell* p) {}

template<class T, class... Rest>
inline void dwrite(dcell* p, T first, Rest... rest) {
  *p++ = tocell(first);
  dwrite(p, rest...);
}

template<class... Rest>
void dprintf(const char* fmt, Rest... args) {
  int n = sizeof...(args);
  int sz = n + 2;
  dcell* p = __sync_fetch_and_add(&g_dbuf.curr, sz*sizeof(dcell));
  if(p + sz < g_dbuf.finish) {
    *p++ = (dcell)fmt;
    *p++ = n;
    dwrite(p, args...);
  }
}

void dflush();

#endif

