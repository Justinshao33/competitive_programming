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
    int b = __lg(n);
    vector<vector<ll>> p23(b + 1);
    rep (i, 0, b + 1) {
        for (ll num = 1LL << i; num <= n; num *= 3) {
            p23[i].pb(num);
        }
    }
    auto get = [&](int b, int x) -> int {
        return upper_bound(all(p23[b]), x) - p23[b].begin();
    };
    map<vector<int>, int> memo;
    auto calc = [&](int x) -> int {
        vector<int> lim;
        rep (i, 0, __lg(x) + 1) lim.pb(get(i, x));
        lim.pb(0);
        if (memo.contains(lim)) return memo[lim];
        int m = lim[0];
        vector<int> dp(1 << m, IINF);
        dp[0] = 0;
        rep (j, 1, ssize(lim)) {
            int nm = lim[j];
            vector<int> g(1 << nm, IINF);
            rep (i, 0, m) rep (bit, 0, 1 << m) if (bit >> i & 1) {
                chmin(dp[bit ^ (1 << i)], dp[bit]);
            }
            rep (bit, 0, 1 << m) {
                int msk = (bit | (bit << 1)) & ((1 << m) - 1);
                chmin(g[bit & ((1 << nm) - 1)], dp[(1 << m) - 1 - msk] + __builtin_popcount(bit));
            }
            m = nm;
            swap(dp, g);
        }
        return memo[lim] = dp[0];
    };
    auto no23 = [&](int x) -> int {
        return x - x / 2 - x / 3 + x / 6;
    };
    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        assert(l <= r);
        ans += (no23(r) - no23(l - 1)) * calc(n / l);
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