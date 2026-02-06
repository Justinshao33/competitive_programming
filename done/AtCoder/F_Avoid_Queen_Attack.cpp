#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

void solve() {
    int n, m; cin >> n >> m;
    set<int> r, c, d, ad;
    rep (i, 0, m) {
        int x, y; cin >> x >> y;
        r.insert(x);
        c.insert(y);
        d.insert(x + y);
        ad.insert(x - y);
    }
    int ans = (n - ssize(r)) * (n - ssize(c));
    for (int di : d) {
        set<int> dup_ad;
        if (di <= n) ans -= di - 1;
        else ans -= 2 * n - di + 1;
        for (int x : r) if (x + 1 <= di && di <= x + n) dup_ad.insert(x - (di - x));
        for (int y : c) if (y + 1 <= di && di <= y + n) dup_ad.insert((di - y) - y);
        ans += ssize(dup_ad); 
    }
    for (int adi : ad) {
        if (adi <= 0) ans -= adi + n; 
        else ans -= n - adi;
        set<int> dup_d;
        for (int x : r) if (x - n <= adi && adi <= x - 1) dup_d.insert(x + (x - adi)); 
        for (int y : c) if (1 - y <= adi && adi <= n - y) dup_d.insert((adi + y) + y);
        for (int di : d) if ((adi + di) % 2 == 0) {
            int x = (adi + di) / 2, y = di - x;
            if (1 <= x && x <= n && 1 <= y && y <= n) {
                dup_d.insert(x + y);
            }
        }
        ans += ssize(dup_d);
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}