// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

#include<bits/extc++.h>
using namespace __gnu_pbds;
template<typename T> using RBT = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct info {
    int u, v, w;
};

struct info2 {
    int v, x, k, id;
};

struct UnionFind {
    vector<int> pa, sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b, int c) {
        a = find(a), b = find(b);
        if (a == b) return false;
        sz[c] += sz[a] + sz[b];
        sz[a] = sz[b] = c;
        return true;
    }
};


void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<info> edge(m);
    vector<RBT<pii>> st(2 * n);

    rep (i, 0, n) {
        int h; cin >> h;
        st[i].insert({h, i});
    }
    for (auto &[u, v, w] : edge) { 
        cin >> u >> v >> w;
        u--, v--;
    }
    
    vector<int> w(2 * n, 0);
    vector<vector<int>> adj(2 * n), pa(2 * n, vector<int>(20));
    UnionFind dsu(2 * n);
    int id = n;

    sort(all(edge), [](auto a, auto b) {
        return a.w < b.w;
    });

    for (auto [u, v, _w] : edge) {
        u = dsu.find(u), v = dsu.find(v);
        if (dsu.Union(u, v, id)) {
            pa[u][0] = pa[v][0] = pa[id][0] = id;
            adj[id].pb(u);
            adj[id].pb(v);
            w[id] = _w;
            id++;
        }
    }

    vector<info2> query;
    rep (i, 0, q) {
        int v, x, k; cin >> v >> x >> k;
        v--;
        query.pb({v, x, k, i});
    }

    vector<bool> vis(2 * n, 0);
    auto dfs = [&](auto self, int u) -> void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) self(self, v);
            if (st[u].size() < st[v].size()) {
                st[u].swap(st[v]);
            }
            for (pii h : st[v]) {
                st[u].insert(h);
            }
            st[v].clear();
        }
    };

    vector<int> ans(q);

    rep (j, 1, 20) rep (i, 0, 2 * n) pa[i][j] = pa[pa[i][j - 1]][j - 1];
    sort(all(query), [](auto a, auto b) {
        return a.x < b.x;
    });

    for (auto [v, x, k, id] : query) {
        for (int i = 19; i >= 0; --i) {
            if(w[pa[v][i]] <= x) v = pa[v][i];
        }
        dfs(dfs, v);
        int sz = st[v].size();
        if (sz < k) ans[id] = -1;
        else ans[id] = (*st[v].find_by_order(k - 1)).F;
    }

    rep (i, 0, q) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}