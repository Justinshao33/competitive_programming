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

void solve() {
    int n, L, R; cin >> n >> L >> R;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<bool> vis(n, 0);
    vector<int> sz(n, 0);
    auto dfs_sz = [&](auto self, int u, int pa) -> int {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v == pa || vis[v]) continue;
            sz[u] += self(self, v, u);
        }
        return sz[u];
    };
    auto dfs_cen = [&](auto self, int u, int pa, int tar) -> int {
        for (int v : adj[u]) {
            if (v == pa || vis[v] || sz[v] < tar) continue;
            return self(self, v, u, tar);
        }
        return u;
    };
    vector<int> cnt(n + 1, 0), tot(n + 1, 0);
    tot[0] = 1;
    int submx = 0, allmx = 0;
    auto calc = [&](auto self, int u, int pa, int dep) -> void {
        if (dep > R) return;
        chmax(submx, dep);
        cnt[dep]++;
        for (int v : adj[u]) {
            if (v == pa || vis[v]) continue;
            self(self, v, u, dep + 1);
        }
    };
    ll ans = 0;
    auto dc = [&](auto self, int u) -> void {
        int cen = dfs_cen(dfs_cen, u, -1, dfs_sz(dfs_sz, u, -1) >> 1);
        vis[cen] = 1;
        allmx = 0;
        ll pre = L == 1;
        for (int v : adj[cen]) {
            if (vis[v]) continue;
            submx = 0;
            calc(calc, v, cen, 1);
            ll psum = pre;
            for (int d = 1; d <= submx; d++) {
                ans += psum * cnt[d];
                // L <= x + d <= R
                // L - d <= x <= R - d
                if (R - d >= 0) psum -= tot[R - d];
                if (L - d - 1 >= 0) psum += tot[L - d - 1];
            }
            for (int d = L - 1; d <= R - 1 && d <= submx; d++) {
                pre += cnt[d];
            }
            rep (d, 0, submx + 1) {
                tot[d] += cnt[d];
                cnt[d] = 0;
            }
            chmax(allmx, submx);
        }
        fill(tot.begin() + 1, tot.begin() + allmx + 1, 0);
        for (int v : adj[cen]) {
            if (vis[v]) continue;
            self(self, v);
        }
    };
    dc(dc, 0);
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}