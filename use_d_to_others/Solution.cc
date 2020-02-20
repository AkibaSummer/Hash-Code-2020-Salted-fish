#include <bits/stdc++.h>
using namespace std;
struct _ls {
  int n, t, m, id;
  set<int> books;
};
struct answer {
  int a, b;
  vector<int> outs;
};

struct cmp {
  bool operator()(const int &a, const int &b) { return a > b; }
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

  vector<vector<int>> who_has_me(b);
  map<int, set<int>, cmp> books_num;
  vector<int> my_location(l);

  for (int num = 0; num < l; num++) {
    auto &i = ls[num];
    i.id = num;
    cin >> i.n >> i.t >> i.m;
    for (int j = 0; j < i.n; j++) {
      int tmp;
      cin >> tmp;
      i.books.insert(tmp);
      who_has_me[tmp].push_back(num);
    }
    books_num[i.n].insert(num);
    my_location[num] = i.n;
  }

  for (int num = 0; num < l; num++) {
    assert(books_num[my_location[num]].count(num));
  }

  // cout << l << endl;
  int ans = 0;
  vector<answer> anss;
  for (int i = (*books_num.begin()).first; i >= 1;
       i = (*books_num.begin()).first) {
    if (i == 0) break;
    while (books_num[i].size()) {
      int now = *books_num[i].begin();
      books_num[i].erase(now);
      answer tmp;
      tmp.a = ls[now].id;
      tmp.b = ls[now].n;
      // cout << ls[now].id << ' ' << ls[now].n << endl;
      for (auto &j : ls[now].books) {
        // cout << j << ' ';
        tmp.outs.push_back(j);
      }
      anss.push_back(tmp);
      // cout << endl;
      ans++;
      for (auto &j : ls[now].books) {  // book i have
        // cerr << "book:" << j << endl;
        for (auto &k : who_has_me[j]) {  // k:who has book j
          if (k == now) continue;
          int loc = my_location[k];
          if (loc == 0) continue;

          // cerr << k << ' ' << loc << endl;
          // for (auto &tmp : books_num[loc]) {
          //   cerr << tmp << endl;
          // }

          assert(books_num[my_location[k]].count(k));
          // assert(loc == i);
          my_location[k]--;
          ls[k].n--;
          assert(ls[k].books.count(j));
          ls[k].books.erase(j);

          // cerr << loc << endl;
          // for (auto &tmp : books_num[loc]) {
          //   cerr << tmp << endl;
          // }
          // cerr << k << endl;
          // cerr << endl;

          books_num[loc].erase(k);
          if (loc == 0) continue;
          books_num[loc - 1].insert(k);
          assert(loc > 0);

          // cerr << k << ' ' << my_location[k] << endl;
          // cerr << endl;
        }
      }
    }
    books_num.erase(i);
  }
  cout << anss.size() << endl;
  for (auto &i : anss) {
    cout << i.a << ' ' << i.b << endl;
    for (auto &j : i.outs) {
      cout << j << ' ';
    }
    cout << endl;
  }
}