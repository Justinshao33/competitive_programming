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

struct UnionFind {
    vector<int> pa;
    vector<ll> val;
    int id;
    UnionFind(int n) : pa(n, 0), id(n / 2), val(n, LINF) {
        iota(all(pa), 0);
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

    int Union(int a, int b, ll w) {
        a = find(a), b = find(b);
        if (a == b) {
            chmin(val[a], w);
            return -1;
        }
        pa[a] = pa[b] = id;
        val[id] = w;
        id++;
        return id - 1;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    ll ans = 0;
    vector<array<int, 3>> edge;
    vector<int> deg(n, 0);
    rep (i, 0, m) {
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        deg[a]++;
        deg[b]++;
        edge.push_back({a, b, w});
        ans += w;       
    }
    bool f = 1;
    vector<bool> odd(n, 0);
    rep (i, 0, n) if (deg[i] % 2) {
        odd[i] = 1;        
    }
    UnionFind dsu(n + n);
    vector<vector<int>> adj(n + n);
    for (const auto &[u, v, w] : edge) {
        int fu = dsu.find(u), fv = dsu.find(v);
        int rt = dsu.Union(u, v, w);
        if (rt != -1) {
            adj[rt].push_back(fu);
            adj[rt].push_back(fv);
        }
    }
    // rt = n + n - 1
    auto dfs = [&](auto self, int u) -> int {
        if (u < n) return odd[u]; 
        int cnt = 0;
        for (int v : adj[u]) {
            chmin(dsu.val[v], dsu.val[u]);
            cnt += self(self, v);
        }
        ans += dsu.val[u] * (cnt / 2);
        return cnt % 2;
    };
    dfs(dfs, n + n - 2);
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