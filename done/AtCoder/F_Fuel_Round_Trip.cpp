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
#define pld pair<ld, ld>
#define ld long double
#define FF first
#define S second

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
    int n, H; cin >> n >> H;
    vector<int> x(n + 1), F(n + 1), P(n + 1);
    x[0] = 0;
    rep (i, 1, n + 1) cin >> x[i];
    rep (i, 1, n) cin >> P[i] >> F[i];
    F[n] = 0, P[n] = 0;
    vector<vector<int>> dp(H + 1, vector<int>(H + 1, IINF));
    rep (i, 0, H + 1) dp[H][i] = 0;
    rep (i, 0, n) {
        int dis = x[i + 1] - x[i];
        vector<vector<int>> g(H + 1, vector<int>(H + 1, IINF));
        rep (j, 0, H + 1) rep (k, 0, H + 1) {
            if (dp[j][k] == IINF) continue;
            if (k + 1 <= H) chmin(dp[j][k + 1], dp[j][k]);
            if (j - dis < 0 || k + dis > H) continue;
            chmin(g[j - dis][k + dis], dp[j][k]);
            chmin(g[min(H, j - dis + F[i + 1])][k + dis], dp[j][k] + P[i + 1]);
            if (k + dis >= F[i + 1]) chmin(g[j - dis][k + dis - F[i + 1]], dp[j][k] + P[i + 1]);
        }
        swap(dp, g);
    }
    int ans = IINF;
    rep (i, 0, H + 1) chmin(ans, dp[i][i]);
    if (ans == IINF) ans = -1;
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