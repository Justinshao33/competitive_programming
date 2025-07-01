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
 
const int MAXN = 1e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

vector<pii> adj[MAXN];
ll ans[MAXN], cnt[MAXN], cdis[MAXN][20];
int sz[MAXN], fa[MAXN], cdep[MAXN];
int cen;
bool vis[MAXN];

void dfs_sz(int u, int pa) {
    sz[u] = 1;
    for (auto [v, w] : adj[u]) {
        if (v == pa || vis[v]) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}

void dfs_cen(int u, int pa, int root) {
    int mx = sz[root] - sz[u];
    for (auto [v, w] : adj[u]) {
        if (v == pa || vis[v]) continue;
        chmax(mx, sz[v]);
        dfs_cen(v, u, root);
    }
    if (mx <= sz[root] / 2) cen = u;
}

void dfs(int u, int pa, ll dis, int dep) {
    cdis[u][dep] = dis;
    for (auto [v, w] : adj[u]) {
        if (v == pa || vis[v]) continue;
        dfs(v, u, dis + w, dep);
    }
}

void cd(int u, int pa, int dep) {
    dfs_sz(u, -1);
    dfs_cen(u, -1, u);
    dfs(cen, -1, 0, dep);
    vis[cen] = 1;
    fa[cen] = pa;
    cdep[cen] = dep;
    int cur = cen;
    for (auto [v, w] : adj[cen]) {
        if (vis[v]) continue;
        cd(v, cur, dep + 1);
    }
}

void mod(int x) {
    int p = x;
    while (p != -1) {
        ans[p] += cdis[x][cdep[p]] - cdis[x][cdep[p] - 1];
        cnt[p]++;
        p = fa[p];
    }
}

ll query(int x) {
    ll res = 0;
    int p = x, presz = 0;;
    while (p != -1) {
        res += ans[p];
        res += cdis[x][cdep[p]] * (cnt[p] - presz);
        presz = cnt[p];
        p = fa[p];
    }
    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    rep (i, 0, n - 1) {
        int a, b, l; cin >> a >> b >> l;
        adj[a].pb({b, l});
        adj[b].pb({a, l});
    }
    cd(0, -1, 0);
    fill(vis, vis + n, 0);
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            if (!vis[x]) {
                mod(x);
                vis[x] = 1;
            }
        } else {
            cout << query(x) << '\n';
        }
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}