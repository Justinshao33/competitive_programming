#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

pair<vector<vector<int>>, vector<int>> SCC(vector<vector<int>> &adj, vector<int> &pid) {
    // need adj, 0-base
    int n = ssize(adj);
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
    map<pii, int> mp;
    vector<vector<int>> reb(sccid);
    vector<int> id(sccid);
    rep (i, 0, n) {
        id[scc[i]] = pid[i];
        for (int v : adj[i]) if (scc[i] != scc[v] && !mp.contains({scc[i], scc[v]})) {
            reb[scc[i]].pb(scc[v]);
            mp[{scc[i], scc[v]}] = 1;
        }
    }
    return make_pair(reb, id);
}


void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
    }
    vector<int> id(n);
    iota(all(id), 0);
    set<int> S, T;
    auto work = [&]() -> void {
        auto [_adj, _id] = SCC(adj, id);
        int _n = ssize(_adj);
        vector<int> _S, _T;
        vector<bool> ind(n);
        rep (i, 0, _n) {
            if (ssize(_adj[i]) == 0) _T.pb(i);
            for (int v : _adj[i]) ind[v] = 1;
        }
        rep (i, 0, _n) if (!ind[i]) _S.pb(i);
        adj = _adj, id = _id;
        n = ssize(adj);
        S.clear();
        T.clear();
        for (int u : _S) S.insert(u);
        for (int v : _T) T.insert(v);
    };
    work();
    vector<pii> ans;
    vector<bool> vis(n);
    vector<pii> edge;
    for (int u : S) {
        int cur = u;
        while (!T.count(cur)) {
            vis[cur] = 1;
            int nxt = cur;
            for (int v : adj[cur]) {
                if (vis[v]) continue;
                nxt = v;
                if (T.count(nxt)) {
                    break;
                }
            }
            if (nxt == cur) break;
            cur = nxt;
        }
        if (T.count(cur)) {
            vis[cur] = 1;
            edge.pb({u, cur});
        }
    }
    int mat = ssize(edge);
    rep (i, 0, mat) {
        auto [u, v] = edge[i];
        auto [u2, v2] = edge[(i + 1) % mat];
        if (v != u2) {
            adj[v].pb(u2);
            ans.pb({id[v], id[u2]});
        }
    }
    work();
    vector<int> dup;
    for (int u : S) if (T.count(u)) dup.pb(u);
    for (int x : dup) {
        S.erase(x);
        T.erase(x);
    }
    for (auto it = S.begin(), it2 = T.begin(); it != S.end() || it2 != T.end();) {
        if (it == S.end()) ans.pb({id[*it2], id[*S.begin()]});
        else if (it2 == T.end()) ans.pb({id[*T.begin()], id[*it]});
        else ans.pb({id[*it2], id[*it]});
        if (it != S.end()) it++;
        if (it2 != T.end()) it2++;
    }
    cout << ssize(ans) << '\n';
    for (auto [x, y] : ans) cout << x + 1 << ' ' << y + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}