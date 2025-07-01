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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

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

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector f(n, vector<int>(m));
    rep (i, 0, n) rep (j, 0, m) cin >> f[i][j];
    vector<array<int, 3>> edge;
    rep (i, 0, n) rep (j, 0, m) {
        rep (k, 0, 4) {
            int nx = i + dx[k], ny = j + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            edge.pb({min(f[i][j], f[nx][ny]), i * m + j, nx * m + ny});
        }
    }
    sort(all(edge), greater<array<int, 3>>());
    UnionFind dsu(n * m);
    vector<vector<pii>> adj(n * m);
    for (auto [w, a, b] : edge) {
        if (dsu.Union(a, b)) {
            adj[a].pb({b, w});
            adj[b].pb({a, w});
        }
    }
    n *= m;
    vector<int> dep(n);
    vector pa(n, vector<int>(20)), we(n, vector<int>(20, IINF));
    auto dfs = [&](auto self, int u, int p) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            pa[v][0] = u;
            we[v][0] = w;
            self(self, v, u);
        }
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) {
        pa[i][j] = pa[pa[i][j - 1]][j - 1];
        we[i][j] = min(we[i][j - 1], we[pa[i][j - 1]][j - 1]);
    }
    auto lca = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        int res = IINF;
        rep (i, 0, 20) if (d & (1 << i)) {
            chmin(res, we[a][i]);
            a = pa[a][i];
        }
        if(a == b) return res;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                chmin(res, min(we[a][i], we[b][i]));
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return min({res, we[a][0], we[b][0]});
    };
    int q; cin >> q;
    while (q--) {
        int a, b, y, c, d, z; cin >> a >> b >> y >> c >> d >> z;
        a--, b--, c--, d--;
        int res = lca(a * m + b, c * m + d);
        if (res < min(y, z)) {
            cout << y - res + z - res << '\n';
        } else {
            cout << max(y, z) - min(y, z) << '\n';
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