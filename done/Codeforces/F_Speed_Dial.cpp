#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 505, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, K; cin >> n >> K;
    vector trie(MAXN, vector<int>(10, 0));
    vector<int> frq(MAXN);
    int id = 0;
    rep (i, 0, n) {
        string s; cin >> s;
        int m; cin >> m;
        int cur = 0;
        for (char c : s) {
            if (!trie[cur][c - '0']) trie[cur][c - '0'] = ++id;
            cur = trie[cur][c - '0'];
        }
        frq[cur] += m;
    }
    vector dp(MAXN, vector (MAXN, vector<int> (K + 2, LINF)));
    auto dfs = [&](auto self, int u, int d) -> void {
        rep (i, 0, d + 1) rep (j, 0, K + 1) dp[u][i][j] = i * frq[u];
        rep (i, 0, 10) {
            int v = trie[u][i];
            if (!v) continue;
            self(self, v, d + 1);
            rep (j, 0, d + 1) {
                for (int x = K; x >= 0; --x) {
                    dp[u][j][x] += dp[v][j + 1][0];
                    rep (k, 1, x + 1) {
                        chmin(dp[u][j][x], dp[u][j][x - k] + dp[v][j + 1][k]);
                        chmin(dp[u][j][x], dp[u][j][x - k] + dp[v][0][k - 1]);
                    }
                }
            }
        }
    };
    dfs(dfs, 0, 0);
    cout << dp[0][0][K] << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}