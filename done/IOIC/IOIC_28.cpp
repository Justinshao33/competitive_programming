#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ld long double
#define F first
#define S second

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1

pii operator + (const pii &p1, const pii &p2) { return {p1.F + p2.F, p1.S + p2.S}; }
pii operator - (const pii &p1, const pii &p2) { return {p1.F - p2.F, p1.S - p2.S}; }
pll operator + (const pll &p1, const pll &p2) { return {p1.F + p2.F, p1.S + p2.S}; }
pll operator - (const pll &p1, const pll &p2) { return {p1.F - p2.F, p1.S - p2.S}; }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    ll l = -2e9, r = 2e14;
    vector<vector<pll>> dp(n, vector<pll>(2));
    auto dfs = [&](auto self, int u, int pa, ll p) -> void {
        pll sum = {0, 0}, mx = {-LINF, 0}, smx = {-LINF, 0};
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u, p);
            sum = sum + dp[v][0];
            if (dp[v][1] - dp[v][0] > mx) {
                smx = mx;
                mx = dp[v][1] - dp[v][0];
            } else if (dp[v][1] - dp[v][0] > smx) {
                smx = dp[v][1] - dp[v][0];
            }
        }
        dp[u][1] = max(sum + (pll){a[u], 0}, sum + mx);
        dp[u][0] = max({sum, sum + mx + (pll){a[u] - p, 1}, sum + mx + smx + (pll){-p, 1}});
    };
    dfs(dfs, 0, -1, l);
    if (dp[0][0].S < k) {
        cout << "The God Had Left...\n";
        return;
    }
    while (r - l > 1) {
        ll mid = l + r >> 1;
        dfs(dfs, 0, -1, mid);
        if (dp[0][0].S >= k) l = mid;
        else r = mid;
    }
    dfs(dfs, 0, -1, l);
    cout << dp[0][0].F + l * k << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}