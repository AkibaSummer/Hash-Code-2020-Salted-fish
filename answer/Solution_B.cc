#include <bits/stdc++.h>
using namespace std;
struct _ls {
  int n, t, m, id;
  vector<int> books;
};
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int b, l, d;
  cin >> b >> l >> d;
  vector<int> score(b);
  for (auto &i : score) {
    cin >> i;
  }
  vector<_ls> ls(l);
  for (int num = 0; num < l; num++) {
    auto &i = ls[num];
    i.id = num;
    cin >> i.n >> i.t >> i.m;
    i.books.resize(i.n);
    for (auto &j : i.books) {
      cin >> j;
    }
  }
  sort(ls.begin(), ls.end(), [](_ls &a, _ls &b) { return a.t < b.t; });
  cout << l << endl;
  for (auto &i : ls) {
    cout << i.id << ' ' << i.n << endl;
    for (auto &j : i.books) {
      cout << j << ' ';
    }
    cout << endl;
  }
}