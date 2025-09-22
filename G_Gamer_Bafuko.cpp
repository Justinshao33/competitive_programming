#include <bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

namespace ranges = std::ranges;
namespace views = std::views;

// #ifdef LOCAL
// #include "debug.h"
// #else
#define debug(...) void(0)
// #endif

int cnt;

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    x--;
    y--;
    if (y == 0) std::swap(x, y);
    std::vector<std::vector<int>> adj(n), nodup(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        if (std::minmax(u, v) == std::minmax(x, y)) continue;
        if (u == y) u = x;
        if (v == y) v = x;
        nodup[u].push_back(v);
        nodup[v].push_back(u);
    }

    std::vector<int> dep(n, -1), par(n, -1);
    auto bfs = [&](int s, auto &adj) -> void {
        int n = adj.size();
        std::fill(dep.begin(), dep.begin() + n, -1);
        std::fill(par.begin(), par.begin() + n, -1);
        std::queue<int> q;
        q.emplace(s);    
        dep[s] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto &y : adj[x]) {
                if (dep[y] == -1) {
                    dep[y] = dep[x] + 1;
                    par[y] = x;
                    q.emplace(y);
                }
            }
        }
    };

    int len = 0;
    auto diameter = [&](auto &adj) {
        bfs(0, adj);
        bfs(ranges::max_element(dep | views::take(ssize(adj))) - dep.begin(), adj);
        return ranges::max(dep | views::take(ssize(adj)));
    };
    
    bfs(x, adj);
    std::vector<bool> cycle(n);
    std::vector<int> cid;
    cycle[y] = true;
    cid.push_back(y);
    for (int i = par[y]; i != -1; i = par[i]) {
        cycle[i] = true;
        cid.push_back(i);
    }
    len = ranges::count(cycle, true);
    int rem = diameter(adj);
    adj[x].push_back(y);
    adj[y].push_back(x);

    if (len == 2) {
        std::cout << 2 * (n - 2) - diameter(nodup) << '\n';
        return;
    }

    if (len == n) {
        std::cout << len - 2 << "\n";
        return;
    }
    
    for (int t = 0; t < 2; t++) {
        int tot = 0;
        int mx = 0, mx2 = 0;
        std::vector<int> id(n, -1);
        std::vector<int> d(len, 0);
        for (int j = 0; int i : cid) {
            tot = 0;
            std::vector<std::vector<int>> g;
            auto bruh = [&](auto &&self, int x, int p) -> void {
                if (id[x] == -1) {
                    id[x] = tot++;
                    g.push_back({});
                }
                for (auto &y : adj[x]) {
                    if (y == p or cycle[y]) {
                        continue;
                    }
                    self(self, y, x);
                    g[id[x]].push_back(id[y]);
                    g[id[y]].push_back(id[x]);
                }
            };
            bruh(bruh, i, -1);
            int D = diameter(g);
            bfs(0, g);
            d[j] = ranges::max(dep | views::take(ssize(g)));
            rem = std::max(rem, len - 1 + std::max(D, d[j] + 1));
            if (j) {
                rem = std::max(rem, len - 1 + 1 + d[j] + d[j - 1]);
                if (j != len - 1) rem = std::max(rem, d[j] + j + mx + 2);
                rem = std::max(rem, len + d[j] - j + mx2 + 2 - 1);
            }
            mx = std::max(mx, d[j] - j);
            mx2 = std::max(mx2, d[j] + j);
            j++;
        }
        reverse(cid.begin(), cid.end());
        rem = std::max(rem, len - 1 + d[0] + d.back());
    }
    std::cout << 2 * (n - 1) - rem << "\n";    
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        cnt++;
        solve();
    }

    return 0;
}