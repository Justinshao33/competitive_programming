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
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

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
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> dep(n), dfn(n);
    int cnt = 0;
    vector<vector<int>> pa(n, vector<int>(20));
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

    // need LCA
    vector<vector<int>> vir(n);

    auto clear = [&](auto self, int u) -> void {
        for (int v : vir[u]) {
            self(self, v);
        }
        vir[u].clear();
    };
    
    auto build = [&](vector<int> &v) -> void {
        sort(all(v), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        if (v[0] != 0) {
            v.insert(v.begin(), 0);
        }
        int k = v.size();
        vector<int> st;
        rep (i, 0, k) {
            if (st.empty()) {
                st.pb(v[i]);
                continue;
            }
            int p = lca(v[i], st.back());         
            if (p == st.back()) {
                st.pb(v[i]);
                continue;
            }
            while (st.size() >= 2 && dep[st.end()[-2]] >= dep[p]) {
                vir[st.end()[-2]].pb(st.back());
                st.pop_back();
            }
            if (st.back() != p) {
                vir[p].pb(st.back());
                st.pop_back();
                st.pb(p);
            }
            st.pb(v[i]);
        }
        while (st.size() >= 2) {
            vir[st.end()[-2]].pb(st.back());
            st.pop_back();
        }
    };

    int ans;

    auto dfs2 = [&](auto self, int u) -> void {
        for (int v : vir[u]) {
            ans += dep[v] - dep[u];
            self(self, v);
        }
    };

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<int> v(k);
        rep (i, 0, k) {
            cin >> v[i];
            v[i]--;
        }
        bool f = (v[0] == 0);
        clear(clear, 0);
        build(v);
        ans = 0;
        dfs2(dfs2, 0);
        if (!f && vir[0].size() == 1) ans -= dep[vir[0][0]] - dep[0];
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