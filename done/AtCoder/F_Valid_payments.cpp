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
    int n; ll X; cin >> n >> X;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<ll> lim(n);
    rep (i, 0, n - 1) lim[i] = a[i + 1] / a[i];
    lim[n - 1] = LINF;
    // y = x + ch, if ch fixed, y fixed
    // dp #ch <=> #y 
    // 0/1 -> carry? (ch[i] + x[i] == lim[i] will cause carry)
    // ch[i] == 0 || y[i] == 0
    // ch[i] != 0 -> y[i] == 0 -> carry
    // y[i] != 0 -> ch[i] = 0 -> y[i] = x[i] + carry
    // => y[i] has only two possible value
    // also means that y[i] doesn't matter, we just need to focus on if this digit can carry
    // ch[i] < lim[i] (or it will go to bigger value)
    // => x[i] == 0 -> no carry
    // if previous have carry, then next x[i] + 1 < lim[i] can cause no carry
    vector<ll> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = X / a[i];
        X %= a[i];
    }
    vector dp(n, vector<ll>(2, 0));
    dp[0][0] = 1;
    dp[0][1] = (x[0] != 0);
    rep (i, 1, n) {
        dp[i][0] += dp[i - 1][0];
        if (x[i]) dp[i][1] += dp[i - 1][0];
        dp[i][1] += dp[i - 1][1];
        if (x[i] + 1 < lim[i]) dp[i][0] += dp[i - 1][1];
    }
    cout << dp[n - 1][0] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}