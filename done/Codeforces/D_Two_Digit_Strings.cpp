#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int dp[5005][5005];

void solve() {
    string s, t; cin >> s >> t;
    int n = ssize(s), m = ssize(t);
    rep (i, 0, n + 1) rep (j, 0, m + 1) dp[i][j] = -IINF;
    dp[0][0] = 0;
    for (char &c : s) c -= '0'; 
    for (char &c : t) c -= '0'; 
    vector preS(n + 1, vector<int>(10, -1)), preT(m + 1, vector<int>(10, -1));
    preS[0][0] = 0;
    vector<int> pS(n + 1), pT(m + 1);
    for (int i = 0, sum = 0; i < n; i++) {
        sum += s[i];
        pS[i + 1] = sum % 10; 
        // preS[i + 1][sum % 10] = i + 1;
        // rep (j, 0, 10) chmax(preS[i + 1][j], preS[i][j]);
    }
    preT[0][0] = 0;
    for (int i = 0, sum = 0; i < m; i++) {
        sum += t[i];
        pT[i + 1] = sum % 10;
        // preT[i + 1][sum % 10] = i + 1;
        // rep (j, 0, 10) chmax(preT[i + 1][j], preT[i][j]);
    }
    vector pre(m + 1, vector<int>(10, -IINF));
    rep (i, 0, m + 1) pre[i][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (pS[i] != pT[j]) continue;
            rep (k, 0, 10) if (pre[j - 1][k] != -IINF) {
                chmax(dp[i][j], pre[j - 1][k] + 1);
            }
            chmax(pre[j][pT[j]], dp[i][j]);
            // rep (k, 0, 10) {
            //     int a = preS[i - 1][k], b = preT[j - 1][k];
            //     if (a != -1) chmax(dp[i][j], dp[a][j]);
            //     if (b != -1) chmax(dp[i][j], dp[i][b]);
            //     if (a != -1 && b != -1) chmax(dp[i][j], dp[a][b] + 1);
            // }
            // debug(i, j, dp[i][j]);
        }
        rep (j, 0, m) rep (k, 0, 10) chmax(pre[j + 1][k], pre[j][k]);
    }
    chmax(dp[n][m], -1LL);
    cout << dp[n][m] << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}