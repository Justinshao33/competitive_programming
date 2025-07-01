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
 
const int MAXN = 2e5 + 5, MOD2 = 998244353, IINF = 1e9 + 7, MOD = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

#define int long long

void solve() {
    int n, m, ss, tt, x, step; cin >> n >> m >> ss >> tt >> x >> step;
    ss--, tt--;
    
    // dp[i][j][t]: from i->j, length 2^t. pair: {rank (relative to same t), hash}
    // dp[i][j][t] <- dp[i][k][t - 1] + dp[k][j][t - 1], min lexi.(compare {r1, r2}), hash = h1 * x^{2^{t-1}} + h2
    // maybe 離散化 the rank after each round doubling
    
    vector<int> X(30);
    rep (i, 0, 30) X[i] = fpow(x, (1 << i), MOD);

    vector dp(30, vector (n, vector<pii>(n, pii(-1, -1))));
    rep (i, 0, m) {
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        dp[0][a][b] = pii(w, w);
    }

    auto lisan = [&](vector<vector<pii>> &arr) -> void {
        vector<int> dic;
        rep (i, 0, n) rep (j, 0, n) if (arr[i][j].fi != -1) {
            dic.pb(arr[i][j].fi);
        }
        sort(all(dic));
        dic.erase(unique(all(dic)), dic.end());
        rep (i, 0, n) rep (j, 0, n) if (arr[i][j].fi != -1) {
            arr[i][j].fi = lower_bound(all(dic), arr[i][j].fi) - dic.begin();
        }
    };
    
    // build doubling
    lisan(dp[0]);
    rep (t, 1, 30) {
        rep (k, 0, n) rep (i, 0, n) rep (j, 0, n) {
            auto &[r1, h1] = dp[t - 1][i][k];
            auto &[r2, h2] = dp[t - 1][k][j];
            auto &[r, h] = dp[t][i][j];
            if (r1 == -1 || r2 == -1) continue;
            if (r == -1 || r > r1 * (n * n) + r2) {
                r = r1 * (n * n) + r2;
                h = (h1 * X[t - 1] + h2) % MOD;
            }
        }
        lisan(dp[t]);
    }

    // jump
    vector cur(n, vector<pii>(n, pii(-1, -1)));
    cur[ss][ss] = {0, 0};

    rep (t, 0, 30) if (step >> t & 1) {
        vector nxt(n, vector<pii>(n, pii(-1, -1)));
        rep (k, 0, n) rep (i, 0, n) rep (j, 0, n) {
            auto &[r1, h1] = cur[i][k];
            auto &[r2, h2] = dp[t][k][j];
            auto &[r, h] = nxt[i][j];
            if (r1 == -1 || r2 == -1) continue;
            if (r == -1 || r > r1 * (n * n) + r2) {
                r = r1 * (n * n) + r2;
                h = (h1 * X[t] + h2) % MOD;
            }
        }
        swap(cur, nxt);
        lisan(cur);
    }

    cout << cur[ss][tt].se << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}