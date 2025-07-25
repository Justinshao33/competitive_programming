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

void solve() {
    int n, m; cin >> n >> m;
    vector<int> x(n), y(n), p(n);
    rep (i, 0, n) cin >> x[i] >> y[i];
    iota(all(p), 0);
    sort(all(p), [&](int a, int b) {
        if (x[a] != x[b]) return x[a] < x[b];
        return y[a] < y[b];
    });
    vector<vector<int>> pre(n), adj(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        if (x[a] < x[b] || (x[a] == x[b] && y[a] < y[b])) pre[b].pb(a);
        else pre[a].pb(b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    rep (i, 0, n) {
        sort(all(pre[i]), [&](int a, int b) {
            return ((x[b] - x[i]) * (y[a] - y[i]) - (x[a] - x[i]) * (y[b] - y[i])) < 0;
        });
        debug(pre[i]);
    }
    vector<int> col(n, -1);
    set<int> difc;
    for (int cur : p) {
        difc.clear();
        col[cur] = 0;
        for (int v : pre[cur]) difc.insert(col[v]);
        if (ssize(difc) < 4) {
            while (difc.count(col[cur])) col[cur]++;
            continue;
        }
        col[cur] = -1;
        vector<bool> vis(n, 0);
        auto dfs = [&](auto self, int u, int ac, int cc) -> void {
            vis[u] = 1;
            assert(col[u] == ac || col[u] == cc);
            for (int v : adj[u]) {
                if (vis[v] || col[v] == -1) continue;
                if (col[v] != cc && col[v] != ac) continue;
                if (col[u] == ac && col[v] != cc) continue;
                if (col[u] == cc && col[v] != ac) continue;
                self(self, v, ac, cc);
            }
        };
        dfs(dfs, pre[cur][0], col[pre[cur][0]], col[pre[cur][2]]);
        auto chan = [&](auto self, int u, int ac, int cc) -> void {
            vis[u] = 1;
            assert(col[u] == ac || col[u] == cc);
            if (col[u] == ac) col[u] = cc;
            else col[u] = ac;
            for (int v : adj[u]) {
                if (vis[v] || col[v] == -1 || (col[v] != ac && col[v] != cc)) continue;
                self(self, v, ac, cc);
            }
        };
        if (!vis[pre[cur][2]]) {
            fill(all(vis), 0);
            int ori = col[pre[cur][0]];
            chan(chan, pre[cur][0], col[pre[cur][0]], col[pre[cur][2]]); 
            col[cur] = ori;
        } else {
            fill(all(vis), 0);
            int ori = col[pre[cur][1]];
            chan(chan, pre[cur][1], col[pre[cur][1]], col[pre[cur][3]]);
            col[cur] = ori;
        }
    }
    rep (i, 0, n) cout << col[i] + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}