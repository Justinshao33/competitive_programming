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

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<array<int, 3>>> edge(1e6 + 1);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        int c; cin >> c;
        edge[c].pb({a, b, i});
    }
    vector<int> ans(m);
    vector<vector<pii>> adj(n);
    UnionFind dsu(n);
    vector<int> dfn(n, -1), low(n, -1);
    vector<bool> vis(m, 0);
    rep (w, 1, 1e6 + 1) {
        vector<int> cand;
        for (auto [a, b, id] : edge[w]) {
            int u = dsu.find(a), v = dsu.find(b);
            if (dsu.same(a, b)) ans[id] = 0;
            else {
                ans[id] = 1;
                adj[u].pb({v, id});
                adj[v].pb({u, id});
                cand.pb(u);
                cand.pb(v);
            }
        }
        for (auto [a, b, id] : edge[w]) dsu.Union(a, b);
        int id = 0;
        auto dfs = [&](auto self, int u, int pa) -> void {
            dfn[u] = low[u] = id++;
            for (auto [v, id] : adj[u]) {
                if (vis[id]) continue;
                vis[id] = 1;
                if (dfn[v] == -1) {
                    self(self, v, u);
                    chmin(low[u], low[v]);
                    if (low[v] > dfn[u]) {
                        ans[id] = 2;
                    }
                } else {
                    chmin(low[u], dfn[v]);
                }
            }
        };
        for (int v : cand) if (dfn[v] == -1) {
            dfs(dfs, v, -1);
        }
        for (int v : cand) {
            adj[v].clear();
            dfn[v] = low[v] = -1;    
        }
    }
    rep (i, 0, m) {
        if (ans[i] == 0) cout << "none\n";
        else if (ans[i] == 1) cout << "at least one\n";
        else cout << "any\n";
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