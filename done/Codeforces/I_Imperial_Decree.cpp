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
 
const int MAXN = 2e5 + 5, MOD2 = 998244353, IINF = 1e9 + 7, MOD = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void add(ll &x, ll y) {
    x += y;
    if (x < 0) x += MOD;
    if (x >= MOD) x -= MOD;
}

void solve() {
    int n, m; cin >> n >> m;
    vector p(n, vector<ll>(m));
    ll inv = 0;
    rep (i, 0, n) rep (j, 0, m) {
        cin >> p[i][j];
        add(inv, p[i][j]);
    }
    auto init = [&](auto &c) -> void {
        rep (i, 0, n) {
            rep (j, 1, m) add(c[i][j], c[i][j - 1]); 
            if (i) rep (j, 0, m) add(c[i][j], c[i - 1][j]);
        }
    };
    auto calc = [&](auto &c, int x, int y, int x2, int y2) -> ll {
        if (x2 < 0 || y2 < 0 || x > x2 || y > y2) return 0;
        ll res = c[x2][y2];
        if (x - 1 >= 0) res -= c[x - 1][y2];
        if (y - 1 >= 0) res -= c[x2][y - 1];
        if (x - 1 >= 0 && y - 1 >= 0) res += c[x - 1][y - 1];
        res = (res % MOD + MOD) % MOD;
        return res;
    };
    auto P = p, xP = p, yP = p, xyP = p;
    rep (i, 0, n) rep (j, 0, m) {
        xP[i][j] = xP[i][j] * i % MOD;
        yP[i][j] = yP[i][j] * j % MOD;
        xyP[i][j] = xyP[i][j] * i * j % MOD;
    }
    init(P), init(xP), init(yP), init(xyP);
    // (x1, y1), (x2, y2)
    ll ans = 0, inv3 = fpow(3, MOD - 2, MOD);
    {   // 1. x1 == x2 && y1 == y2
        rep (i, 0, n) rep (j, 0, m) {
            add(ans, p[i][j] * inv3 % MOD * p[i][j] % MOD * inv3 % MOD);
        }    
    }
    {   // 2. x1 == x2 || y1 == y2
        rep (i, 0, n) rep (j, 0, m) {
            // U
            add(ans, inv3 * p[i][j] % MOD * i % MOD * calc(P, 0, j, i - 1, j) % MOD);
            add(ans, -inv3 * p[i][j] % MOD * calc(xP, 0, j, i - 1, j) % MOD);
            // D
            add(ans, -inv3 * p[i][j] % MOD * i % MOD * calc(P, i + 1, j, n - 1, j) % MOD);
            add(ans, inv3 * p[i][j] % MOD * calc(xP, i + 1, j, n - 1, j) % MOD);
            // L
            add(ans, inv3 * p[i][j] % MOD * j % MOD * calc(P, i, 0, i, j - 1) % MOD);
            add(ans, -inv3 * p[i][j] % MOD * calc(yP, i, 0, i, j - 1) % MOD);
            // R
            add(ans, -inv3 * p[i][j] % MOD * j % MOD * calc(P, i, j + 1, i, m - 1) % MOD);
            add(ans, inv3 * p[i][j] % MOD * calc(yP, i, j + 1, i, m - 1) % MOD);
        }
    }
    {   // 3. x1 != x2 && y1 != y2
        rep (i, 0, n) rep (j, 0, m) {
            // LU
            add(ans, p[i][j] * i % MOD * j % MOD * calc(P, 0, 0, i - 1, j - 1) % MOD);
            add(ans, -p[i][j] * i % MOD * calc(yP, 0, 0, i - 1, j - 1) % MOD);
            add(ans, -p[i][j] * j % MOD * calc(xP, 0, 0, i - 1, j - 1) % MOD);
            add(ans, p[i][j] * calc(xyP, 0, 0, i - 1, j - 1) % MOD);
            // RU
            add(ans, -p[i][j] * i % MOD * j % MOD * calc(P, 0, j + 1, i - 1, m - 1) % MOD);
            add(ans, p[i][j] * i % MOD * calc(yP, 0, j + 1, i - 1, m - 1) % MOD);
            add(ans, p[i][j] * j % MOD * calc(xP, 0, j + 1, i - 1, m - 1) % MOD);
            add(ans, -p[i][j] * calc(xyP, 0, j + 1, i - 1, m - 1) % MOD);
            // LD
            add(ans, -p[i][j] * i % MOD * j % MOD * calc(P, i + 1, 0, n - 1, j - 1) % MOD);
            add(ans, p[i][j] * i % MOD * calc(yP, i + 1, 0, n - 1, j - 1) % MOD);
            add(ans, p[i][j] * j % MOD * calc(xP, i + 1, 0, n - 1, j - 1) % MOD);
            add(ans, -p[i][j] * calc(xyP, i + 1, 0, n - 1, j - 1) % MOD);
            // RD
            add(ans, p[i][j] * i % MOD * j % MOD * calc(P, i + 1, j + 1, n - 1, m - 1) % MOD);
            add(ans, -p[i][j] * i % MOD * calc(yP, i + 1, j + 1, n - 1, m - 1) % MOD);
            add(ans, -p[i][j] * j % MOD * calc(xP, i + 1, j + 1, n - 1, m - 1) % MOD);
            add(ans, p[i][j] * calc(xyP, i + 1, j + 1, n - 1, m - 1) % MOD);
        }
    }
    inv = fpow(inv, MOD - 2, MOD);
    cout << ans * inv % MOD * inv % MOD << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}