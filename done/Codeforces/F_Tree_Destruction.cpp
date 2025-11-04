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
    int n; cin >> n;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dep(n);
    vector<int> dp(n, 0), who(n, 0);
    vector<bool> diam(n, 0);
    int dl, dr;
    {
        auto dfs = [&](auto self, int u, int pa, int rt) -> void {
            for (int v : adj[u]) {
                if (v == pa) continue;
                dep[v] = dep[u] + 1;
                if (chmax(dp[v], dep[u] + 1)) who[v] = rt;
                self(self, v, u, rt);
            }
        };
        dep[0] = -1;
        dfs(dfs, 0, -1, 0);
        dl = max_element(all(dep)) - dep.begin();
        dep[dl] = 0;
        dfs(dfs, dl, -1, dl);
        dr = max_element(all(dep)) - dep.begin();
        dep[dr] = 0;
        dfs(dfs, dr, -1, dr);
        for (int cur = dl;;) {
            diam[cur] = 1;
            if (cur == dr) break;
            for (int v : adj[cur]) {
                if (dep[v] == dep[cur] - 1) {
                    cur = v;
                    break;
                }
            }
        }
    }
    ll ans = 0;
    queue<int> q;
    vector<int> deg(n, 0);
    rep (i, 0, n) deg[i] = ssize(adj[i]);
    rep (i, 0, n) if (!diam[i] && deg[i] == 1) q.push(i);
    vector<array<int, 3>> ope;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ope.push_back({u, who[u], u});
        ans += dp[u];
        for (int v : adj[u]) {
            if (diam[v]) continue;
            deg[v]--;
            if (deg[v] == 1) q.push(v);
        }
    }
    for (int cur = dl;;) {
        if (cur == dr) break;
        ope.push_back({cur, dr, cur});
        ans += dp[dl];
        dp[dl]--;
        for (int v : adj[cur]) {
            if (dep[v] == dep[cur] - 1) {
                cur = v;
                break;
            }
        }
    }
    cout << ans << '\n';
    for (const auto &[a, b, c] : ope) cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}