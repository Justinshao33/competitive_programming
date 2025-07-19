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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0, f = 1; char c = GU; while (c == ' ' || c == '\n') {c = GU;} if (c == '-') {f = -1, c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return f * re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in(), q = in();
    vector<int> coin(n);
    int rt = 0;
    rep (i, 0, n) {
        coin[i] = in();
        if (coin[i]) rt = i;
    }
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a = in(), b = in();
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // build spanning tree which all leaf has a coin, and the tree cover all coins
    // ans = 2 * #tree_edge - 2 * #tree_edge_on_path + 2 * minimum_distance_on_path_to_tree + distance_from_a_to_b
    // binary lifting
    vector dis(n, vector<int>(18, 0));
    auto pa = dis;
    int edge = 0;
    vector<int> dep(n), tedge(n);
    {
        vector<int> sz(n);
        auto upd = [&](auto self, int u, int p, int d) -> void {
            dis[u][0] = d;
            for (int v : adj[u]) {
                if (v == p) continue;
                self(self, v, u, d + 1);
            }
        };
        auto dfs = [&](auto self, int u, int p) -> void {
            sz[u] = coin[u];
            for (int v : adj[u]) {
                if (v == p) continue;
                pa[v][0] = u;
                dep[v] = dep[u] + 1;
                self(self, v, u);
                sz[u] += sz[v];
            }
            if (sz[u]) {
                for (int v : adj[u]) if (v != p && sz[v] == 0) {
                    upd(upd, v, u, 1);
                }
            }
            if (u != rt && sz[u]) edge++;
        };
        auto dfs2 = [&](auto self, int u, int p) -> void {
            for (int v : adj[u]) {
                if (v == p) continue;
                tedge[v] = tedge[u] + (sz[v] != 0);
                self(self, v, u);
            }
        };
        dfs(dfs, rt, -1);
        dfs2(dfs2, rt, -1);
        rep (j, 1, 18) rep (i, 0, n) {
            pa[i][j] = pa[pa[i][j - 1]][j - 1];
            dis[i][j] = min(dis[i][j - 1], dis[pa[i][j - 1]][j - 1]);
        }
    }
    auto lca = [&](int a, int b) -> int {
        int di = dep[a] + dep[b], sum = tedge[a] + tedge[b];
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        int mn = IINF; 
        rep (i, 0, 20) if (d & (1 << i)) {
            chmin(mn, dis[a][i]);
            a = pa[a][i];
        }
        if (a == b) {
            chmin(mn, dis[a][0]);
            di -= dep[a] * 2;
            sum -= tedge[a] * 2;
            return 2 * edge - sum * 2 + 2 * mn + di;
        }
        for (int i = 17; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                chmin(mn, dis[a][i]);
                chmin(mn, dis[b][i]);
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        chmin(mn, dis[a][0]);
        chmin(mn, dis[b][0]);
        chmin(mn, dis[pa[a][0]][0]);
        di -= dep[pa[a][0]] * 2;
        sum -= tedge[pa[a][0]] * 2;
        return 2 * edge - sum * 2 + 2 * mn + di;
    };
    while (q--) {
        int a = in(), b = in();
        a--, b--;
        cout << lca(a, b) << '\n';
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