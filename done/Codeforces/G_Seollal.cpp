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

int dx[] = {0, 1, -1, 0}, dy[] = {1, 0, 0, -1};

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

void solve() {
    int n, m; cin >> n >> m;
    vector<string> g(n);
    rep (i, 0, n) cin >> g[i];
    vector<pii> edge;
    auto id = [&](int x, int y) -> int {
        return x * m + y;
    };
    rep (i, 0, n) rep (j, 0, m) {
        if (i && g[i - 1][j] == 'O' && g[i][j] == 'O') edge.push_back({id(i - 1, j), id(i, j)}); 
        if (j && g[i][j - 1] == 'O' && g[i][j] == 'O') edge.push_back({id(i, j - 1), id(i, j)});
    }
    int sz = ssize(edge);
    /*
    M1 = xx matroid, M2 = xx matroid
    y<-s if I+y   satisfies M1
    y->t if I+y   satisfies M2
    x<-y if I-x+y satisfies M2
    x->y if I-x+y satisfies M1
    交換圖點權：
    -w[e] if e \in I
    w[e] otherwise
    */
    vector<int> I(sz, 0);
    while (true) {
        vector<vector<int>> adj(sz + 2);
        int s = sz, t = s + 1;
        auto M1 = [&]() -> void { // graph matroid
            {   // y<-s
                UnionFind dsu(n * m);
                rep (i, 0, sz) if (I[i]) {
                    dsu.Union(edge[i].fi, edge[i].se);
                } 
                rep (y, 0, sz) if (!I[y]) {
                    if (!dsu.same(edge[y].fi, edge[y].se)) {
                        adj[s].push_back(y);
                    }
                }
            }   
            {   // x->y
                rep (x, 0, sz) if (I[x]) {
                    UnionFind dsu(n * m);
                    rep (i, 0, sz) if (I[i] && i != x) {
                        dsu.Union(edge[i].fi, edge[i].se);
                    }
                    rep (y, 0, sz) if (!I[y]) {
                        if (!dsu.same(edge[y].fi, edge[y].se)) {
                            adj[x].push_back(y);
                        }
                    }
                }
            }
        };
        auto M2 = [&]() -> void { // uniform matroid
            {   // y->t
                vector<int> deg(n * m, 0);
                rep (i, 0, sz) if (I[i]) deg[edge[i].fi]++, deg[edge[i].se]++;
                rep (y, 0, sz) if (!I[y]) {
                    const auto &[u, v] = edge[y];
                    bool f = 1;
                    if (u == 0) f = 0;
                    else if ((u / m + u % m) % 2 == 0 && deg[u] >= 2) f = 0;
                    if ((v / m + v % m) % 2 == 0 && deg[v] >= 2) f = 0; 
                    if (f) adj[y].push_back(t);
                }
            }
            {   // x<-y
                rep (x, 0, sz) if (I[x]) {
                    vector<int> deg(n * m, 0);
                    rep (i, 0, sz) if (I[i] && i != x) deg[edge[i].fi]++, deg[edge[i].se]++;
                    rep (y, 0, sz) if (!I[y]) {
                        const auto &[u, v] = edge[y];
                        bool f = 1;
                        if (u == 0) f = 0;
                        else if ((u / m + u % m) % 2 == 0 && deg[u] >= 2) f = 0;
                        if ((v / m + v % m) % 2 == 0 && deg[v] >= 2) f = 0; 
                        if (f) adj[y].push_back(x);
                    }
                }
            }
        };
        auto augment = [&]() -> bool { // 註解掉的是帶權版
            vector<int> vis(sz + 2, 0), dis(sz + 2, IINF), from(sz + 2, -1);
            queue<int> q;
            vis[s] = 1;
            dis[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                // vis[u] = 0;
                for (int v : adj[u]) {
                    int w = 1; // no weight -> 1
                    if (chmin(dis[v], dis[u] + w)) {
                        from[v] = u;
                        // if (!vis[v]) {
                            // vis[v] = 1;
                            q.push(v);
                        // }
                    }
                }
            }
            if (from[t] == -1) return false;
            for (int cur = from[t];; cur = from[cur]) {
                if (cur == -1 || cur == s) break;
                I[cur] ^= 1;
            }
            return true;
        };
        M1(), M2();
        if (!augment()) break;
    }
    vector<int> deg(n * m);
    UnionFind dsu(n * m);
    rep (i, 0, sz) if (I[i]) {
        const auto &[u, v] = edge[i];
        deg[u]++, deg[v]++;
        dsu.Union(u, v);
    }
    rep (i, 0, n) rep (j, 0, m) if (i + j > 0 && g[i][j] == 'O' && (i + j) % 2 == 0) {
        if (deg[id(i, j)] != 2) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    rep (i, 0, sz) if (!I[i] && !dsu.same(edge[i].fi, edge[i].se)) {
        dsu.Union(edge[i].fi, edge[i].se);
        I[i] = 1;
    } 
    vector has(n * m, vector<bool>(n * m));
    rep (i, 0, sz) if (I[i]) has[edge[i].fi][edge[i].se] = has[edge[i].se][edge[i].fi] = 1;
    rep (i, 0, n) {
        rep (j, 0, m) {
            cout << g[i][j];
            if (j < m - 1) {
                if (has[id(i, j)][id(i, j + 1)]) cout << 'O';
                else cout << ' ';
            }
        }
        cout << '\n';
        if (i < n - 1) {
            rep (j, 0, m) {
                if (has[id(i, j)][id(i + 1, j)]) cout << 'O';
                else cout << ' ';
                if (j < m - 1) cout << ' ';
            }
            cout << '\n';
        }
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}