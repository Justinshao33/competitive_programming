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

struct UnionFind {
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x
 
const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in(), q = in();
    UnionFind dsu(n);
    vector<vector<int>> que(q + 1), wt(n, vector<int>(20)), lift(n, vector<int>(20));
    vector<vector<pii>> adj(n);
    vector<int> dep(n, 0);
    rep (i, 1, q + 1) {
        int t = in();
        if (t == 1) {
            int a = in(), b = in();
            a--, b--;
            if (dsu.Union(a, b)) {
                adj[a].pb({b, i});
                adj[b].pb({a, i});
            }
        } else {
            int k = in();
            rep (j, 0, k) {
                int x = in();
                x--;
                que[i].pb(x);
            }
        }
    }
    auto dfs = [&](auto self, int u, int pa) -> void {
        for(auto [v, w] : adj[u]) {
            if (v == pa) continue;
            dep[v] = dep[u] + 1;
            wt[v][0] = w;
            lift[v][0] = u;
            self(self, v, u);
        }
    };
    rep(i, 0, n) if(!dep[i]) {
        dep[i] = 1;
        dfs(dfs, i, -1);
    }
    rep(j, 1, 20) rep(i, 0, n) {
        lift[i][j] = lift[lift[i][j - 1]][j - 1];
        wt[i][j] = max(wt[i][j - 1], wt[lift[i][j - 1]][j - 1]);
    }
    auto lca = [&](int a, int b) -> pii {
        int ret = 0;
        if(dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        rep(i, 0, 20) if(d & (1 << i)){
            ret = max(ret, wt[a][i]);
            a = lift[a][i];
        }
        if(a == b) return {a, ret}; 
        for(int i = 19; i >= 0; --i){
            if(lift[a][i] != lift[b][i]){
                ret = max(ret, max(wt[a][i], wt[b][i]));
                a = lift[a][i];
                b = lift[b][i];
            }
        }
        ret = max(ret, max(wt[a][0], wt[b][0]));
        return {lift[a][0], ret};
    };
    rep (i, 1, q + 1) if (!que[i].empty()) {
        int p = que[i][0], ans = 0;
        for (int x : que[i]) {
            if (dsu.find(x) != dsu.find(p)) {
                ans = IINF;
                break;
            }
            pii info = lca(x, p);
            p = info.F;
            chmax(ans, info.S);
        }
        if (ans > i) cout << -1 << '\n';
        else cout << ans << '\n';
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