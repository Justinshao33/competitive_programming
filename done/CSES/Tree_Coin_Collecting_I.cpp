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

void solve() {
    int n, q; cin >> n >> q;
    queue<int> qu;
    vector<int> dis(n, IINF);
    rep (i, 0, n) {
        int c; cin >> c;
        if (c) {
            qu.push(i);
            dis[i] = 0;
        }
    }
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (int v : adj[u]) {
            if (chmin(dis[v], dis[u] + 1)) {
                qu.push(v);
            }
        }
    }
    vector we(n, vector<int>(20));
    auto pa = we;
    vector<int> dep(n);
    auto dfs = [&](auto self, int u, int p) -> void {
        for (int v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            pa[v][0] = u;
            we[v][0] = dis[v];
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
        rep (i, 0, 20) if (d & (1 << i)) res = min(res, we[a][i]), a = pa[a][i];
        if(a == b) return min(res, dis[a]) * 2 - 2 * dep[a];
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                res = min({res, we[a][i], we[b][i]});
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return min({res, we[a][0], we[b][0], dis[pa[a][0]]}) * 2 - 2 * dep[pa[a][0]];
    };
    while (q--) {
        int a, b; cin >> a >> b;
        a--, b--;
        cout << dep[a] + dep[b] + lca(a, b) << '\n';
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
