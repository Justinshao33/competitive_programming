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

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

ll CEIL(ll a, ll b) {
    if (b < 0) tie(a, b) = make_pair(-a, -b);
    return (a >= 0 ? (a + b - 1) / b : a / b);
}

ll FLOOR(ll a, ll b) {
    if (b < 0) tie(a, b) = make_pair(-a, -b);
    return (a >= 0 ? a / b : (a - b + 1) / b);
}

void solve() {
    ll a, b, a2, b2, L, R; cin >> a >> b >> a2 >> b2 >> L >> R;
    // ak + b = a2l + b2
    // a * k - a2 * l = b2 - b
    ll A = a, B = -a2, C = b2 - b;
    ll x0, y0, g = exgcd(A, B, x0, y0);
    if (C % g) {
        cout << 0 << '\n';
        return;
    }
    if (g < 0) {
        g = -g, x0 = -x0, y0 = -y0;
    }
    // x = x0 + k * B, y = y0 - k * A
    // p = a1 * k1 + b1, p = a1 * (x0 + k * B) + b1
    // L <= p <= R
    // k1, k2 >= 0
    // calc k
    L = max<ll>(0, CEIL(L - b, a));
    R = FLOOR(R - b, a);
    if (L > R) {
        cout << 0 << '\n';
        return;
    }
    ll l = CEIL(R * g - x0 * C, B), r = FLOOR(L * g - x0 * C, B);
    r = min(r, FLOOR(y0 * C, A));
    cout << max<ll>(0, r - l + 1) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}