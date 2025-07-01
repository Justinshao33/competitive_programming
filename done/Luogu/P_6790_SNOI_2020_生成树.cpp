#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
// #pragma GCC optimize("O3,unroll-loops")
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
    int n, m; cin >> n >> m;
    vector<map<int, pll>> G(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        G[a][b] = G[b][a] = { G[a][b].fi + 1, 1 };
    }
    queue<int> q;
    rep (i, 0, n) if (ssize(G[i]) <= 2) q.push(i);
    ll ans = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int deg = ssize(G[u]);
        if (deg == 0) continue;
        for (auto &p : G[u]) G[p.fi].erase(u);
        if (deg == 1) {
            (ans *= G[u].begin()->se.fi) %= MOD;
        } else {
            int v = G[u].begin()->fi, w = next(G[u].begin())->fi;
            auto [f1, g1] = G[u].begin()->se;
            auto [f2, g2] = next(G[u].begin())->se;
            ll f = f1 * f2 % MOD, g = (f1 * g2 + f2 * g1) % MOD;
            if (G[v].contains(w)) {
                auto [f3, g3] = G[v][w];
                G[v][w] = G[w][v] = { (f * g3 + f3 * g) % MOD, g * g3 % MOD };
            } else {
                G[v][w] = G[w][v] = { f, g };
            }
        }
        for (auto &p : G[u]) if (ssize(G[p.fi]) <= 2) q.push(p.fi);
        G[u].clear();
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