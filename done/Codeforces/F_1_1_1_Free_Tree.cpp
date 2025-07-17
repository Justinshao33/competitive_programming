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

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<pii>> adj(n);
    vector<int> col(n);
    rep (i, 0, n) cin >> col[i];
    vector<ll> tot(n, 0);
    ll ans = 0;
    rep (i, 0, n - 1) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }
    vector<int> pa(n, -1), w(n);
    auto dfs = [&](auto self, int u) -> void {
        for (auto [v, c] : adj[u]) {
            if (v == pa[u]) continue;
            pa[v] = u;
            w[v] = c;
            self(self, v);
        }
    };
    dfs(dfs, 0);
    vector<map<int, ll>> child(n);
    rep (i, 1, n) {
        if (col[i] != col[pa[i]]) ans += w[i];
        tot[pa[i]] += w[i];
        child[pa[i]][col[i]] += w[i];
    }
    while (q--) {
        int u, x; cin >> u >> x;
        u--;
        ans -= tot[u];
        ans += child[u][col[u]];
        if (u) {
            if (col[u] != col[pa[u]]) ans -= w[u];
            child[pa[u]][col[u]] -= w[u];
        }
        col[u] = x;
        ans += tot[u];
        ans -= child[u][col[u]];
        if (u) {
            if (col[u] != col[pa[u]]) ans += w[u];
            child[pa[u]][col[u]] += w[u];
        }
        cout << ans << '\n';
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