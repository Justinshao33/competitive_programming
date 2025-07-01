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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i];
    multiset<ll> l1, l2, r1, r2; // 1 choose, 2 no
    rep (i, 0, n) r2.insert(a[i]);
    ll sl = 0, sr = 0;
    rep (i, 0, k) {
        sr += *r2.begin();
        r1.insert(r2.extract(r2.begin()));
    }
    ll ans = sr;
    rep (i, 0, n) {
        if (r1.contains(a[i])) {
            sr -= a[i];
            l2.insert(r1.extract(a[i]));
        } else {
            l2.insert(r2.extract(a[i]));
        }
        while (!l1.empty() && !l2.empty() && *l1.rbegin() > *l2.begin()) {
            ll v = *l1.rbegin(), v2 = *l2.begin();
            sl += v2 - v;
            l1.insert(l2.extract(v2));
            l2.insert(l1.extract(v));
        }
        while (l1.size() + r1.size() != k) {
            if (r2.empty()) {
                sl += *l2.begin();
                l1.insert(l2.extract(l2.begin()));
            } else {
                sr += *r2.begin();
                r1.insert(r2.extract(r2.begin()));
            }
        }
        while (!r1.empty() && !l2.empty() && sl < sr) {
            sl += *l2.begin();
            l1.insert(l2.extract(l2.begin()));
            ll v = *r1.rbegin();
            sr -= v;
            r2.insert(r1.extract(v));
        }
        chmin(ans, max(sl, sr));
        if (!l1.empty() && !r2.empty()) chmin(ans, max(sl - *l1.rbegin(), sr + *r2.begin()));
        debug(sl, sr);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}