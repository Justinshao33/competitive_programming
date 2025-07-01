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

struct Dinic{
    
    struct edge {
        int v, r; ll rc;
    };

    vector<vector<edge>> adj;
    vector<int> dis, it;
    Dinic(int n) : adj(n), dis(n), it(n) {}

    void add_edge (int u, int v, ll c) {
        adj[u].pb({v, adj[v].size(), c});
        adj[v].pb({u, adj[u].size() - 1, 0});
    }

    bool bfs(int s, int t){
        fill(all(dis), IINF);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(const auto& [v, r, rc] : adj[u]){
                if(dis[v] < IINF || rc == 0) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        return dis[t] < IINF;
    }

    ll dfs(int u, int t, ll cap){
        if(u == t || cap == 0) return cap;
        for(int &i = it[u]; i < (int)adj[u].size(); ++i){
            auto &[v, r, rc] = adj[u][i];
            if(dis[v] != dis[u] + 1) continue;
            ll tmp = dfs(v, t, min(cap, rc));
            if(tmp > 0){
                rc -= tmp;
                adj[v][r].rc += tmp;
                return tmp;
            }
        }
        return 0;
    }

    ll flow(int s, int t){
        ll ans = 0, tmp;
        while(bfs(s, t)){
            fill(all(it), 0);
            while((tmp = dfs(s, t, IINF)) > 0){
                ans += tmp;
            }
        }
        return ans;
    }

    bool inScut(int u) { return dis[u] < IINF; }
};

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<char>> g(n, vector<char>(m));
    Dinic G(n * m + 4);
    int s = n * m, t = s + 1, s2 = t + 1, t2 = s2 + 1;
    int cnt = 0;
    rep (i, 0, n) rep (j, 0, m) cin >> g[i][j];
    rep (i, 0, n) rep (j, 0, m) {
        if (g[i][j] == '1') continue;
        if ((i + j) & 1) {
            if (g[i][j] == '2') {
                G.add_edge(s2, i * m + j, 1);
                G.add_edge(s, t2, 1);
                cnt++;
            } else {
                G.add_edge(s, i * m + j, 1);
            }
            rep (k, 0, 4) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '1') continue;
                G.add_edge(i * m + j, nx * m + ny, 1);
            }
        } else {
            if (g[i][j] == '2') {
                G.add_edge(s2, t, 1);
                G.add_edge(i * m + j, t2, 1);
                cnt++;
            } else {
                G.add_edge(i * m + j, t, 1);
            }
        }
    }
    G.add_edge(t, s, n * m);
    // G.flow(s2, t2);
    int flow = G.flow(s2, t2);
    // cerr << flow << '\n';
    cout << (flow == cnt ? "Yes\n" : "No\n"); 
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}