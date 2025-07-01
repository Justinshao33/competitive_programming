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
    int m; cin >> m;
    vector e(n, vector<int>(n, 0));
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        e[a][b] = e[b][a] = 1;
    }
    vector cost(1 << n, IINF);
    cost[0] = 0;
    rep (bit, 1, 1 << n) {
        vector<int> cur;
        rep (i, 0, 1 << n) if (bit >> i & 1) cur.pb(i);
        int pc = __builtin_popcount(bit);
        if (pc <= 2) continue;
        vector<int> p(pc);
        iota(all(p), 0);
        int tot = 0;
        rep (i, 0, n) if (bit >> i & 1) rep (j, i + 1, n) tot += e[i][j];
        do {
            int res = tot;
            rep (i, 0, pc) {
                if (e[cur[p[i]]][cur[p[(i + 1) % pc]]]) {
                    res -= 1;
                } else {
                    res += 1;
                }
            }
            chmin(cost[bit], res);
        } while (next_permutation(all(p)));
    }
    // cout << cost[(1 << n) - 1] << '\n';
    vector dp(1 << n, IINF);
    dp[0] = 0;
    rep (bit, 1, 1 << n) {
        auto g = dp;
        for (int msk = bit; msk > 0; msk = (msk - 1) & bit) {
            chmin(g[bit], dp[msk ^ bit] + cost[msk]);
        }
        swap(dp, g);
    }
    cout << dp[(1 << n) - 1] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}