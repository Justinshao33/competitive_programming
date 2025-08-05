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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, m, x; cin >> n >> m >> x;
    vector<vector<array<int, 3>>> adj(n);
    vector<int> g(3);
    map<char, int> col;
    col['r'] = 0, col['g'] = 1, col['b'] = 2;
    rep (i, 0, m) {
        int a, b, w; char c; cin >> a >> b >> w >> c;
        a--, b--;
        adj[a].pb({b, w, col[c]});
        adj[b].pb({a, w, col[c]});
        g[col[c]] = gcd(g[col[c]], w);
    }
    vector vis(n, vector<bool>(1 << 3, 0));
    auto dfs = [&](auto self, int u, int msk) -> void {
        vis[u][msk] = 1;
        for (auto [v, w, c] : adj[u]) {
            int nm = msk ^ ((w % (2 * g[c]) == g[c]) << c);
            if (vis[v][nm]) continue;
            self(self, v, nm);
        }
    };
    dfs(dfs, 0, 0);
    ll ans = LINF;
    rep (bit, 0, 1 << 3) if (vis[n - 1][bit]) {
        rep (i, 0, 3) {
            int gap = 0;
            rep (j, 0, 3) if (j != i) gap = gcd(gap, 2 * g[j]);
            vector cost(gap, vector<ll>(3, LINF));
            ll ini = (bit >> i & 1) ? g[i] : 0;
            rep (t, 0, 2 * x) {
                ll A = ini + 2LL * g[i] * t;
                rep (j, 0, 3) if (j != i) {
                    ll ini2 = (bit >> j & 1) ? g[j] : 0;
                    chmin(cost[t % gap][j], ini2 + 2 * g[j] * ((A - ini2 + 2 * g[j] - 1) / (2 * g[j])) - A);
                }
            }
            rep (j, 0, gap) {
                ll res = 0;
                rep (k, 0, 3) if (k != i) chmax(res, cost[j][k]);
                chmin(ans, res);
            }
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}