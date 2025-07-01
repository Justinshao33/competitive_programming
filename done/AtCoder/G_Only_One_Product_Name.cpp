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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Dinic {
    
    struct edge {
        int v, r; ll rc;
    };

    vector<vector<edge>> adj;
    vector<int> dis, it;
    Dinic(int n) : adj(n), dis(n), it(n) {}

    void add_edge(int u, int v, ll c) {
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

    ll dfs(int u, int t, ll cap) {
        if (u == t || cap == 0) return cap;
        for (int &i = it[u]; i < (int)adj[u].size(); ++i) {
            auto &[v, r, rc] = adj[u][i];
            if (dis[v] != dis[u] + 1) continue;
            ll tmp = dfs(v, t, min(cap, rc));
            if (tmp > 0) {
                rc -= tmp;
                adj[v][r].rc += tmp;
                return tmp;
            }
        }
        return 0;
    }

    ll flow(int s, int t) {
        ll ans = 0, tmp;
        while (bfs(s, t)) {
            fill(all(it), 0);
            while ((tmp = dfs(s, t, IINF)) > 0) {
                ans += tmp;
            }
        }
        return ans;
    }

    bool inScut(int u) { return dis[u] < IINF; }
};

void solve() {
    int n; cin >> n;
    vector<string> str(n);
    rep (i, 0, n) cin >> str[i];
    vector<vector<int>> adj(n);
    rep (i, 0, n) rep (j, 0, n) {
        if (str[i][1] == str[j][0]) adj[i].pb(j);
    }
    // need adj, 0-base
    int cnt = 0, m = 0;
    vector<int> dfn(n, 0), low(n, 0), scc(n, 0);
    vector<bool> inst(n, 0);
    stack<int> st;
    auto dfs = [&](auto self, int u) -> void {
        st.push(u);
        inst[u] = true;
        dfn[u] = low[u] = ++cnt;
        for(int v : adj[u]){
            if(!inst[v] && dfn[v]) continue;
            if(!dfn[v]) self(self, v);
            chmin(low[u], low[v]);
        }
        if(low[u] == dfn[u]){
            while(st.top() != u){
                inst[st.top()] = false;
                scc[st.top()] = m;
                st.pop();
            }
            scc[u] = m;
            inst[u] = false;
            st.pop();
            m++;
        }
    };
    rep(i, 0, n){
        if(!dfn[i]) dfs(dfs, i);
    }
    vector edge(m, vector<int>(m, 0));
    rep (i, 0, n) for (int j : adj[i]) {
        // cout << scc[i] << ' ' << scc[j] << '\n';
        edge[scc[i]][scc[j]] = 1;
    }
    rep (k, 0, m) rep (i, 0, m) rep (j, 0, m) edge[i][j] |= edge[i][k] & edge[k][j];
    // cout << edge;
    Dinic G(2 * m + 2);
    int s = 2 * m, t = s + 1;
    rep (i, 0, m) {
        G.add_edge(s, i, 1);
        G.add_edge(i + m, t, 1);
        rep (j, 0, i) if (edge[i][j]) {
            // cout << i << ' ' << j << '\n';
            G.add_edge(i, j + m, 1);
        }
    }
    // cout << G.flow(s, t) << '\n';
    cout << m - G.flow(s, t) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}