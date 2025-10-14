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
    int n, k; cin >> n >> k;
    vector<int> g(3);
    rep (i, 0, 3) cin >> g[i];
    string s; cin >> s;
    s = "$" + s;
    int blk = count(all(s), '#');
    vector dp(n + 1, vector<int>(51, -IINF));
    dp[0][0] = 0;
    rep (i, 1, n + 1) rep (j, 0, 51) {
        chmax(dp[i][j], dp[i - 1][j]);
        if (s[i] == '.' && s[i - 1] == '.' && dp[i - 2][j] != -IINF) {
            chmax(dp[i][j], dp[i - 2][j] + 1);
        }
        if (i >= 2 && j && s[i - 2] == '.' && s[i - 1] == '#' && s[i] == '.') {
            chmax(dp[i][j], dp[i - 3][j - 1]);
        }
    }
    int ans = 0;
    rep (j, 0, 51) {
        if (dp[n][j] == -IINF) continue;
        int sing = n - j * 3 - (blk - j) - dp[n][j] * 2;
        ans = max(ans, j * g[2] + dp[n][j] * g[1] + min(sing, k) * g[0]);
        if (g[0] * 2 > g[1] && dp[n][j] && sing < k) {
            while (dp[n][j] && sing + 2 <= k) {
                dp[n][j]--;
                sing += 2;
            }
            ans = max(ans, j * g[2] + dp[n][j] * g[1] + min(sing, k) * g[0]);
            if (dp[n][j]) {
                dp[n][j]--;
                sing += 2;
            }
            ans = max(ans, j * g[2] + dp[n][j] * g[1] + min(sing, k) * g[0]);
        }
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