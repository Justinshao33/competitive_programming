#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<vector<int>> col(n);
    rep (i, 0, n) {
        cin >> a[i];
        a[i]--;
        col[a[i]].pb(i);
    }
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> dfn(n), dep(n);
    vector<vector<int>> pa(n, vector<int>(20));
    int cnt = 0;
    auto dfs = [&](auto self, int u, int p) -> void {
        dfn[u] = ++cnt;
        for (int v : adj[u]) {
            if (v == p) continue;
            pa[v][0] = u;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
    };
    dep[0] = 0;
    pa[0][0] = 0;
    dfs(dfs, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) pa[i][j] = pa[pa[i][j - 1]][j - 1];
    auto lca = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        rep (i, 0, 20) if (d & (1 << i)) a = pa[a][i];
        if(a == b) return a;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return pa[a][0];
    };
    vector<vector<int>> vir(n);
    auto clear = [&](auto self, int u) -> void {
        for (int v : vir[u]) {
            self(self, v);
        }
        vir[u].clear();
    };
    auto build = [&](int c) -> void {
        sort(all(col[c]), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        if(col[c][0] != 0) col[c].insert(col[c].begin(), 0);
        vector<int> st;
        for (int u : col[c]) {
            if (st.empty()) {
                st.pb(u);
                continue;
            }
            int p = lca(u, st.back());
            if (p == st.back()) {
                st.pb(u);
                continue;
            }
            while (st.size() >= 2 && dep[st.end()[-2]] >= dep[p]) {
                vir[st.end()[-2]].pb(st.back());
                st.pop_back();
            }
            if (p != st.back()) {
                vir[p].pb(st.back());
                st.pop_back();
                st.pb(p);
            }
            st.pb(u);
        }
        while (st.size() >= 2) {
            vir[st.end()[-2]].pb(st.back());
            st.pop_back();
        }
    };
    ll ans = 0;
    vector<ll> dp(n);
    auto dfs2 = [&](auto self, int u, int c) -> void {
        dp[u] = 1;
        ll res = 0;
        for (int v : vir[u]) {
            self(self, v, c);
            dp[u] = dp[u] * (dp[v] + 1) % MOD;
            res = (res + dp[v]) % MOD;
        }
        if (a[u] == c) {
            ans = (ans + dp[u]) % MOD;
        } else {
            dp[u] = (dp[u] - res - 1 + MOD) % MOD;
            ans = (ans + dp[u]) % MOD;
            dp[u] = (dp[u] + res) % MOD;
        }
    };
    rep (i, 0, n) {
        if (col[i].empty()) continue;
        clear(clear, 0);
        build(i);
        dfs2(dfs2, 0, i);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}