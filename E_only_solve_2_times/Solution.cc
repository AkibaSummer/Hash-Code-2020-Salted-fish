#include <bits/stdc++.h>
using namespace std;
struct _ls {
  int n, t, m, id, sc;
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
  map<int, set<int>, cmp> score_l;
  vector<int> my_location(l);

  for (int num = 0; num < l; num++) {
    auto &i = ls[num];
    i.sc = 0;
    i.id = num;
    cin >> i.n >> i.t >> i.m;
    for (int j = 0; j < i.n; j++) {
      int tmp;
      cin >> tmp;
      i.books.insert(tmp);
      i.sc += score[tmp];
      who_has_me[tmp].push_back(num);
    }
    score_l[i.m == 2 ? i.sc / i.t : -1].insert(num);
    my_location[num] = i.m == 2 ? i.sc / i.t : -1;
  }

  for (int num = 0; num < l; num++) {
    assert(score_l[my_location[num]].count(num));
  }

  // cout << l << endl;
  int ans = 0;
  vector<answer> anss;
  for (int i = (*score_l.begin()).first; i >= 1; i = (*score_l.begin()).first) {
    if (i == 0) break;
    while (score_l[i].size()) {
      int now = *score_l[i].begin();
      score_l[i].erase(now);
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
          // for (auto &tmp : score_l[loc]) {
          //   cerr << tmp << endl;
          // }

          assert(score_l[my_location[k]].count(k));
          // assert(loc == i);
          ls[k].sc -= score[j];
          ls[k].n--;
          assert(ls[k].n >= 0);
          my_location[k] = ls[k].m==2 ? ls[k].sc / ls[k].t : -1;
          assert(ls[k].books.count(j));
          ls[k].books.erase(j);

          // cerr << loc << endl;
          // for (auto &tmp : score_l[loc]) {
          //   cerr << tmp << endl;
          // }
          // cerr << k << endl;
          // cerr << endl;

          score_l[loc].erase(k);
          if (loc == 0) continue;
          score_l[ls[k].m==2 ? ls[k].sc / ls[k].t : -1].insert(k);

          // cerr << k << ' ' << my_location[k] << endl;
          // cerr << endl;
        }
      }
    }
    score_l.erase(i);
  }
  cout << anss.size() << endl;
  for (auto &i : anss) {
    cout << i.a << ' ' << i.b << endl;
    sort(i.outs.begin(), i.outs.end(),
         [&](int &a, int &b) { return score[a] > score[b]; });
    for (auto &j : i.outs) {
      cout << j << ' ';
    }
    cout << endl;
  }
}