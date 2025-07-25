#ifdef LOCAL
// #define _GLIBCXX_DEBUG 1
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
    auto inp = [&]() -> auto {
        int n; cin >> n;
        vector<vector<int>> adj(n);
        rep (i, 0, n - 1) {
            int a, b; cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vector<ll> dep(n), dp(n);
        auto dfs = [&](auto self, int u, int pa) -> void {
            for (int v : adj[u]) {
                if (v == pa) continue;
                dep[v] = dep[u] + 1;
                self(self, v, u);
            }
        };
        dep[0] = 0;
        dfs(dfs, 0, -1);
        int mx = max_element(all(dep)) - dep.begin();
        dep[mx] = 0;
        dfs(dfs, mx, -1);
        int mx2 = max_element(all(dep)) - dep.begin();
        int diam = dep[mx2];
        auto dfs2 = [&](auto self, int u, int pa) -> void {
            chmax(dp[u], dep[u]);
            for (int v : adj[u]) {
                if (v == pa) continue;
                dep[v] = dep[u] + 1;
                self(self, v, u);
            }
        };
        dep[mx] = 0;
        dfs2(dfs2, mx, -1);
        dep[mx2] = 0;
        dfs2(dfs2, mx2, -1);
        sort(all(dp));
        return make_pair(diam, dp);
    };
    auto [d, v] = inp();
    auto [d2, v2] = inp();
    auto pre = v2;
    int n = ssize(v);
    partial_sum(all(pre), pre.begin());
    d = max(d, d2);
    ll ans = 0;
    rep (i, 0, ssize(v)) {
        int p = lower_bound(all(v2), d - v[i] - 1) - v2.begin();
        ans += 1LL * p * d + pre[n - 1] - (p == 0 ? 0 : pre[p - 1]) + (n - p) + 1LL * (n - p) * v[i];
    }
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