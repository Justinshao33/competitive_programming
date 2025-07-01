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
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Dinic{

    struct edge {
        int v, r; ll rc;
        int id;
    };

    vector<vector<edge>> adj;
    vector<int> dis, it;
    int cnt = 0;
    Dinic(int n) : adj(n), dis(n), it(n) {}

    void add_edge (int u, int v, int c) {
        adj[u].pb({v, adj[v].size(), c, cnt++});
        adj[v].pb({u, adj[u].size() - 1, 0, -1});
    }

    bool bfs(int s, int t){
        fill(all(dis), IINF);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(const auto& [v, r, rc, _] : adj[u]){
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
            auto &[v, r, rc, _] = adj[u][i];
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
            while(tmp = dfs(s, t, IINF) > 0){
                ans += tmp;
            }
        }
        return ans;
    }

    bool inScut(int u) { return dis[u] < IINF; }

    void get_ans(int s, int t) {
        int k = flow(s, t);
        cout << k << '\n';
        vector<bool> vis(cnt, 0);
        vector<int> path;
        fill(all(it), 0);
        auto dfs2 = [&](auto self, int u) -> void {
            path.pb(u);
            for(auto &[v, r, rc, id] : adj[u]) {
                if (id >= 0 && !vis[id] && rc == 0) {
                    vis[id] = 1;
                    self(self, v);
                    return;
                }
            }
        };
        rep (i, 0, k) {
            dfs2(dfs2, s);
            cout << path.size() << '\n';
            rep (j, 0, path.size()) {
                cout << path[j] + 1 << " \n" [j == path.size() - 1];
            }
            path.clear();
        }
    }
};

void solve(){
    int n, m; cin >> n >> m;
    Dinic G(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        G.add_edge(a, b, 1);
    }
    G.get_ans(0, n - 1);
}
 
int main(){
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}