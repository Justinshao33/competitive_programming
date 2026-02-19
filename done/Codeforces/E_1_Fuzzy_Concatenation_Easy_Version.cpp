#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

void solve() {
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;
    // O(nm) gogogo
    vector<int> nxt(m);
    rep (b, 1 - m, n) {
        int l = max(0, -b), r = min(m - 1, n - 1 - b);
        if (l > r) continue;
        for (int i = r, j = r + 1, k = r + 1; i >= l; --i) {
            if (s[i + b] != t[i]) {
                k = j, j = i;
            }
            chmax(nxt[i], k);
        }
    }
    int ans = 0, cur = 0;
    while (cur < m) {
        ans++;
        cur = nxt[cur];
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}