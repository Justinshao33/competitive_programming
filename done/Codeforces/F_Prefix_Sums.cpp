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

ll K;

template<class T>
struct Mat{
    vector<vector<T>> a;
    int x, y;
    Mat(int _x, int _y) {
        a.resize(_x, vector<T>(_y, 0));
        x = _x;
        y = _y;
    }
    Mat operator * (Mat &inp) {
        Mat res(x, inp.y);
        rep (i, 0, x) rep (j, 0, inp.y) rep (k, 0, y) {
            res.a[i][j] += min<ll>(K, __int128(1) * a[i][k] * inp.a[k][j]);
            res.a[i][j] = min<ll>(K, res.a[i][j]);
        }
        return res;
    }
    Mat powpow(Mat base, ll exp) { // exp = exp
        Mat res(base.x, base.y);
        rep (i, 0, res.x) res.a[i][i] = 1;
        while (exp > 0) {
            if (exp & 1) res = res * base;
            base = base * base;
            exp >>= 1;
        }
        return res;
    }
};

void solve() {
    int n; cin >> n >> K;
    vector<ll> a;
    rep (i, 0, n) {
        int b; cin >> b;
        if (a.empty() && b == 0) continue;
        a.push_back(b);
    }
    n = ssize(a);
    if (*max_element(all(a)) >= K) {
        cout << 0 << '\n';
        return;
    }
    // vector<ll> b(4, 0);
    // b[0] = 1;
    // int cnt = 0;
    // while (b.back() < LINF) {
    //     partial_sum(all(b), b.begin());
    //     cnt++;
    // }   
    // cout << cnt << '\n';
    if (n >= 4) {
        int cnt = 0;
        while (*max_element(all(a)) < K) {
            cnt++;
            partial_sum(all(a), a.begin());
        }
        cout << cnt << '\n';
        return;
    }
    if (n == 2) {
        cout << (K - a[1] + a[0] - 1) / a[0] << '\n';
        return;
    }
    assert(n == 3);
    ll l = 0, r = 1e10 + 5;
    Mat<ll> base(3, 3);
    base.a = {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}};
    while (r - l > 1) {
        ll mid = l + r >> 1;
        Mat M = base.powpow(base, mid);
        if (max({__int128(1) * a[0] * M.a[0][0], 
            __int128(1) * a[0] * M.a[1][0] + __int128(1) * a[1] * M.a[1][1], 
            __int128(1) * a[0] * M.a[2][0] + __int128(1) * a[1] * M.a[2][1] + __int128(1) * a[2] * M.a[2][2]}) 
                >= K) r = mid;
        else l = mid;
    }
    cout << r << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}   