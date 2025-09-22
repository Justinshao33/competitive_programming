#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

#define int i64
#define all(a) a.begin(), a.end()
#define rep(a, b, c) for (int a = b; a < c; a++)

#ifdef PEPPA
template <typename R>
concept I = ranges::range<R> && !std::same_as<ranges::range_value_t<R>, char>;
template <typename A, typename B>
std::ostream &operator<<(std::ostream &o, const std::pair<A, B> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
template <I T>
std::ostream &operator<<(std::ostream &o, const T &v) {
    o << "{";
    int f = 0;
    for (auto &&i : v) o << (f++ ? " " : "") << i;
    return o << "}";
}
void debug__(int c, auto &&...a) {
    std::cerr << "\e[1;" << c << "m";
    (..., (std::cerr << a << " "));
    std::cerr << "\e[0m" << std::endl;
}
#define debug_(c, x...) debug__(c, __LINE__, "[" + std::string(#x) + "]", x)
#define debug(x...) debug_(93, x)
#else
#define debug(x...) void(0)
#endif

bool chmin(auto& a, auto b) { return (b < a and (a = b, true)); }
bool chmax(auto& a, auto b) { return (a < b and (a = b, true)); }

// bel[x]: x is belong bel[x]-th jellyfish
// len[x]: cycle length of x-th jellyfish
// ord[x]: order of x in cycle (x == root[x])
struct FunctionalGraph {
    int n, cnt = 0;
    std::vector<std::vector<int>> adj;
    std::vector<int> f, bel, dep, ord, root, in, out, len;
    FunctionalGraph(int n) : n(n), adj(n), root(n),
    bel(n, -1), dep(n), ord(n), in(n), out(n) {};
    void dfs(int u) {
        in[u] = cnt++;
        for (int v : adj[u]) {
            if (bel[v] == -1) {
                dep[v] = dep[u] + 1;
                root[v] = root[u];
                bel[v] = bel[u];
                dfs(v);
            }
        } 
        out[u] = cnt;
    }
    void build(const auto &f_) {
        f = f_;
        for (int i = 0; i < n; i++) {
            adj[f[i]].push_back(i);
        }
        std::vector<int> vis(n, -1);
        for (int i = 0; i < n; i++) {
            if (vis[i] == -1) {
                int x = i;
                while (vis[x] == -1) {
                    vis[x] = i;
                    x = f[x];
                }
                if (vis[x] != i) {
                    continue;
                }
                int s = x, l = 0;
                do {
                    bel[x] = len.size();
                    ord[x] = l++;
                    root[x] = x;
                    x = f[x];
                } while (x != s);
                len.push_back(l);
            }
        } 
        for (int i = 0; i < n; i++) {
            if (root[i] == i) {
                dfs(i);
            }
        }
    }
    int dist(int x, int y) { // x -> y
        if (bel[x] != bel[y]) {
            return -1;
        } else if (dep[x] < dep[y]) {
            return -1;
        } else if (dep[y] != 0) {
            if (in[y] <= in[x] and in[x] < out[y]) {
                return dep[x] - dep[y];
            }
            return -1;
        } else {
            return dep[x] + (ord[y] - ord[root[x]] + len[bel[x]]) % len[bel[x]];
        }
    }
};

int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> G(n);
    rep (i, 0, n) cin >> G[i];
    vector id(n, vector(m, vector<int>(4, 0)));
    int cnt = 0;
    rep (i, 0, n) rep (j, 0, m) {
        if (G[i][j] == '#') continue;
        rep (k, 0, 4) {
            id[i][j][k] = cnt++;
        }
    }
    vector<int> to(cnt);
    rep (i, 0, n) rep (j, 0, m) {
        if (G[i][j] == '#') continue;
        rep (k, 0, 4) {
            int nxt = -1;
            rep (l, 0, 4) {
                int nk = (k + l) % 4;
                int nx = i + dx[nk], ny = j + dy[nk];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m || G[nx][ny] == '#') {
                    continue;
                }
                // debug(i, j, k, "->", nx, ny, nk);
                nxt = id[nx][ny][nk];
                break;
            }
            if (nxt == -1) to[id[i][j][k]] = id[i][j][k];
            else to[id[i][j][k]] = nxt;
        }
    }
    FunctionalGraph FG(cnt);
    FG.build(to);
    int q; cin >> q;
    const int INF = 1e9 + 7;
    while (q--) {
        int rs, rt, cs, ct; cin >> rs >> cs >> rt >> ct;
        rs--, rt--, cs--, ct--;
        int dis = INF;
        rep (i, 0, 4) {
            rep (j, 0, 4) {
                int d = FG.dist(id[rs][cs][i], id[rt][ct][j]);
                if (d >= 0) chmin(dis, d);
            }
        }
        cout << (dis == INF ? -1 : dis + 1) << '\n';
    }

}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    // std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}