#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n);
    vector<pii> edge;
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        edge.push_back({a, b});
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
    vector<int> dep(n, 0), dfn(n, -1);
    vector pa(n, vector<int>(20));
    vector<bool> tedg(m, 0);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int p) -> void {
        dfn[u] = cnt++;
        for (auto [v, id] : adj[u]) {
            if (v == p || dfn[v] != -1) continue;
            pa[v][0] = u;
            dep[v] = dep[u] + 1;
            tedg[id] = 1;
            self(self, v, u);
        }
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) {
        pa[i][j] = pa[pa[i][j - 1]][j - 1];
    }
    auto lca = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        rep (i, 0, 20) if (d & (1 << i)) a = pa[a][i];
        if (a == b) return a;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return pa[a][0];
    };
    // need LCA
    vector<vector<pii>> vir(n);

    auto clear = [&](auto self, int u) -> void {
        for (auto [v, w] : vir[u]) {
            self(self, v);
        }
        vir[u].clear();
    };
    
    auto build = [&](vector<int> &v) -> void {
        // maybe dont need to sort when do it while dfs
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
                vir[st.end()[-2]].pb({st.back(), dep[st.back()] - dep[st.end()[-2]]});
                vir[st.back()].pb({st.end()[-2], dep[st.back()] - dep[st.end()[-2]]});
                st.pop_back();
            }

            if (st.back() != p) {
                vir[p].pb({st.back(), dep[st.back()] - dep[p]});
                vir[st.back()].pb({p, dep[st.back()] - dep[p]});
                st.pop_back();
                st.pb(p);
            }

            st.pb(v[i]);
        }

        while (st.size() >= 2) {
            vir[st.end()[-2]].pb({st.back(), dep[st.back()] - dep[st.end()[-2]]});
            vir[st.back()].pb({st.end()[-2], dep[st.back()] - dep[st.end()[-2]]});
            st.pop_back();
        }
    };
    vector<int> node{0, n - 1};
    rep (i, 0, m) if (!tedg[i]) {
        node.push_back(edge[i].fi);
        node.push_back(edge[i].se);
    }
    sort(all(node));
    node.erase(unique(all(node)), node.end());
    build(node);
    rep (i, 0, m) if (!tedg[i]) {
        vir[edge[i].se].push_back({edge[i].fi, 1});
        vir[edge[i].fi].push_back({edge[i].se, 1});
    }
    vector<int> ans(n, 0);
    vector<bool> vis(n, 0);
    auto dfs2 = [&](auto self, int u, int d) -> void {
        if (u == n - 1) {
            ans[d]++;
            return;
        }
        vis[u] = 1;
        for (auto [v, w] : vir[u]) {
            if (vis[v]) continue;
            self(self, v, d + w);
        }
        vis[u] = 0;
    };
    dfs2(dfs2, 0, 0);
    rep (i, 1, n) cout << ans[i] << " \n" [i == n - 1];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}