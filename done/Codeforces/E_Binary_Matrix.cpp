#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

struct UnionFind {
    vector<int> pa;
    UnionFind(int n) : pa(n) {
        iota(all(pa), 0);
    }

    int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (a < b) swap(a, b);
        pa[b] = a;
        return true;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    string s;
    UnionFind dsu(m << 1);
    int ans = 0;
    vector<bool> a(m, false), b(m);
    rep (_, 0, n) {
        cin >> s;
        rep (i, 0, m >> 2) {
            int x = 0;
            if (isdigit(s[i])) x = s[i] - '0';
            else x = 10 + s[i] - 'A';
            rep (j, 0, 4) b[i * 4 + 3 - j] = x >> j & 1;
            ans += __builtin_popcount(x);
        }
        rep (i, 0, m) {
            if (i && b[i] && b[i - 1]) ans -= dsu.Union(m + i, m + i - 1);
            if (a[i] && b[i]) ans -= dsu.Union(i, m + i);
        }
        rep (i, 0, m) {
            dsu.pa[i] = dsu.pa[i + m] - m;
            dsu.pa[i + m] = i + m;
            a[i] = b[i];
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}