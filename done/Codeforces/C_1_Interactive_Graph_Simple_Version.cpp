#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pld = pair<ld, ld>;
#define fi first
#define se second

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    if (n == 1) {
        cout << "! 0\n";
        return;
    }
    auto ask = [&](int x) -> vector<int> {
        cout << "? " << x << '\n';
        int q; cin >> q;
        vector<int> path;
        rep (i, 0, q) {
            int y; cin >> y;
            path.push_back(y);
        }
        return path;
    };
    vector<bool> vis(n + 1);
    vector<int> cpath{1}, cnt(n + 1);
    int lex = 1;
    vector<pii> edge;
    auto dfs = [&](auto self, int u, int d) -> void {
        cnt[u] = vis[u] = 1;
        lex++;
        cpath = ask(lex);
        while (true) {
            if (ssize(cpath) <= d) break;
            int v = cpath.back();
            edge.push_back({u, v});
            if (!vis[v]) {
                self(self, v, d + 1);              
            } else {
                lex += cnt[v];
                cpath = ask(lex);
            }
            cnt[u] += cnt[v];
        }
    };
    rep (i, 1, n + 1) if (!vis[i]) {
        int nxt = 1;
        rep (j, 1, i) nxt += cnt[j];
        if (nxt != lex) {
            lex = nxt;
            cpath = ask(lex);
        }
        if (!cpath.empty()) {
            assert(ssize(cpath) == 1);
            dfs(dfs, i, 1);
        }
    }
    cout << "! " << ssize(edge) << '\n';
    for (auto [u, v] : edge) {
        cout << u << ' ' << v << '\n';
    }
}
 
signed main() {
    // ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}