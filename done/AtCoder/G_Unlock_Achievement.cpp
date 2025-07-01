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

void solve() {
    int n, m; cin >> n >> m;
    Dinic G(5 * n + m + 2);
    vector<int> a(m + 1);
    rep (i, 1, n + 1) {
        int c; cin >> c;
        G.add_edge(0, i, 0);
        rep (j, 1, 5) {
            G.add_edge(i + n * (j - 1), i + n * j, c * j);
            G.add_edge(i + n * j, i + n * (j - 1), IINF);
        }
        G.add_edge(i + 4 * n, 5 * n + m + 1, c * 4);
    }
    ll sum = 0;
    rep (i, 1, m + 1) {
        cin >> a[i];
        sum += a[i];
    }
    rep (i, 1, m + 1) {
        G.add_edge(0, 5 * n + i, a[i]);
        rep (j, 1, n + 1) {
            int L; cin >> L;
            rep (k, 0, L - 1) {
                G.add_edge(5 * n + i, j + n * k, IINF);
            }
        }
    }
    int cut = G.flow(0, 5 * n + m + 1);
    cout << max(0LL, sum - cut) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}