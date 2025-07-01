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
const ll LINF = 5e18L + 5;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int r[6][6] = {
    {-1, -1, 5, 4, 2, 3},
    {-1, -1, 4, 5, 3, 2},
    {4, 5, -1, -1, 1, 0},
    {5, 4, -1, -1, 0, 1},
    {3, 2, 0, 1, -1, -1},
    {2, 3, 1, 0, -1, -1}
};

int op(int x) {
    if (x & 1) return x - 1;
    else return x + 1;
}

const int B = 5e5 + 5;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> x(6);
    rep (i, 0, 6) cin >> x[i];
    if (1LL * n * m < B) {
        vector dp(n, vector (m, vector (6, vector<ll>(6, -LINF)))); // d, f
        // front back up down left right
        vector up(6, vector<pii>(6, {-1, -1}));
        auto ri = up;
        rep (i, 0, 6) rep (j, 0, 6) {
            if (i == j || i == op(j)) continue;
            up[i][j] = {j, op(i)};
            ri[i][j] = {r[i][j], j};
        }
        rep (i, 0, 6) {
            rep (j, 0, 6) if (i != j && i != op(j)) {
                dp[0][0][i][j] = x[i];
            }
        }
        rep (k, 0, n) {
            rep (l, 0, m) {
                rep (i, 0, 6) rep (j, 0, 6) {
                    if (up[i][j].fi != -1 && k < n - 1) {
                        chmax(dp[k + 1][l][up[i][j].fi][up[i][j].se], dp[k][l][i][j] + x[up[i][j].fi]);
                    }
                    if (ri[i][j].fi != -1 && l < m - 1) {
                        chmax(dp[k][l + 1][ri[i][j].fi][ri[i][j].se], dp[k][l][i][j] + x[ri[i][j].fi]);
                    }
                }
            }
        }
        ll ans = -LINF;
        rep (i, 0, 6) rep (j, 0, 6) chmax(ans, dp[n - 1][m - 1][i][j]);
        cout << ans << '\n';
    } else {
        ll ans = -LINF;
        ll sum = x[0] + x[1];
        rep (bit, 0, 1 << 6) {
            int la = __builtin_popcount(bit);
            ll res = 0;
            if (la == 2) {
                bool no = 0;
                int f = -1;
                rep (i, 0, 6) if (bit >> i & 1) {
                    if (f == -1) {
                        f = i;
                    } else {
                        if (op(f) == i) {
                            no = 1;
                        }
                    }
                }
                if (no) continue;
            }
            rep (i, 0, 6) if (bit >> i & 1) res += x[i];
            chmax(ans, (n + m - 1 - la) / 2 * sum + res);
        }
        cout << ans << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}