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
    vector<vector<int>> adj(n);
    vector<int> c(n);
    {
        int seed, m, f; cin >> seed >> m >> f;
        vector<int> q(m), d(m);
        rep (i, 1, m) cin >> q[i];
        rep (i, 0, m) cin >> d[i];
        ull state = seed;
        rep (i, 1, n) {
            if (i < m) {
                adj[q[i] - 1].push_back(i);
            } else {
                adj[state % i].push_back(i);
                state = (state * 1103515245 + 12345) % (1LL << 31);
            }
        }
        rep (i, 0, n) {
            if (i < m) c[i] = d[i] - 1;
            else {
                c[i] = state % f;
                state = (state * 1103515245 + 12345) % (1LL << 31);
            }
        }
    }
    vector<int> mx(n, 0), sz(n), hson(n, -1), dfn(n), ord;
    int iddd = 0;
    auto dfs = [&](auto self, int u) -> void {
        sz[u] = 1;
        dfn[u] = iddd++;
        ord.push_back(u);
        for (int v : adj[u]) {
            self(self, v);
            sz[u] += sz[v];
            if (hson[u] == -1 || sz[hson[u]] < sz[v]) hson[u] = v;
        }
    };
    dfs(dfs, 0);
    vector<int> cnt(n, 0), ccnt(n + 1, 0), cccnt(n, 0);
    ccnt[0] = n;
    int mxv = 0;
    auto add = [&](int x) -> void {
        ccnt[cnt[x]]--;
        cnt[x]++;
        ccnt[cnt[x]]++;
        chmax(mxv, cnt[x]);
    };
    auto sub = [&](int x) -> void {
        ccnt[cnt[x]]--;
        cnt[x]--;
        ccnt[cnt[x]]++;
        if (ccnt[mxv] == 0) mxv--;
    };
    // auto dfs3 = [&](auto self, int u, bool f) -> void {
    //     if (f) add(c[u]);
    //     else sub(c[u]);
    //     for (int v : adj[u]) self(self, v, f);
    // };
    auto dfs2 = [&](auto self, int u, bool rem) -> void {
        for (int v : adj[u]) if (v != hson[u]) self(self, v, 1);
        if (hson[u] != -1) self(self, hson[u], 0);
        for (int v : adj[u]) if (v != hson[u]) rep (i, dfn[v], dfn[v] + sz[v]) add(c[ord[i]]);
        add(c[u]);
        mx[u] = mxv;
        cccnt[u] = ccnt[mxv];
        if (rem) rep (i, dfn[u], dfn[u] + sz[u]) sub(c[ord[i]]);
    };
    dfs2(dfs2, 0, 0);
    int ans = 0;
    rep (i, 0, n) ans += (mx[i] ^ (i + 1)) * (cccnt[i] ^ (i + 1)) % MOD;
    cout << ans % MOD << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}