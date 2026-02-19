#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

template <typename T>
struct Dinic {
    
    const T INF = numeric_limits<T>::max() / 2;

    struct edge {
        int v, r; T rc;
    };

    vector<vector<edge>> adj;
    vector<int> dis, it;
    Dinic(int n) : adj(n), dis(n), it(n) {}

    void add_edge(int u, int v, T c) {
        adj[u].pb({v, adj[v].size(), c});
        adj[v].pb({u, adj[u].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(all(dis), IINF);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& [v, r, rc] : adj[u]) {
                if (dis[v] < IINF || rc == 0) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        return dis[t] < IINF;
    }

    T dfs(int u, int t, T cap) {
        if (u == t || cap == 0) return cap;
        for (int &i = it[u]; i < (int)adj[u].size(); ++i) {
            auto &[v, r, rc] = adj[u][i];
            if (dis[v] != dis[u] + 1) continue;
            T tmp = dfs(v, t, min(cap, rc));
            if (tmp > 0) {
                rc -= tmp;
                adj[v][r].rc += tmp;
                return tmp;
            }
        }
        return 0;
    }

    T flow(int s, int t) {
        T ans = 0, tmp;
        while (bfs(s, t)) {
            fill(all(it), 0);
            while ((tmp = dfs(s, t, INF)) > 0) {
                ans += tmp;
            }
        }
        return ans;
    }

    bool inScut(int u) { return dis[u] < IINF; }
};

void solve() {
    int n, A, B; cin >> n >> A >> B;
    int dx[8] = {A, B, B, A, -A, -B, -B, -A}, dy[8] = {B, A, -A, -B, -B, -A, A, B};
    vector<string> g(n);
    rep (i, 0, n) cin >> g[i];
    Dinic<int> G(n * n + 2);
    int s = n * n, t = s + 1;
    vector col(n, vector<int>(n, -1));
    auto dfs = [&](auto self, int x, int y) -> void {
        rep (k, 0, 8) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if (col[nx][ny] == -1) {
                col[nx][ny] = col[x][y] ^ 1;
                self(self, nx, ny);
            }
        }
    };
    rep (i, 0, n) rep (j, 0, n) if (col[i][j] == -1) {
        col[i][j] = 0;
        dfs(dfs, i, j);
    }
    int emp = 0;
    rep (i, 0, n) rep (j, 0, n) {
        if (g[i][j] == '#') continue;
        emp++;
        if (col[i][j] == 0) G.add_edge(s, i * n + j, 1);
        else G.add_edge(i * n + j, t, 1);
        if (col[i][j] == 0) {
            rep (k, 0, 8) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n || g[nx][ny] == '#') continue;
                G.add_edge(i * n + j, nx * n + ny, 1);
            }
        }
    }
    int ans = G.flow(s, t);
    // cout << emp - ans << '\n';
    rep (i, 0, n) rep (j, 0, n) {
        if (g[i][j] == '#') continue;
        if (col[i][j] == 0 && G.inScut(i * n + j)) g[i][j] = 'o';
        if (col[i][j] == 1 && !G.inScut(i * n + j)) g[i][j] = 'o';
    }
    rep (i, 0, n) cout << g[i] << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}