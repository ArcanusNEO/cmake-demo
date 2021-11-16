#pragma once
#include <bits/stdc++.h>
using namespace std;
class FastIO {
public:
  //   #define getchar getchar_unlocked
  //   #define putchar putchar_unlocked
  //   #define fputs fputs_unlocked
#define endl '\n'
  char buf[64];
  bool bad{false};

  template<typename T>
  T abs(const T& x) const { return (x < 0 ? -x : x); }
  bool isw(int ch) const { return (ch <= ' ' || ch == 0x7f); }
  FastIO& operator << (const char& ch) {
    putchar(ch);
    return *this;
  }
  FastIO& operator << (char* str) {
    fputs(str, stdout);
    return *this;
  }
  FastIO& operator << (const char* const& str) {
    fputs(str, stdout);
    return *this;
  }
  FastIO& operator >> (char* str) {
    int ch;
    bad = true;
    //ignore white charactor
    //while (ch = getchar(), ~ch) {*str++ = ch; bad = false;}
    //stopped by white charactor
    while (ch = getchar(), ~ch && !isw(ch)) { *str++ = ch; bad = false; }
    //stopped by new line
    //while (ch = getchar(), ~ch && ch != '\r' && ch != '\n') {*str++ = ch; bad = false;}
    *str = '\0';
    return *this;
  }
  FastIO& operator >> (char& ch) {
    bad = true;
    while (ch = getchar(), ~ch && isw(ch)) {}
    if (~ch) { bad = false; }
    return *this;
  }
  template<typename T>
  FastIO& operator >> (T& x) {
    x = 0;
    int ch = getchar(), sig = 1;
    bad = true;
    while (~ch && isw(ch)) { ch = getchar(); }
    if (ch == '+') { ch = getchar(); } else if (ch == '-') { sig = -1; ch = getchar(); } else if (!(ch >= '0' && ch <= '9')) { return *this; }
    while (ch >= '0' && ch <= '9') {
      x = x * 10 + ch - '0';
      ch = getchar();
      bad = false;
    }
    x *= sig;
    return *this;
  }
  template<typename T>
  FastIO& operator << (T x) {
    if (x == 0) {
      putchar('0');
      return *this;
    }
    if (x < 0) { putchar('-'); }
    char* sp = buf;
    while (x) {
      *sp++ = abs(x % 10) + '0';
      x /= 10;
    }
    do {
      putchar(*--sp);
    } while (sp != buf);
    return *this;
  }
  operator bool() { return !bad; }
  //   #undef getchar
  //   #undef putchar
  //   #undef fputs
} fio;
#define cin fio
#define cout fio
