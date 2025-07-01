#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int dp[55][55][55][55], vis[55][55][55][55];

void solve() {
    int n; cin >> n;
    vector<string> g(n);
    rep (i, 0, n) cin >> g[i];
    vector row(n + 1, vector<int>(n + 1, 0));
    auto col = row;
    rep (i, 0, n) rep (j, 0, n) row[i + 1][j + 1] = row[i + 1][j] + (g[i][j] == '#');
    rep (j, 0, n) rep (i, 0, n) col[j + 1][i + 1] = col[j + 1][i] + (g[i][j] == '#');
    auto dfs = [&](auto self, int l, int r, int x, int y) -> int {
        if (l > r || x > y) 
            return 0;
        if (l == r && x == y) 
            return g[x - 1][l - 1] == '#';
        if (vis[l][r][x][y])
            return dp[l][r][x][y];
        vis[l][r][x][y] = 1;
        int res = max(r - l + 1, y - x + 1);
        rep (i, l, r + 1) {
            if (col[i][y] - col[i][x - 1] == 0) {
                int val = self(self, l, i - 1, x, y) + self(self, i + 1, r, x, y);
                chmin(res, val);
            }
        }
        rep (i, x, y + 1) {
            if (row[i][r] - row[i][l - 1] == 0) {
                int val = self(self, l, r, x, i - 1) + self(self, l, r, i + 1, y);
                chmin(res, val);
            }
        }
        return dp[l][r][x][y] = res;
    };
    cout << dfs(dfs, 1, n, 1, n) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}