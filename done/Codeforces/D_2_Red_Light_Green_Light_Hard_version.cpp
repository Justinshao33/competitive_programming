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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; ll k; cin >> n >> k;
    vector<ll> p(n), d(n);
    rep (i, 0, n) cin >> p[i];
    rep (i, 0, n) cin >> d[i];
    map<ll, vector<pll>> di, adi;
    // y = x, y = -x
    rep (i, 0, n) {
        di[(p[i] + d[i]) % k].pb(pll(p[i], i));
        adi[((p[i] - d[i]) % k + k) % k].pb(pll(p[i], i));
    }
    vector to(n, vector<pii>(2, pii(-1, -1)));
    // 0: right, 1: left
    for (auto &[_, v] : di) {
        sort(all(v));
        rep (i, 0, ssize(v) - 1) {
            to[v[i].se][0] = pii(v[i + 1].se, 1);
        }
    }
    for (auto &[_, v] : adi) {
        sort(all(v));
        rep (i, 1, ssize(v)) {
            to[v[i].se][1] = pii(v[i - 1].se, 0);
        }
    }
    vector dp(n, vector<int>(2, -1));
    auto dfs = [&](auto self, int u, int d) -> void {
        auto &[v, nd] = to[u][d];
        if (v == -1) {
            dp[u][d] = 1;
            return;
        }
        dp[u][d] = 0;
        if (dp[v][nd] == -1) self(self, v, nd);
        if (dp[v][nd] == 1) dp[u][d] = 1;
    };
    rep (i, 0, n) rep (j, 0, 2) if (dp[i][j] == -1) dfs(dfs, i, j);
    int q; cin >> q;
    while (q--) {
        ll x; cin >> x;
        auto it = lower_bound(all(adi[x % k]), pll(x, -1));
        // if (x == 2) {
        //     debug(adi[x % k], dp[2][1]);
        // }
        if (it == adi[x % k].end()) cout << "YES\n";
        else {
            if (dp[it->se][1]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}