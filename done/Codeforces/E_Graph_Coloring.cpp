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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int dp[5005][5005], opt[5005][5005];

void solve() {
    int n, m; cin >> n >> m;
    vector<int> cnt(3);
    rep (i, 0, 3) cin >> cnt[i];
    vector<vector<int>> adj(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bool f = 0;
    vector<int> col(n, -1);
    vector<vector<int>> cc;
    vector<int> w;
    auto dfs = [&](auto self, int u) -> void {
        cc.back().push_back(u);
        if (col[u] == 1) w.back()++;
        for (int v : adj[u]) {
            if (col[v] != -1) {
                if (col[u] == col[v]) f = 1;
            } else {
                col[v] = col[u] ^ 1;
                self(self, v);
            }
        }
    };
    dp[0][0] = 1;
    int ccc = 0;
    rep (i, 0, n) if (col[i] == -1) {
        ccc++;
        col[i] = 0;
        cc.push_back({});
        w.push_back(0);
        dfs(dfs, i);
        if (f) {
            cout << "NO\n";
            return;
        }
        for (int j = 0; j <= n; j++) {
            int b = ssize(cc.back()) - w.back();
            if (j - w.back() >= 0 && dp[ccc - 1][j - w.back()]) {
                dp[ccc][j] = 1;
                opt[ccc][j] = w.back();
            }
            if (j - b >= 0 && dp[ccc - 1][j - b]) {
                dp[ccc][j] = 1;
                opt[ccc][j] = b;
            }
        }
    }
    if (!dp[ccc][cnt[1]]) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (int i = ccc, j = cnt[1]; i > 0; --i) {
        if (opt[i][j] != w[i - 1]) for (int v : cc[i - 1]) col[v] ^= 1;
        for (int v : cc[i - 1]) if (col[v] == 0 && cnt[2]) {
            col[v] = 2;
            cnt[2]--;
        }
        j -= opt[i][j];
    }
    rep (i, 0, n) cout << col[i] + 1;
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}