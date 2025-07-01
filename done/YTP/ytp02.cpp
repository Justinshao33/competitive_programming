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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

#define int long long

void solve() {
    int n, k; cin >> n >> k;
    ll x, y, z; cin >> x >> y >> z;
    vector<int> c(n);
    rep (i, 0, n) cin >> c[i];
    vector<int> st(1 << n, -1);
    rep (bit, 1, 1 << n) {
        int sum = 0;
        rep (i, 0, n) if (bit & (1 << i)) sum += c[i];
        st[bit] = sum;
    }
    ll ans = LINF;
    int sz = 1 << n;
    for (int d = 1; d * d <= k; ++d) if (k % d == 0) {
        rep (i, 0, sz) rep (j, 0, sz) {
            if (st[i] == -1 || st[j] == -1 || (i & j)) continue;
            ll cur = z * (__builtin_popcount(i) + __builtin_popcount(j) - 2), cur2 = cur;
            int oth = k / d;
            int a = st[i], b = st[j];
            if (a > b) swap(a, b);
            if (a < d) cur += x * (d - a);
            if (a > d) cur += y * (a - d);
            if (b > oth) cur += y * (b - oth);
            if (b < oth) cur += x * (oth - b);
            if (b < d) cur2 += x * (d - b);
            if (b > d) cur2 += y * (b - d);
            if (a > oth) cur2 += y * (a - oth);
            if (a < oth) cur2 += x * (oth - a);
            chmin(ans, cur);
            chmin(ans, cur2);
        }
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