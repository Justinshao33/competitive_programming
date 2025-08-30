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

template <typename T>
struct Dinic {
    const T INF = numeric_limits<T>::max() / 2;
    struct edge {
        int v, r; T rc;
    };
    vector<vector<edge>> adj;
    vector<T> dis, it;
    Dinic(int n) : adj(n), dis(n), it(n) {}
    void add_edge(int u, int v, T c) {
        adj[u].push_back({v, adj[v].size(), c});
        adj[v].push_back({u, adj[u].size() - 1, 0});
    }
    bool bfs(int s, int t) {
        fill(all(dis), INF);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& [v, r, rc] : adj[u]) {
                if (dis[v] < INF || rc == 0) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        return dis[t] < INF;
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

    bool inScut(int u) { return dis[u] < INF; }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    set<int> st;
    for (int i = 0; i * i <= 1e9 + 1000; i++) st.insert(i * i);
    rep (i, 0, n) cin >> a[i];
    Dinic<int> G(2 * n + 2);
    int s = n * 2, t = s + 1;
    rep (i, 0, n) {
        G.add_edge(s, i, 1);
        G.add_edge(n + i, t, 1);
    }
    rep (i, 0, n) {
        rep (j, 1, n + 1) if (st.count(a[i] + j)) {
            G.add_edge(i, n + j - 1, 1);
        }
    }
    cout << (G.flow(s, t) == n ? "YES\n" : "NO\n");
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}