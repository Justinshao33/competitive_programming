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

struct MCMF {

    struct edge { int v, r; ll rc, k; }; // k => cost
    
    vector<vector<edge>> adj;
    vector<int> who, who_eid;
    MCMF(int n) : adj(n), who(n), who_eid(n) {}

    void add_edge(int u, int v, ll c, ll k) {
        adj[u].pb({v, adj[v].size(), c, k});
        adj[v].pb({u, adj[u].size() - 1, 0, -k});
    }

    ll spfa(int s, int t) {
        fill(all(who), -1);
        vector<bool> vis(who.size(), 0);
        vector<ll> dis(who.size(), LLONG_MAX);
        queue<int> q;
        vis[s] = true;
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            rep (i, 0, adj[u].size()) {
                auto &[v, r, rc, k] = adj[u][i];
                if (rc > 0 && dis[u] + k < dis[v]) {
                    dis[v] = dis[u] + k;
                    who[v] = u;
                    who_eid[v] = i;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dis[t];
    }

    pll flow(int s, int t) { // apply spfa find the lowest cost path
        ll flow = 0, cost = 0, d;
        while ((d = spfa(s, t)) < LLONG_MAX) {
            ll cur = LLONG_MAX;
            for (int u = t; u != s; u = who[u]) {
                cur = min(cur, adj[who[u]][who_eid[u]].rc);
            }
            flow += cur;
            cost += d * cur; // per flow's cost * current_flows
            for (int u = t; u != s; u = who[u]) {
                adj[who[u]][who_eid[u]].rc -= cur;
                adj[u][ adj[who[u]][who_eid[u]].r ].rc += cur;
            }
        }
        return make_pair(flow, cost);
    }

};

void solve() {
    int n, m; cin >> n >> m;
    int s = n + m, t = s + 1;
    MCMF G(n + m + 2), G2(n + m + 2);
    rep (i, 0, n) {
        int a; cin >> a;
        G.add_edge(s, i, a, 0);
        G2.add_edge(s, i, a, 0);
    }
    rep (i, 0, m) {
        int b; cin >> b;
        G.add_edge(n + i, t, b, 0);
        G2.add_edge(n + i, t, b, 0);
    }
    rep (i, 0, n) rep (j, 0, m) {
        int c; cin >> c;
        G.add_edge(i, j + n, IINF, c);
        G2.add_edge(i, j + n, IINF, -c);
    }
    cout << G.flow(s, t).S << '\n' << -G2.flow(s, t).S << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}