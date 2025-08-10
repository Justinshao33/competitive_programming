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

void solve() {
    int n; cin >> n;
    map<pll, ll> mp;
    vector<pll> vec;
    rep (i, 0, n) {
        ll x, y; cin >> x >> y;
        if (x == 0 && y == 0) {
            mp[{x, y}]++;
            continue;
        }
        ll g = gcd(abs(x), abs(y));
        x /= g, y /= g;
        if (y < 0) {
            x = -x, y = -y;
        } else if (y == 0 && x < 0) {
            x = -x;
        }
        if (mp.find({x, y}) == mp.end() && !(x == 0 && y == 0)) vec.pb({x, y});
        mp[{x, y}]++;
    }
    using i128 = __int128_t;
    auto cross = [&](pll u, pll v) -> i128 {
        return i128(u.fi) * v.se - i128(v.fi) * u.se;
    };
    auto dot = [&](pll u, pll v) -> i128 {
        return i128(u.fi) * v.fi + i128(v.se) * u.se;
    };
    sort(all(vec), [&](const auto &u, const auto &v) {
        return cross(u, v) > 0;
    });
    debug(vec);
    ll ans = 1;
    int ptr = 0;
    rep (i, 0, ssize(vec)) {
        if (mp[vec[i]] == 0) continue;
        while (ptr < ssize(vec) && dot(vec[i], vec[ptr]) > 0) ptr++;
        if (ptr != ssize(vec) && dot(vec[i], vec[ptr]) == 0) {
            ans = ans * fpow(2, mp[vec[i]], MOD2) % MOD2 + ans * fpow(2, mp[vec[ptr]], MOD2) % MOD2 - ans + MOD2;
            ans %= MOD2;
            mp[vec[ptr]] = 0;
        } else {
            ans = ans * fpow(2, mp[vec[i]], MOD2) % MOD2;
        }
        debug(i, ptr, ans);
    }
    ans = (ans + mp[{0, 0}] - 1 + MOD2) % MOD2;
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}