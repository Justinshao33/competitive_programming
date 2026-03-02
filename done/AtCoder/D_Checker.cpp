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

void solve() {
    int n, k; cin >> n >> k;
    vector b(2 * k, vector<int>(2 * k));
    auto w = b;
    rep (i, 0, n) {
        int x, y; cin >> x >> y;
        char c; cin >> c;
        if (c == 'B') b[x % (2 * k)][y % (2 * k)]++;
        else w[x % (2 * k)][y % (2 * k)]++;
    }
    // W|B -> B|W
    int ans = 0;
    vector dif(2 * k + 1, vector<int>(2 * k + 1, 0));
    auto add = [&](int x, int y, int x2, int y2, int v) -> void {
        if (x2 < x || y2 < y) return;
        dif[x][y] += v;
        dif[x2 + 1][y] -= v;
        dif[x][y2 + 1] -= v;
        dif[x2 + 1][y2 + 1] += v;
    };
    rep (i, 0, k) {
        rep (j, 0, k) {
            // LW
            add(0, 0, k - 1 - i, k - 1 - j, w[i][j]);
            add(k - i, k - j, k - 1, k - j + k - 1, w[i][j]);
            add(0, k + k - j, k - 1 - i, 2 * k - 1, w[i][j]);
            add(0, 0, k - 1 - i, k - 1 - j, w[i + k][j + k]);
            add(k - i, k - j, k - 1, k - j + k - 1, w[i + k][j + k]);
            add(0, k + k - j, k - 1 - i, 2 * k - 1, w[i + k][j + k]);
            // LB
            add(k - i, 0, k - 1, k - 1 - j, b[i][j]);
            add(0, k - j, k - 1 - i, k - j + k - 1, b[i][j]);
            add(k - i, k + k - j, k - 1, 2 * k - 1, b[i][j]);
            add(k - i, 0, k - 1, k - 1 - j, b[i + k][j + k]);
            add(0, k - j, k - 1 - i, k - j + k - 1, b[i + k][j + k]);
            add(k - i, k + k - j, k - 1, 2 * k - 1, b[i + k][j + k]);
            // RB
            add(0, 0, k - 1 - i, k - 1 - j, b[i][j + k]);
            add(k - i, k - j, k - 1, k - j + k - 1, b[i][j + k]);
            add(0, k + k - j, k - 1 - i, 2 * k - 1, b[i][j + k]);
            add(0, 0, k - 1 - i, k - 1 - j, b[i + k][j]);
            add(k - i, k - j, k - 1, k - j + k - 1, b[i + k][j]);
            add(0, k + k - j, k - 1 - i, 2 * k - 1, b[i + k][j]);
            // RW
            add(k - i, 0, k - 1, k - 1 - j, w[i][j + k]);
            add(0, k - j, k - 1 - i, k - j + k - 1, w[i][j + k]);
            add(k - i, k + k - j, k - 1, 2 * k - 1, w[i][j + k]);
            add(k - i, 0, k - 1, k - 1 - j, w[i + k][j]);
            add(0, k - j, k - 1 - i, k - j + k - 1, w[i + k][j]);
            add(k - i, k + k - j, k - 1, 2 * k - 1, w[i + k][j]);
        }
    }
    rep (i, 0, 2 * k) rep (j, 0, 2 * k) {
        if (i) dif[i][j] += dif[i - 1][j];
        if (j) dif[i][j] += dif[i][j - 1];
        if (i && j) dif[i][j] -= dif[i - 1][j - 1];
        chmax(ans, dif[i][j]);
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}