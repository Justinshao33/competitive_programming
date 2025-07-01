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
 
const int MAXN = 5e4 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

struct info {
    int u, v, w;
    bool operator < (const info& oth) const {
        return w < oth.w;
    }
};

int tree[MAXN << 2];

void mod(int pos, int l, int r, int idx, int val) {
    if (l == r) {
        tree[pos] += val;
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx, val);
    else mod(rpos, mid + 1, r, idx, val);
    tree[pos] = tree[lpos] + tree[rpos];
} 

int query(int pos, int l, int r, int k) {
    if (l == r) return l;
    int mid = l + r >> 1;
    if (tree[lpos] >= k) return query(lpos, l, mid, k);
    else return query(rpos, mid + 1, r, k - tree[lpos]); 
}

void solve() {
    int n, m; cin >> n >> m;
    vector<info> edge(m);
    for (auto &[u, v, w] : edge) {
        cin >> u >> v >> w;
        u--, v--;
    }
    sort(all(edge));
    vector<pii> fa(n, {-1, -1});
    vector<int> L(m, 0), vis(n, 0);
    int tag = 0;
    UnionFind dsu(n);
    auto make_root = [&](int x) -> void {
        pii son = {-1, -1};
        while (x != -1) {
            auto p = fa[x];
            fa[x] = son;
            son = {x, p.S};
            x = p.F;
        }
    };
    auto del = [&](int a, int b, int id) -> void {
        tag++;
        vector<int> r(2), c(2);
        r[0] = c[0] = a;
        r[1] = c[1] = b;
        vector<vector<int>> path(2);
        int lca = -1;
        while (lca == -1) {
            rep (i, 0, 2) if (c[i] != -1) {
                path[i].pb(c[i]);
                if (vis[c[i]] == tag) {
                    lca = c[i];
                    break;
                }
                vis[c[i]] = tag;
                c[i] = fa[c[i]].F;
            }
            if (lca != -1) break;
        }
        int mi = IINF;
        rep (i, 0, 2) for (int v : path[i]) {
            if (v == lca) break;
            chmin(mi, fa[v].S);
        }
        L[id] = mi + 1;
        rep (i, 0, 2) for (int v : path[i]) {
            if (v == lca) break;
            if (mi == fa[v].S) {
                fa[v] = {-1, -1};
                make_root(r[i]);
                fa[r[i]] = {r[i ^ 1], id};
                return;
            }
        }
    };
    rep (i, 0, m) {
        auto &[u, v, w] = edge[i];
        if (dsu.size(u) < dsu.size(v)) swap(u, v);
        if (dsu.Union(u, v)) {
            make_root(v);
            fa[v] = {u, i};
        } else {
            del(u, v, i);
        }
    }
    vector<int> p(m);
    iota(all(p), 0);
    sort(all(p), [&](int i, int j) {
        return L[i] < L[j];
    });
    int ptr = 0, ans = IINF;
    vis.resize(m, 0);
    rep (i, 0, m) {
        while (ptr < m && L[p[ptr]] <= i) {
            if (p[ptr] >= i) {
                mod(1, 1, m, p[ptr] + 1, 1);
                vis[p[ptr]] = 1;
            }
            ptr++;
        }
        if (i && vis[i - 1]) mod(1, 1, m, i, -1);
        if (tree[1] < n - 1) continue;
        int pos = query(1, 1, m, n - 1);
        chmin(ans, edge[pos - 1].w - edge[i].w);
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