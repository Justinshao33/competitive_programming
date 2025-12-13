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
    pii s, t; cin >> s.fi >> s.se >> t.fi >> t.se;
    pii X, Y; cin >> X.fi >> X.se >> Y.fi >> Y.se;
    if (X.fi > X.se) swap(X.fi, X.se); 
    if (Y.fi > Y.se) swap(Y.fi, Y.se); 
    if ((s.fi - t.fi) % 2 != 0 || (s.se - t.se) % 2 != 0) {
        cout << "No\n";
        return;
    }
    if (X.fi == X.se && Y.fi == Y.se) {
        if (s == t) {
            cout << "Yes\n";
        } else if (make_pair(2 * X.fi - s.fi, 2 * Y.fi - s.se) == t) {
            cout << "Yes\n" << X.fi << ' ' << Y.fi << '\n';
        } else {
            cout << "No\n";
        }
        return;
    }
    if ((X.fi == X.se && (t.fi != s.fi && t.fi != 2 * X.fi - s.fi)) || (Y.fi == Y.se && (t.se != s.se && t.se != 2 * Y.fi - s.se))) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    vector<pii> ope;
    if (X.fi == X.se && t.fi == 2 * X.fi - s.fi) {
        ope.push_back({X.fi, Y.fi});
        s.fi = t.fi;
        s.se = 2 * Y.fi - s.se;
    }
    if (Y.fi == Y.se && t.se == 2 * Y.fi - s.se) {
        ope.push_back({X.fi, Y.fi});
        s.fi = 2 * X.fi - s.fi;
        s.se = t.se;
    }
    while (s.fi < t.fi) {
        ope.push_back({X.fi, Y.fi});
        ope.push_back({X.fi + 1, Y.fi});
        s.fi += 2;
    }
    while (s.fi > t.fi) {
        ope.push_back({X.fi + 1, Y.fi});
        ope.push_back({X.fi, Y.fi});
        s.fi -= 2;
    }
    while (s.se < t.se) {
        ope.push_back({X.fi, Y.fi});
        ope.push_back({X.fi, Y.fi + 1});
        s.se += 2;
    }
    while (s.se > t.se) {
        ope.push_back({X.fi, Y.fi + 1});
        ope.push_back({X.fi, Y.fi});
        s.se -= 2;
    }
    assert(s == t);
    for (const auto &[x, y] : ope) cout << x << ' ' << y << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}