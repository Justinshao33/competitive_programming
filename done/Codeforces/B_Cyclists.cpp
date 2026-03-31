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

void solve() {
    int n, k, p, m; cin >> n >> k >> p >> m;
    p--;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<int> b;
    rep (i, 0, p) b.push_back(a[i]);
    sort(all(b));
    int sum = 0;
    rep (i, 0, p - k + 1) {
        sum += b[i];
    }
    if (m < sum + a[p]) {
        cout << 0 << '\n';
        return;
    }
    m -= sum + a[p];
    b.clear();
    rep (i, 0, n) if (i != p) {
        b.push_back(a[i]);
    }
    sort(all(b));
    sum = a[p];
    rep (i, 0, n - k) {
        sum += b[i];
    }
    cout << 1 + m / sum << '\n';
    // vector dp(m + 1, vector<int>(n, -IINF));
    // dp[m][p] = 0;
    // vector<int> pre(n, IINF);
    // rep (i, 0, n) {
    //     if (i) pre[i] = pre[i - 1];
    //     if (i < k) chmin(pre[i], a[i]);
    // }
    // for (int i = m; i > 0; --i) {
    //     rep (j, 0, n) if (dp[i][j] >= 0) {
    //         if (j && i >= pre[j - 1]) chmax(dp[i - pre[j - 1]][j - 1], dp[i][j]);
    //         if (j < k && i >= a[j]) chmax(dp[i - a[j]][n - 1], dp[i][j] + 1);
    //     }
    // }
    // int ans = 0;
    // rep (i, 0, m + 1) chmax(ans, *max_element(all(dp[i])));
    // cout << ans << '\n';  
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}