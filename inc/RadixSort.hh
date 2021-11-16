#pragma once
#include <queue>
#include <iostream>
template<typename Iterator>
inline void radixSort(Iterator first, Iterator last, unsigned radix = 32) {
  using namespace std;
  vector<deque<decltype((*first)++)>> buf(radix + 1);
  vector<decltype((*first)++)> powRadix;
  auto maxEle = *first;
  for (auto it = first; it != last; ++it)
    maxEle = max(maxEle, *it);
  __uint128_t t = 1;
  do {
    powRadix.push_back(t);
  } while ((t *= radix) / radix <= maxEle);
  for (auto i = 1; powRadix[i - 1] <= maxEle; ++i) {
    for (auto it = first; it != last; ++it)
      buf[((*it) % powRadix[i]) / powRadix[i - 1]].push_back(*it); //hash
    auto it = first;
    for (auto k = 0; k < radix && it != last; ++k) { //write back
      while (!buf[k].empty()) {
        (*it++) = buf[k].front();
        buf[k].pop_front();
      }
    }
  }
}
