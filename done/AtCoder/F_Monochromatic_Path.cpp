#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

int dx[2] = {0, 1}, dy[2] = {1, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector<int> ro(n), co(m);
    rep (i, 0, n) cin >> ro[i];
    rep (i, 0, m) cin >> co[i];
    vector<string> G(n);
    rep (i, 0, n) cin >> G[i];
    auto calc = [&](char c) -> int {
        vector dp(n, vector(m, vector(2, vector<int>(2, LINF)))); // r/d, inv?
        rep (fr, 0, 2) rep (fc, 0, 2) {
            if ((G[0][0] ^ fr ^ fc) == c) {
                chmin(dp[0][0][0][fr], fr * ro[0] + fc * co[0]);
                chmin(dp[0][0][1][fc], fr * ro[0] + fc * co[0]);
            }
        }
        int res = LINF;
        rep (i, 0, n) rep (j, 0, m) rep (k, 0, 2) rep (l, 0, 2) {
            if (dp[i][j][k][l] == LINF) continue;
            if (i == n - 1 && j == m - 1) {
                chmin(res, dp[i][j][k][l]);
                continue;
            }
            int ni = i + dx[k], nj = j + dy[k];
            if (ni >= n || nj >= m) continue;
            int cost = 0, dif = (G[ni][nj] ^ l) != c;
            if (dif) cost = k == 0 ? co[nj] : ro[ni];
            rep (d, 0, 2) {
                int nl = k == d ? l : dif;
                chmin(dp[ni][nj][d][nl], dp[i][j][k][l] + cost);
            }
        }
        return res;
    };
    cout << min(calc('0'), calc('1')) << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}