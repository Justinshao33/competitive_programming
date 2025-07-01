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
    int n; cin >> n;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    set<int> exi;
    rep (i, 0, n) exi.insert(i);
    vector<int> dep(n), fa(n);
    vector<pii> info(n);
    array<int, 3> diam;
    auto dfs = [&](auto self, int u, int pa) -> void {
        info[u] = {1, u};
        pii mx = {0, u}, smx = {0, -1};
        for (int v : adj[u]) {
            if (v == pa || !exi.contains(v)) continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            self(self, v, u);
            if (mx <= info[v]) {
                smx = mx, mx = info[v];
            } else if (smx <= info[v]) {
                chmax(smx, info[v]);
            }
        }
        info[u] = {mx.fi + 1, mx.se};
        if (mx.fi != 0) chmax(diam, {mx.fi + 1, max(mx.se, u), min(mx.se, u)});
        if (smx.fi != 0) chmax(diam, {mx.fi + smx.fi + 1, max(mx.se, smx.se), min(mx.se, smx.se)});
    };
    vector<array<int, 3>> ord;
    while (!exi.empty()) {
        int rt = *exi.begin();
        dep[rt] = 0;
        diam = {1, rt, rt};
        dfs(dfs, rt, -1);
        int a = diam[1], b = diam[2];
        // debug(a, b);
        while (a != b) {
            if (dep[a] < dep[b]) swap(a, b);
            exi.erase(a);
            a = fa[a];
        }
        exi.erase(a);
        ord.pb(diam);
    }
    sort(all(ord), greater<>());
    for (auto [d, x, y] : ord) cout << d << ' ' << x + 1 << ' ' << y + 1 << ' ';
    cout << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}