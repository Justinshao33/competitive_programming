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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    {
        vector<int> far(n);
        rep (i, 0, n - 1) far[i] = i + 1;
        rep (i, 0, m) {
            int a, b; cin >> a >> b;
            a--, b--;
            chmax(far[a], b);
        }
        rep (i, 0, n - 1) adj[far[i]].push_back(i);
    }
    // \sum dep[y] - dep[lca(x, y)], dep[y] <= dep[x]
    vector<deque<int>> cdep(n);
    vector<int> sz(n);
    int ans = 0;
    auto dfs = [&](auto self, int u, int d) -> void {
        cdep[u].push_back(1);
        sz[u] = 1;
        for (int v : adj[u]) {
            self(self, v, d + 1);
            cdep[v].push_front(0);
            if (ssize(cdep[v]) > ssize(cdep[u])) {
                cdep[u].swap(cdep[v]);
                swap(sz[u], sz[v]);
            }
            int sum = 0, sum2 = 0;
            rep (i, 0, ssize(cdep[v])) sum2 += cdep[u][i];
            for (int i = ssize(cdep[v]) - 1; i >= 0; --i) {
                sum += cdep[v][i];
                sum2 -= cdep[u][i];
                ans -= d * (cdep[u][i] * sum + cdep[v][i] * (sz[u] - sum2));
                cdep[u][i] += cdep[v][i];
            }
            sz[u] += sz[v];
        }
    };
    dfs(dfs, n - 1, 0);
    // cout << ans << '\n';
    int sum = 0;
    // for (int x : cdep[n - 1]) cout << x << ' ';
    for (int i = ssize(cdep[n - 1]) - 1; i >= 0; --i) {
        ans += i * cdep[n - 1][i] * (cdep[n - 1][i] - 1 + sum);
        sum += cdep[n - 1][i];
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}