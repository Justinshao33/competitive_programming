#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
// #pragma GCC optimize("O3,unroll-loops")
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
const ll LINF = 4e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, k; cin >> n >> k;
    k++;
    // 選 k+1 條不相連的鏈串在一起，求最大直徑
    vector<vector<pll>> adj(n);
    rep (i, 0, n - 1) {
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }
    vector dp(n, vector<pll>(3)); // 0/1/2 -> degree
    auto dfs = [&](auto self, int u, int pa, ll p) -> void {
        dp[u][0] = {0, 0};
        dp[u][1] = {-LINF, 0};
        dp[u][2] = {-p, 1};
        for (auto [v, w] : adj[u]) {
            if (v == pa) continue;
            self(self, v, u, p);
            vector<pll> nxt(3, {-LINF, 0});
            rep (i, 0, 3) {
                nxt[0] = max(nxt[0], dp[u][0] + dp[v][i]);
                nxt[1] = max(nxt[1], dp[u][1] + dp[v][i]);
                nxt[2] = max(nxt[2], dp[u][2] + dp[v][i]);
            }
            for (int i : {0, 1}) for (int j : {0, 1}) {
                int add = (!i || !j) - (i || j);
                nxt[i + 1] = max(nxt[i + 1], dp[u][i] + dp[v][j] + pll(w - add * p, add));
            }
            swap(dp[u], nxt);
        }
    };
    ll l = -5e11, r = 5e11, ans = -LINF;
    while (r - l > 1) {
        ll mid = l + r >> 1;
        dfs(dfs, 0, -1, mid);
        pll mx = max({dp[0][0], dp[0][1], dp[0][2]});
        if (mx.se >= k) {
            l = mid;
            ans = mx.fi + mid * k;
        } else {
            r = mid;
        }
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