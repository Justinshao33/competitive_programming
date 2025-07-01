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

double dp[1 << 12][1 << 5][20];

void solve() {
    int n, m; cin >> n >> m;
    vector<pii> town(n), chest(m);
    for (auto &[x, y] : town) cin >> x >> y;
    for (auto &[x, y] : chest) cin >> x >> y;
    rep (i, 0, 1 << n) rep (j, 0, 1 << m) rep (k, 0, n + m) dp[i][j][k] = 1e15;
    auto dis = [&](pii x, pii y) -> double {
        return sqrt(1LL * (x.F - y.F) * (x.F - y.F) + 1LL * (x.S - y.S) * (x.S - y.S));
    };
    rep (i, 0, n) dp[1 << i][0][i] = dis({0, 0}, town[i]);
    rep (i, 0, m) dp[0][1 << i][n + i] = dis({0, 0}, chest[i]);
    rep (bit, 0, 1 << n) rep (bit2, 0, 1 << m) {
        int acc = 1 << __builtin_popcount(bit2);
        rep (i, 0, n) if (bit >> i & 1) {
            rep (j, 0, n) if (bit >> j & 1 ^ 1) {
                chmin(dp[bit | (1 << j)][bit2][j], dp[bit][bit2][i] + dis(town[i], town[j]) / acc);
            }
            rep (j, 0, m) if (bit2 >> j & 1 ^ 1) {
                chmin(dp[bit][bit2 | (1 << j)][n + j], dp[bit][bit2][i] + dis(town[i], chest[j]) / acc);
            }
        }
        rep (i, 0, m) if (bit2 >> i & 1) {
            rep (j, 0, n) if (bit >> j & 1 ^ 1) {
                chmin(dp[bit | (1 << j)][bit2][j], dp[bit][bit2][n + i] + dis(chest[i], town[j]) / acc);
            }
            rep (j, 0, m) if (bit2 >> j & 1 ^ 1) {
                chmin(dp[bit][bit2 | (1 << j)][n + j], dp[bit][bit2][n + i] + dis(chest[i], chest[j]) / acc);
            }
        }
    }
    double ans = 1e15;
    rep (i, 0, n) rep (j, 0, 1 << m) {
        int acc = 1 << __builtin_popcount(j);
        chmin(ans, dp[(1 << n) - 1][j][i] + dis(town[i], {0, 0}) / acc);
    }
    rep (j, 0, 1 << m) rep (i, 0, m) if (j >> i & 1) {
        int acc = 1 << __builtin_popcount(j);
        chmin(ans, dp[(1 << n) - 1][j][n + i] + dis(chest[i], {0, 0}) / acc);
    }
    cout << fixed << setprecision(10) << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}