#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

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
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

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
    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n), cnt(26, 0);
    for (char c : s) cnt[c - 'a']++;
    rep (i, 0, n) cin >> a[i];
    MCMF G(n / 2 + 26 + 2);
    int S = n / 2 + 26, T = S + 1;
    rep (i, 0, 26) G.add_edge(S, i, cnt[i], 0);
    rep (i, 0, n / 2) {
        G.add_edge(26 + i, T, 2, 0);
        if (s[i] == s[n - i - 1]) {
            G.add_edge(s[i] - 'a', 26 + i, 1, -max(a[i], a[n - i - 1]));
            rep (j, 0, 26) if (j != s[i] - 'a') G.add_edge(j, 26 + i, 1, 0);
        } else {
            G.add_edge(s[i] - 'a', 26 + i, 1, -a[i]);
            G.add_edge(s[n - i - 1] - 'a', 26 + i, 1, -a[n - i - 1]);
            rep (j, 0, 26) if (j != s[i] - 'a' && j != s[n - i - 1] - 'a') G.add_edge(j, 26 + i, 1, 0);
        }
    }
    cout << -G.flow(S, T).second << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}