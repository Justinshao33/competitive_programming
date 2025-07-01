#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, k; ll p; cin >> n >> k >> p;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i];
    int h = n / 2, h2 = n - h;
    vector<vector<ll>> L(h + 1), R(h2 + 1);
    rep (bit, 0, 1 << h) {
        int cnt = __builtin_popcount(bit);
        ll res = 0;
        rep (i, 0, h) if (bit & (1 << i)) res += a[i];
        L[cnt].pb(res);
    }
    rep (bit, 0, 1 << h2) {
        int cnt = __builtin_popcount(bit);
        ll res = 0;
        rep (i, 0, h2) if (bit & (1 << i)) res += a[h + i];
        R[cnt].pb(res);
    }
    ll ans = 0;
    rep (i, 1, h2 + 1) sort(all(R[i]));
    rep (i, 1, h + 1)  sort(all(L[i]));
    rep (i, 0, min(k, h) + 1) {
        if (k - i >= 0 && k - i <= h2) {
            for (ll v : L[i]) {
                if (v > p) break;
                ans += upper_bound(all(R[k - i]), p - v) - R[k - i].begin();
            }
        }
    }
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