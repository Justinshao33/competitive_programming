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
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> c(k);
    vector<int> sz(n), lf, col(n); 
    int cen = 0;   
    auto dfs = [&](auto self, int u, int pa) -> void {
        if (ssize(adj[u]) == 1) lf.push_back(u);
        sz[u] = 1;
        bool f = 1;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            if (sz[v] > n / 2) f = 0;
        }
        if (n - sz[u] > n / 2) f = 0;
        if (f) cen = u;
    };
    dfs(dfs, 0, -1);
    lf.clear();
    dfs(dfs, cen, -1);
    vector<int> p(k);
    rep (i, 0, k) cin >> c[i];
    iota(all(p), 0);
    sort(all(p), [&](int x, int y) {
        return c[x] > c[y];
    });
    int sum = 0;
    rep (i, 0, k) {
        if (c[i] >= 2) sum += c[i];
    }
    if (sum < ssize(lf)) {
        cout << -1 << '\n';
        return;
    }
    vector<int> use;
    vector<bool> isl(n);
    for (int x : lf) isl[x] = 1;
    int odd = ssize(lf) % 2;
    rep (i, 0, k) {
        if (c[p[i]] == 1) continue;
        int cnt = 0;
        while (c[p[i]] > 0 && ssize(use) < ssize(lf)) {
            use.push_back(p[i]);
            c[p[i]]--;
            cnt++;
        }
        if (cnt == 1) {
            assert(c[p[i]] > 0);
            col[cen] = p[i] + 1;
            c[p[i]]--;
            // assert(bg);
            // vector<int> use2;
            // rep (j, 0, k) {
            //     if (cccc[p[j]] > 2) {
            //         bool f = 0;
            //         for (int x : use) {
            //             if (x == p[j] && !f) {
            //                 f = 1;
            //                 continue;
            //             }
            //             use2.push_back(x);
            //         }
            //         use2.push_back(p[i]);
            //         c[p[i]]--;
            //         use = use2;
            //         break;
            //     }
            // }
        }
        if (ssize(use) == ssize(lf)) break;
    }
    vector<int> ord;
    assert(ssize(use) == ssize(lf));
    rep (i, 0, ssize(lf) / 2) {
        ord.push_back(i);
        ord.push_back(i + (ssize(lf) + 1) / 2);
    }
    // debug(lf);
    if (odd) ord.push_back(ssize(lf) / 2);
    // cerr << ssize(ord) << ' ' << odd << '\n';
    assert(ssize(ord) == ssize(lf));
    rep (i, 0, ssize(lf)) {
        // cerr << ord[i] << '\n';
        col[lf[ord[i]]] = use[i] + 1;
    }
    vector<int> rest;
    rep (i, 0, k) if (c[i] > 0) rest.push_back(i);
    rep (i, 0, n) {
        if (!col[i]) {
            col[i] = rest.back() + 1;
            c[rest.back()]--;
            if (c[rest.back()] == 0) rest.pop_back();
        }
    }
    rep (i, 0, n) cout << col[i] << " \n" [i == n - 1];
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}