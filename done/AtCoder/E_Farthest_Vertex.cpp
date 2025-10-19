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
    int n; cin >> n;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dp(n), who(n), dep(n);
    auto dfs = [&](auto self, int u, int pa) -> void {
        who[u] = u;
        for (int v : adj[u]) {
            if (v == pa) continue;
            dep[v] = dep[u] + 1;
            self(self, v, u);
            if (chmax(dp[u], dp[v] + 1)) {
                who[u] = who[v];
            } else if (dp[u] == dp[v] + 1) {
                chmax(who[u], who[v]);
            }
        }
    };
    dfs(dfs, 0, -1);
    vector<int> ans(n);
    auto dfs2 = [&](auto self, int u, int pa, int mx, int mxw) -> void {
        vector<int> pre(ssize(adj[u])), suf(ssize(adj[u]));
        vector<int> wp(ssize(adj[u])), ws(ssize(adj[u]));
        if (mx + 1 > dp[u]) {
            ans[u] = mxw;
        } else if (dp[u] > mx + 1) {
            ans[u] = who[u];
        } else {
            ans[u] = max(who[u], mxw);
        }
        rep (i, 0, ssize(adj[u])) {
            if (i != 0) {
                pre[i] = pre[i - 1];
                wp[i] = wp[i - 1];
            }
            if (adj[u][i] == pa) {
                if (mx + 1 > pre[i]) {
                    pre[i] = mx + 1;
                    wp[i] = mxw;
                } else if (mx + 1 == pre[i]) {
                    chmax(wp[i], mxw);
                }
                continue;
            }
            if (dp[adj[u][i]] + 1 > pre[i]) {
                pre[i] = dp[adj[u][i]] + 1;
                wp[i] = who[adj[u][i]];
            } else if (dp[adj[u][i]] + 1 == pre[i]) {
                chmax(wp[i], who[adj[u][i]]);
            }
        }
        for (int i = ssize(adj[u]) - 1; i >= 0; --i) {
            if (i != ssize(adj[u]) - 1) {
                suf[i] = suf[i + 1];
                ws[i] = ws[i + 1];
            }
            if (adj[u][i] == pa) {
                if (mx + 1 > suf[i]) {
                    suf[i] = mx + 1;
                    ws[i] = mxw;
                } else if (mx + 1 == suf[i]) {
                    chmax(ws[i], mxw);
                }
                continue;
            }
            if (dp[adj[u][i]] + 1 > suf[i]) {
                suf[i] = dp[adj[u][i]] + 1;
                ws[i] = who[adj[u][i]];
            } else if (dp[adj[u][i]] + 1 == suf[i]) {
                chmax(ws[i], who[adj[u][i]]);
            }
        }
        if (ssize(adj[u]) == 1) {
            if (adj[u][0] != pa) {
                self(self, adj[u][0], u, 0, u);
            }
            return;
        }
        rep (i, 0, ssize(adj[u])) {
            int v = adj[u][i];
            if (v == pa) continue;
            int mxv = 0, oth = 0;
            if (i == 0) {
                mxv = suf[i + 1];
                oth = ws[i + 1];
            } else if (i == ssize(adj[u]) - 1) {
                mxv = pre[i - 1];
                oth = wp[i - 1];
            } else {
                if (pre[i - 1] > suf[i + 1]) {
                    mxv = pre[i - 1];
                    oth = wp[i - 1];
                } else if (suf[i + 1] > pre[i - 1]) {
                    mxv = suf[i + 1];
                    oth = ws[i + 1];
                } else {
                    mxv = pre[i - 1];
                    oth = max(wp[i - 1], ws[i + 1]);
                }
            }
            self(self, v, u, mxv, oth);
        }
    };
    ans[0] = who[0];
    dfs2(dfs2, 0, -1, -1, 0);
    rep (i, 0, n) cout << ans[i] + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}