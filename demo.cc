#include "List.hh"
#include "RadixSort.hh"
#include "FastIO.hh"
signed main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  List<int> r;
  for (int i = 0; i < n; ++i) {
    int t; cin >> t;
    r.pushBack(t);
  }
  radixSort(r.cbegin(), r.cend(), 32);
  for (auto element : r)
    cout << element << " ";
  cout << endl;
}