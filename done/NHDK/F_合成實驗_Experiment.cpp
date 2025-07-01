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
    // d <= m / v
    // vd <= m
    // m - vd >= 0
    int n; cin >> n;
    vector<ld> m(n + 1), v(n + 1);
    rep (i, 1, n + 1) cin >> m[i];
    rep (i, 1, n + 1) cin >> v[i];
    ld l = 0.0, r = 5000000000.0;
    vector<ld> dp(n + 1);
    while (r - l > eps) {
        ld mid = (l + r) / 2;
        dp[0] = 0;
        dp[1] = dp[0] + m[1] - mid * v[1];
        rep (i, 2, n + 1) {
            dp[i] = max(dp[i - 1] + m[i] - mid * v[i], dp[i - 2] + m[i] - mid * v[i]);
        }
        if (dp[n] >= 0 || dp[n - 1] >= 0) l = mid;
        else r = mid;
    }
    cout << fixed << setprecision(10);
    cout << l << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}