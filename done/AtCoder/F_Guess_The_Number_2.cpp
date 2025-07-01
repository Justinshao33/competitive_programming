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

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// return {x, T}
// a: moduli, b: remainders
// x: first non-negative solution, T: minimum period
pair<ll, ll> exCRT(auto &a, auto &b) {
    auto [m1, r1] = tie(a[0], b[0]);
    for (int i = 1; i < ssize(a); i++) {
        auto [m2, r2] = tie(a[i], b[i]);
        ll x, y;
        ll g = exgcd(m1, m2, x, y);
        if ((r2 - r1) % g) { // no solution
            return {-1, -1};
        }
        x = (__int128(x) * (r2 - r1) / g) % (m2 / g);
        if (x < 0) {
            x += (m2 / g);
        }
        r1 = m1 * x + r1;
        m1 = lcm(m1, m2);
    }
    r1 %= m1;
    if (r1 < 0) {
        r1 += m1;
    }
    return {r1, m1};
};

void solve() {
    vector len{4, 9, 5, 7, 11, 13, 17, 19, 23};
    vector<int> A;
    for (int ptr = 1; int x : len) {
        rep (i, 0, x) {
            A.pb(ptr + (i + 1) % x);
        }
        ptr = ssize(A) + 1;
    }
    int m = ssize(A);
    cout << m << endl;
    for (int x : A) cout << x << " ";
    cout << endl;
    vector<int> B(m);
    rep (i, 0, m) cin >> B[i];
    vector<int> a, b;
    for (int cur = 1; int x : len) {
        int nxt = B[cur - 1];
        a.pb(x);
        b.pb(nxt - cur);
        cur += x;
    }
    auto [x, T] = exCRT(a, b);
    cout << x << endl;
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}