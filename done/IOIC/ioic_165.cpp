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

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
 
const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in(), m = in();
    vector<int> a(n);
    rep (i, 0, n) a[i] = in();
    vector<vector<int>> adj(n);
    rep (i, 0, m) {
        int a = in(), b = in();
        a--, b--;
        adj[a].pb(b);
    }
    vector<int> dfn(n, 0), low(n), scc(n), st;
    vector<bool> inst(n, 0);
    int cnt = 0, sccid = 0;
    auto dfs = [&](auto self, int u) -> void {
        st.pb(u);
        inst[u] = true;
        dfn[u] = low[u] = ++cnt;
        for(int v : adj[u]){
            if(!inst[v] && dfn[v]) continue;
            if(!dfn[v]) self(self, v);
            chmin(low[u], low[v]);
        }
        if(low[u] == dfn[u]){
            while(st.back() != u){
                inst[st.back()] = false;
                scc[st.back()] = sccid;
                st.pop_back();
            }
            scc[u] = sccid;
            inst[u] = false;
            st.pop_back();
            sccid++;
        }
    };
    rep (i, 0, n) if (!dfn[i]) {
        dfs(dfs, i);
    }
    vector<int> mx(sccid, 0), smx(sccid, 0), ind(sccid, 0);
    vector<vector<int>> reb(sccid);
    rep (i, 0, n) {
        if (a[i] >= mx[scc[i]]) {
            smx[scc[i]] = mx[scc[i]];
            mx[scc[i]] = a[i];
        } else if (a[i] > smx[scc[i]]) {
            smx[scc[i]] = a[i];
        }
        for (int v : adj[i]) if (scc[v] != scc[i]) {
            reb[scc[v]].pb(scc[i]);
            ind[scc[i]]++;
        }
    }
    vector<int> dp(sccid, 0);
    queue<int> q;
    rep (i, 0, sccid) if (ind[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : reb[u]) {
            dp[v] = max({dp[v], mx[u], dp[u]});
            ind[v]--;
            if (ind[v] == 0) q.push(v);
        }
    }
    ll ans = 0;
    rep (i, 0, n) {
        if (smx[scc[i]] == 0) {
            ans += dp[scc[i]];
        } else {
            if (a[i] == mx[scc[i]]) ans += max(dp[scc[i]], smx[scc[i]]);
            else ans += max(dp[scc[i]], mx[scc[i]]);
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}