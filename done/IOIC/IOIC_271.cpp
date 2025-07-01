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

int in[MAXN << 2], out[MAXN << 2], cnt = 0, id[MAXN]; 
vector<int> adj[MAXN << 2];

void build(int pos, int l, int r) {
    if (l == r) {
        in[pos] = out[pos] = id[l] = ++cnt;
        return;
    }
    int mid = l + r >> 1;
    in[pos] = ++cnt;
    out[pos] = ++cnt;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    adj[in[lpos]].pb(in[pos]);
    adj[in[rpos]].pb(in[pos]);
    adj[out[pos]].pb(out[lpos]);
    adj[out[pos]].pb(out[rpos]);
}

void add(int pos, int l, int r, int ql, int qr, int t, int v) {
    if (ql == l && qr == r) {
        if (t == 2) adj[id[v]].pb(out[pos]);
        else adj[in[pos]].pb(id[v]);
        return;
    }
    int mid = l + r >> 1;
    if (qr <= mid) add(lpos, l, mid, ql, qr, t, v); 
    else if (ql > mid) add(rpos, mid + 1, r, ql, qr, t, v);
    else {
        add(lpos, l, mid, ql, mid, t, v);
        add(rpos, mid + 1, r, mid + 1, qr, t, v);
    }
}

void solve() {
    int n, m; cin >> n >> m;
    build(1, 1, n);
    rep (i, 0, m) {
        int t; cin >> t;
        if (t == 1) {
            int u, v; cin >> u >> v;
            adj[id[u]].pb(id[v]);
        } else {
            int u, l, r; cin >> u >> l >> r;
            add(1, 1, n, l, r, t, u);
        }
    }
    vector<int> dfn(cnt + 1, 0), low(cnt + 1), scc(cnt + 1), st;
    vector<bool> inst(cnt + 1, 0);
    int cnt2 = 0, sccid = 0;
    auto dfs = [&](auto self, int u) -> void {
        st.pb(u);
        inst[u] = true;
        dfn[u] = low[u] = ++cnt2;
        for(int v : adj[u]){
            if(!inst[v] && dfn[v]) continue;
            if(!dfn[v]) self(self, v);
            chmin(low[u], low[v]);
        }
        if(low[u] == dfn[u]){
            sccid++;
            while(st.back() != u){
                inst[st.back()] = false;
                scc[st.back()] = sccid;
                st.pop_back();
            }
            scc[u] = sccid;
            inst[u] = false;
            st.pop_back();
        }
    };
    rep (i, 1, cnt + 1) if (!dfn[i]) {
        dfs(dfs, i);
    }
    vector<vector<int>> reb(sccid + 1);
    rep (i, 1, cnt + 1) {
        for (int v : adj[i]) {
            if (scc[v] != scc[i]) reb[scc[i]].pb(scc[v]);
        }
    }
    int ans = 0;
    vector<int> vis(sccid + 1, 0);
    auto dfs2 = [&](auto self, int u) -> void {
        vis[u] = 1;
        for (int v : reb[u]) {
            if (vis[v]) {
                if (vis[v] == 2) {
                    ans--;
                    vis[v] = 1;
                }
                continue;
            }
            self(self, v);
        }
    };
    rep (i, 1, n + 1) if (!vis[scc[id[i]]]) {
        ans++;
        dfs2(dfs2, scc[id[i]]);
        vis[scc[id[i]]] = 2;
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}