#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> lf;
    auto dfs = [&](auto self, int u, int pa) -> void {
        if (u != 0 && ssize(adj[u]) == 1) lf.push_back(u);
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, -1);
    vector<int> lp(n, n + 1);
    rep (i, 0, ssize(lf)) {
        int p; cin >> p;
        p--;
        lp[p] = i;
    }
    vector<int> mn(n, n), mx(n, 0);
    auto dfs3 = [&](auto self, int u, int pa) -> void {
        if (lp[u] < n) mn[u] = mx[u] = lp[u];
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            chmin(mn[u], mn[v]);
            chmax(mx[u], mx[v]);
        }
    };
    dfs3(dfs3, 0, -1);
    vector<int> ord;
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        ord.push_back(u);
        sort(all(adj[u]), [&](int x, int y) {
            if (x == pa) return false;
            if (y == pa) return true;
            return mn[x] < mn[y];
        });
        int p = mn[u] - 1;
        for (int v : adj[u]) {
            if (v == pa) continue;
            if (mn[v] != p + 1) {
                cout << -1 << '\n';
                exit(0);
            }
            p = mx[v];
            self(self, v, u);
            ord.push_back(u);
        }
    };
    dfs2(dfs2, 0, -1);
    for (int x : ord) cout << x + 1 << ' ';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}