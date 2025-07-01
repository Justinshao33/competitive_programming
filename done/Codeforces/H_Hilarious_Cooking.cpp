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

ll calc(ll a, ll b) {
    if (a > b) return 0;
    return (a + b) * (b - a + 1) / 2;
}

void solve() {
    ll T, n, m; cin >> T >> n >> m;
    vector<ll> a(m), b(m);
    rep (i, 0, m) cin >> a[i] >> b[i];
    rep (i, 1, m) if (a[i] - a[i - 1] < b[i] - b[i - 1]) {
        cout << "No\n";
        return;
    }
    ll mx = calc(b[0], b[0] + a[0] - 1), mn = calc(max(0LL, b[0] - a[0] + 1), b[0]);
    rep (i, 0, m - 1) {
        mx -= b[i], mn -= b[i];
        ll l = b[i], r = b[i + 1];
        if (l > r) swap(l, r);
        ll gap = a[i + 1] - a[i] + 1 - max(0LL, r - l);
        mx += calc(l, r - 1);
        mx += calc(r, r + (gap - 1) / 2) * 2 - (gap % 2) * (r + (gap - 1) / 2);
        mn += calc(l + 1, r);
        mn += calc(max(0LL, l - (gap - 1) / 2), l) * 2 - (gap % 2) * max(0LL, l - (gap - 1) / 2);
    }
    mx += calc(b[m - 1] + 1, b[m - 1] + n - a[m - 1]);
    mn += calc(max(0LL, b[m - 1] - (n - a[m - 1])), max(0LL, b[m - 1] - 1));
    cout << ((mn <= T && T <= mx) ? "Yes\n" : "No\n");
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}