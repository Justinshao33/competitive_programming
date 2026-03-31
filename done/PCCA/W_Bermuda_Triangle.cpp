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

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// ax + b = 0 (mod m)
std::pair<int, int> sol(int a, int b, int m) {
    assert(m > 0);
    b *= -1;
    int x, y;
    int g = exgcd(a, m, x, y);
    if (g < 0) {
        g *= -1, x *= -1, y *= -1;
    }
    if (b % g != 0) return {-1, -1};
    x = x * (b / g) % (m / g);
    if (x < 0) {
        x += m / g;
    }
    return {x, m / g};
}

int CEIL(int a, int b) {
    if (b < 0) a = -a, b = -b;
    return (a >= 0 ? (a + b - 1) / b : a / b);
}

void print(__int128 x) {
    if (x < 0) {
        x = -x;
        cout << '-';
    }
    vector<int> s;
    if (x == 0) {
        s.push_back(0);   
    }
    while (x > 0) {
        s.push_back(x % 10);
        x /= 10;
    }
    while (!s.empty()) {
        cout << s.back();
        s.pop_back();
    }
}

void solve() {
    int n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;
    {
        int g = gcd(vx, vy);
        vx /= g;
        vy /= g;
    }
    auto [x1, t1] = sol(vx, x, n);
    auto [x2, t2] = sol(vy, y, n);
    if (x1 == -1 || x2 == -1) {
        cout << -1 << '\n';
        return;
    }
    int X, Y;
    int g = exgcd(t1, t2, X, Y), c = x2 - x1;
    if (c % g != 0) {
        cout << -1 << '\n';
        return;
    }
    X *= c / g;
    Y *= -c / g;
    int k = max(CEIL(-X * g, t2), CEIL(-Y * g, t1));
    int y1 = X + k * (t2 / g);
    using i128 = __int128_t;
    i128 k2 = x1 + t1 * y1;
    i128 tx = x + i128(1) * vx * k2, ty = y + i128(1) * vy * k2;
    assert(tx % n == 0 && ty % n == 0);
    tx /= n, ty /= n;
    i128 ans = (tx - 1) + (ty - 1) + (tx + ty) / 2 + (max(tx, ty) - min(tx, ty)) / 2;
    print(ans);
    cout << '\n';
    // print(tx);
    // cout << ' ';
    // print(ty);
    // cout << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}