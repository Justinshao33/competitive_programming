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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
    }
    // need adj, 0-base
    int cnt = 0, sccid = 0;
    vector<int> dfn(n, 0), low(n, 0), scc(n, 0);
    vector<bool> inst(n, 0);
    stack<int> st;
    auto dfs = [&](auto self, int u) -> void {
        st.push(u);
        inst[u] = true;
        dfn[u] = low[u] = ++cnt;
        for (int v : adj[u]) {
            if (!inst[v] && dfn[v]) continue;
            if (!dfn[v]) self(self, v);
            chmin(low[u], low[v]);
        }
        if (low[u] == dfn[u]) {
            while (st.top() != u) {
                inst[st.top()] = false;
                scc[st.top()] = sccid;
                st.pop();
            }
            scc[u] = sccid;
            inst[u] = false;
            st.pop();
            sccid++;
        }
    };
    rep (i, 0, n) if (!dfn[i]) dfs(dfs, i);
    m = sccid;
    vector<vector<int>> reb(n + n + m);
    vector<int> ind(2 * n + m, 0);
    rep (i, 0, n) {
        reb[i].pb(2 * n + scc[i]);
        ind[2 * n + scc[i]]++;
        reb[2 * n + scc[i]].pb(n + i);
        ind[n + i]++;
        for (int v : adj[i]) if (scc[i] != scc[v]) {
            reb[n + i].pb(v);
            ind[v]++;
        }
    }
    vector<int> dp(2 * n, 0), dp2(n, 0), vis(n, 0);
    vector<vector<int>> cc(m);
    queue<int> q;
    rep (i, 0, n) if (!ind[i]) {
        dp[i] = 1;
        q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u >= 2 * n) {
            auto dfs2 = [&](auto self, int u, int d, int st) -> void {
                vis[u] = 1;
                chmax(dp2[u], dp[st] + d);
                for (int v : adj[u]) if (!vis[v] && scc[u] == scc[v]) {
                    self(self, v, d + 1, st);
                }
                vis[u] = 0;
            };
            for (int st : cc[u - 2 * n]) dfs2(dfs2, st, 0, st);
            for (int v : cc[u - 2 * n]) chmax(dp[v + n], dp2[v]);
        } else if (u < n) {
            for (int v : reb[u]) cc[v - 2 * n].pb(u);
        } else {
            for (int v : reb[u]) chmax(dp[v], dp[u] + 1);
        }
        for (int v : reb[u]) {
            if (--ind[v] == 0) q.push(v);
        }
    }
    cout << *max_element(all(dp)) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}