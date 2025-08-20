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
    int n, q; cin >> n >> q;
    int mod; cin >> mod;
    auto add = [&](int &a, int b) -> void {
        a += b;
        if (a < 0) a += mod;
        if (a >= mod) a -= mod;
    };
    vector<int> a(n), b(n);
    rep (i, 0, n) cin >> a[i];
    rep (i, 0, n) cin >> b[i];
    vector<int> fib(n + 5);
    fib[1] = fib[2] = 1;
    rep (i, 3, n + 5) {
        add(fib[i], fib[i - 1]);
        add(fib[i], fib[i - 2]);
    }
    // make all a become 0
    // c[i] = a[i] - a[i - 1] - a[i - 2]
    // c[0] = a[0], c[1] = a[1] - a[0]
    // add fib[1...r-l+1] -> a[l]...a[r]
    // c[l] += fib[1], c[r+1] -= f[r-l+1] + f[r-l], c[r+2] -= f[r-l+1]
    // a[1] = a[0] + c[1], a[i] = c[i] + a[i - 1] + a[i - 2]
    vector<int> c(n), d(n);
    c[0] = a[0];
    if (n > 1) add(c[1], a[1] - a[0]);
    rep (i, 2, n) {
        add(c[i], a[i] - a[i - 1]);
        add(c[i], -a[i - 2]);
    }
    d[0] = b[0];
    if (n > 1) add(d[1], b[1] - b[0]);
    rep (i, 2, n) {
        add(d[i], b[i] - b[i - 1]);
        add(d[i], -b[i - 2]);
    }
    set<int> dif;
    rep (i, 0, n) if (c[i] != d[i]) dif.insert(i);
    auto adjust = [&](int x) -> void {
        if (c[x] == d[x]) dif.erase(x);
        else dif.insert(x);
    };
    while (q--) {
        char ch; cin >> ch;
        int l, r; cin >> l >> r;
        if (ch == 'A') {
            add(c[l - 1], fib[1]);
            adjust(l - 1);
            if (r < n) {
                add(c[r], -fib[r - l + 1]);
                add(c[r], -fib[r - l]);
                adjust(r);
            }
            if (r + 1 < n) {
                add(c[r + 1], -fib[r - l + 1]);
                adjust(r + 1);
            }
        } else {
            add(d[l - 1], fib[1]);
            adjust(l - 1);
            if (r < n) {
                add(d[r], -fib[r - l + 1]);
                add(d[r], -fib[r - l]);
                adjust(r);
            }
            if (r + 1 < n) {
                add(d[r + 1], -fib[r - l + 1]);
                adjust(r + 1);
            }
        }
        cout << (dif.empty() ? "YES\n" : "NO\n");
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}