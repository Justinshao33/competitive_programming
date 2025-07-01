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

struct FenwickTree{
    vector<ll> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    void mod(int x, ll val) {
        while(x < BIT.size()){
            BIT[x] += val;
            x += x & -x;
        }
    }

    ll query(int x) {
        ll res = 0;
        while (x) {
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }

    ll rquery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<vector<int>> adj(n);
    vector<int> dep(n), in(n), out(n);
    vector pa(n, vector<int>(20));
    rep (i, 0, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int t = 0;
    auto dfs = [&](auto self, int u, int p) -> void {
        in[u] = ++t;
        for (int v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            pa[v][0] = u;
            self(self, v, u);
        }
        out[u] = t;
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) pa[i][j] = pa[pa[i][j - 1]][j - 1];
    FenwickTree bit(n + 1);
    rep (i, 0, n) {
        bit.mod(in[i], a[i]);
        bit.mod(out[i] + 1, -a[i]);
    }
    auto lca = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        rep (i, 0, 20) if (d & (1 << i)) a = pa[a][i];
        if(a == b) return a;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        return pa[a][0];
    };
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 0) {
            bit.mod(in[l], r);
            bit.mod(out[l] + 1, -r);
            a[l] += r;
        } else {
            int p = lca(l, r);
            cout << bit.query(in[l]) + bit.query(in[r]) - bit.query(in[p]) * 2 + a[p] << '\n';
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