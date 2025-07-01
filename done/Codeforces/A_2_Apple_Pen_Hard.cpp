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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<ll> sh(n, 0), sz(n, 0), sh2(n, 0);
    int p = get_rand(200, 400), p2 = get_rand(200, 400);
    rep (i, 0, n) {
        string s; cin >> s;
        sz[i] = ssize(s);
        for (char c : s) {
            sh[i] = (sh[i] * p + c) % MOD;
            sh2[i] = (sh2[i] * p2 + c) % MOD2;
        }
    }
    string t; cin >> t;
    int m = ssize(t);
    ll hs = 0, hs2 = 0;
    for (char c : t) hs = (hs * p + c) % MOD;
    for (char c : t) hs2 = (hs2 * p2 + c) % MOD2;
    unordered_map<int, int> mp, mp2;
    rep (i, 0, n) mp[sh[i]] = i;
    rep (i, 0, n) mp2[sh2[i]] = i;
    // s + t = a -> s * fpow(x, sz[t])
    vector<pii> ans;
    rep (i, 0, n) {
        if (sz[i] >= m) continue;
        ll res = (hs - sh[i] * fpow(p, m - sz[i], MOD) % MOD + MOD) % MOD;
        ll res2 = (hs2 - sh2[i] * fpow(p2, m - sz[i], MOD2) % MOD2 + MOD2) % MOD2;
        if (mp.count(res) && mp2.count(res2) && mp[res] == mp2[res2] && i != mp[res]) ans.pb(minmax(i, mp[res])); 
    }
    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    cout << ans.size() << '\n';
    for (auto &[x, y] : ans) cout << x + 1 << ' ' << y + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}