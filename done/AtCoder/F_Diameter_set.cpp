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

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> dep(n), dep2(n);
    auto dfs = [&](auto self, int u, int pa, vector<int> &d) -> void {
        for (int v : adj[u]) {
            if (v == pa) continue;
            d[v] = d[u] + 1;
            self(self, v, u, d);
        }
    };
    dep[0] = 0;
    dfs(dfs, 0, -1, dep);
    int L = max_element(all(dep)) - dep.begin();
    dep[L] = 0;
    dfs(dfs, L, -1, dep);
    int R = max_element(all(dep)) - dep.begin();
    dfs(dfs, R, -1, dep2);
    if (dep[R] & 1) {
        ll cl = 0, cr = 0;
        cl = count(all(dep), dep[R]);
        cr = count(all(dep2), dep2[L]);
        cout << cl * cr % MOD << '\n';
    } else {
        int m;
        rep (i, 0, n) if ((dep[i] == dep2[i]) && (dep[i] == dep[R] / 2)) m = i;
        // cout << dep << dep2;
        // cout << L << ' ' << R << '\n';
        // cout << m << '\n';
        ll ans = 1;
        dep2[m] = 0;
        dfs(dfs, m, -1, dep2);
        auto dfs2 = [&](auto self, int u, int pa) -> int {
            int res = (dep2[u] == dep[R] / 2);
            for (int v : adj[u]) {
                if (v == pa) continue;
                res += self(self, v, u);
            }
            return res;
        };
        ll sub = 0;
        for (int v : adj[m]) {
            // cout << ans << '\n';
            sub += dfs2(dfs2, v, m);
            // cout << sub << '\n';
            ans = ans * (dfs2(dfs2, v, m) + 1) % MOD;
        }
        ans -= sub;
        ans--;
        while (ans < 0) ans += MOD;
        ans %= MOD;
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