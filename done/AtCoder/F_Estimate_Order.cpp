#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n);
    rep (i, 0, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[b].pb({a, c});
        adj[a].pb({b, -c});
    }
    vector<bool> vis(n, 0);
    vector<vector<int>> cc;
    vector<int> idx(n, 0), cc_info; 
    auto dfs = [&](auto self, int u) -> void {
        cc.back().pb(u);
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (vis[v]) continue;
            idx[v] = idx[u] + w;
            self(self, v);
        }
    };
    rep (i, 0, n) if (!vis[i]) {
        cc.pb({});
        dfs(dfs, i);
        int mi = 0, bit = 0;
        for (int x : cc.back()) chmin(mi, idx[x]);
        for (int x : cc.back()) {
            idx[x] -= mi;
            bit |= 1 << idx[x];
        }
        cc_info.pb(bit);
    }
    vector<int> ans(n, -1);
    m = cc_info.size();
    rep (cur, 0, m) {
        vector<bool> dp(1 << n, 0);
        dp[0] = 1;
        int cnt = 0;
        rep (i, 0, m) if (i != cur) {
            rep (bit, 0, 1 << n) if (dp[bit] && cnt == __builtin_popcount(bit)) {
                int x = cc_info[i];
                while (x < 1 << n) {
                    if ((bit & x) == 0) dp[bit | x] = true;
                    x <<= 1;
                }
            }
            cnt += cc[i].size();
        }
        cnt = 0;
        int x = cc_info[cur], offset = 0;
        while (x < 1 << n) {
            if (dp[((1 << n) - 1) ^ x]) {
                cnt++;
                offset = __builtin_ctz(x);
            }
            x <<= 1;
        }
        if (cnt == 1) {
            for (int x : cc[cur]) ans[x] = offset + idx[x] + 1;
        }
    }
    rep (i, 0, n) cout << ans[i] << " \n" [i == n - 1];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}