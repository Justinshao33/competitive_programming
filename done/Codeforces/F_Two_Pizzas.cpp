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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> b(n);
    rep (i, 0, n) {
        int k; cin >> k;
        rep (j, 0, k) {
            int f; cin >> f;
            b[i].pb(f - 1);
        }
    }
    vector<int> c(m);
    vector<vector<int>> a(m);
    rep (i, 0, m) {
        cin >> c[i];
        int r; cin >> r;
        rep (j, 0, r) {
            int f; cin >> f;
            a[i].pb(f - 1);
        }
    }
    const int C = 512;
    vector<int> cnt(C, 0);
    rep (i, 0, n) {
        int mask = 0;
        for (int x : b[i]) mask |= 1 << x;
        cnt[mask]++;
    }
    vector<pii> mn(C, {IINF, -1}), smn(C, {IINF, -1});
    rep (i, 0, m) {
        int mask = 0;
        for (int x : a[i]) mask |= 1 << x;
        if (mn[mask].fi > c[i]) {
            smn[mask] = mn[mask];
            mn[mask] = {c[i], i};
        } else if (chmin(smn[mask].fi, c[i])) {
            smn[mask].se = i;
        }    
    }
    // cout << mn[15] << ' ' << smn[15] << '\n';
    int p1 = -1, p2 = -1, ans = INT_MAX, ans2 = 0;
    rep (i, 0, C) rep (j, 0, C) {
        int cc = 0;
        if (mn[i].se == -1 || mn[j].se == -1) continue;
        if (i == j && smn[i].se == -1) continue;
        if (i == j) cc = mn[i].fi + smn[j].fi;
        else cc = mn[i].fi + mn[j].fi;
        int res = 0;
        rep (k, 0, C) if (((i | j) & k) == k) {
            res += cnt[k];
        }
        if (ans2 > res || (ans2 == res && cc >= ans)) continue;
        ans2 = res;
        ans = cc;
        p1 = mn[i].se; p2 = (i == j ? smn[j].se : mn[j].se); 
    } 
    // cout << ans << ' ' << ans2 << '\n';
    cout << p1 + 1 << ' ' << p2 + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}