#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
    vector<vector<pii>> adj(n);
    vector<int> ww(n);
    rep (i, 1, n) {
        int p, w; cin >> p >> w;
        p--;
        adj[p].push_back({i, w});
        ww[i] = w;
    }
    vector<int> dep(n);
    vector pa(n, vector<int>(20));
    auto dfs = [&](auto self, int u, int p) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == p) continue;
            pa[v][0] = u;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) {
        pa[i][j] = pa[pa[i][j - 1]][j - 1];
    }
    auto lca = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        rep (i, 0, 20) if (d & (1 << i)) a = pa[a][i];
        if (a == b) return a;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return pa[a][0];
    };
    vector w(n, vector<int>(20));
    vector<int> dis(n);
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;
        int p = lca(a, b);
        dis[p] -= 2;
        dis[a]++;
        dis[b]++;
    }
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            dis[u] += dis[v];
        }
        w[u][0] = ww[u] + dis[u];
    };
    dfs2(dfs2, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) {
        w[i][j] = min(w[i][j - 1], w[pa[i][j - 1]][j - 1]);
    }
    auto lca2 = [&](int a, int b) -> int {
        int mn = LINF;
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        rep (i, 0, 20) if (d & (1 << i)) {
            mn = min(mn, w[a][i]);
            a = pa[a][i];
        }
        if (a == b) return mn;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                mn = min({mn, w[a][i], w[b][i]});
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return min({mn, w[a][0], w[b][0]});
    };
    cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;
        if (a == b) cout << 0 << '\n';
        else cout << lca2(a, b) << '\n';
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}