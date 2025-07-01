#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

template <typename T>
struct FenwickTree{
    vector<T> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    void mod(int x, T val) {
        while(x < BIT.size()){
            BIT[x] += val;
            x += x & -x;
        }
    }

    T query(int x) {
        T res = 0;
        while (x > 0) {
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }

    T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<pii> edge;
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
        edge.pb({a, b});
    }
    vector<int> in(n), out(n), dep(n);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int pa) -> void {
        in[u] = ++cnt;
        for (int v : adj[u]) {
            if (v == pa) continue;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
        out[u] = cnt;
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);
    for (auto &[a, b] : edge) if (dep[a] > dep[b]) swap(a, b);
    FenwickTree<ll> bit(n);
    rep (i, 1, n + 1) bit.mod(in[i - 1], 1);
    int q; cin >> q;
    ll tot = n;
    // cout << in << out;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, w; cin >> x >> w;
            x--;
            bit.mod(in[x], w);
            tot += w;
        } else {
            int y; cin >> y;
            y--;
            auto [a, b] = edge[y];
            // cout << bit.query(in[b], out[b]) << '\n';
            ll sub = bit.query(in[b], out[b]);
            cout << abs(sub - (tot - sub)) << '\n';
        }
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}