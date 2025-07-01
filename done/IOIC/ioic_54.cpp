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

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }

template<typename T>inline void read(T &x) {
    x = 0;
    static int p; p = 1;
    static char c; c = getchar();
    while (!isdigit(c)) { if (c == '-') p = -1; c = getchar();}
    while (isdigit(c)) { x = (x << 1) + (x << 3) + (c - 48); c = getchar();}
    x *= p;
}

void solve() {
    int n, m; read(n), read(m);
    vector<vector<int>> adj(n);
    vector<int> edge(m);
    rep (i, 0, m) {
        int a, b; read(a), read(b);
        a--, b--;
        adj[a].pb(i);
        adj[b].pb(i);
        edge[i] = a ^ b;
    }
    vector<int> dep(n), from(n, -1), used(m, 0);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int pa) -> void {
        for (int i : adj[u]) {
            int v = u ^ edge[i];
            if (v == pa) continue;
            if (from[v] == -1) {
                dep[v] = dep[u] + 1;
                from[v] = i;
                self(self, v, u);
            } else if (dep[v] < dep[u]) {
                used[i]++;
                bool f = used[i] == 2;
                int cur = u;
                while (dep[cur] > dep[v]) {
                    int eid = from[cur];
                    used[eid]++;
                    f |= used[eid] == 2;
                    cur ^= edge[eid];
                }
                if (f) {
                    cout << "No\n";
                    exit(0);
                }
            }
        }
    };
    from[0] = 0;
    dep[0] = 0;
    dfs(dfs, 0, -1);
    cout <<"Yes\n";
}
 
int main() {
    // ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}