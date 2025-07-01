#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include <bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }
 
const int MAXN = 1 << 17, MOD = 1000000007;
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

vector<int> adj[MAXN];

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
    int va, vb, id;
};

struct com {
    bool operator () (const info a, const info b) const {
        return a.va * b.vb > a.vb * b.va;
    }
};

inline void solve() {
    int n = in(), m = in(), t = in();
    vector<int> vis(n, 0);
    rep (i, 0, t) {
        int a = in();
        a--;
        vis[a] = 2;
    }
    rep (i, 0, m) {
        int a = in(), b = in();
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> cc, deg(n, 0);
    priority_queue<info, vector<info>, com> pq;
    auto dfs = [&](auto self, int u) -> void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (vis[v] == 2) continue;
            deg[u]++;
            if (vis[v]) continue;
            self(self, v);
        }
        pq.push({deg[u], adj[u].size(), u});
    };
    int da = 0, db = 1;
    UnionFind dsu(n);
    rep (i, 0, n) if (!vis[i]) {
        dfs(dfs, i);
        while (!pq.empty()) {
            auto [a, b, u] = pq.top();
            pq.pop();
            if (1LL * a * adj[u].size() != 1LL * b * deg[u]) continue;
            cc.pb(u);
            vis[u] = 0;
            for (int v : adj[u]) {
                if (vis[v] == 2) continue;
                deg[v]--;
                if (!vis[v]) continue;
                pq.push({deg[v], adj[v].size(), v});
            }
        }
        reverse(all(cc));
        for (int u : cc) {
            vis[u] = 1;
            for (int v : adj[u]) {
                if (vis[v] == 2 || !vis[v]) continue;
                dsu.Union(u, v);
                deg[u]++;
            }
            if (da * adj[u].size() < deg[u] * db) da = deg[u], db = adj[u].size();
        }
        cc.clear();
    }
    out(da * fpow(db, MOD - 2, MOD) % MOD);
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}