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

    void mod(int x, ll val){
        while(x <= BIT.size()){
            BIT[x] += val;
            x += x & -x;
        }
    }

    ll query(int x){
        ll res = 0;
        while(x){
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    FenwickTree bit(n), bit2(n);
    vector<int> in(n + 1), out(n + 1), p(n + 1);
    int tid = 0; 
    ll tot = 0;
    auto dfs = [&](auto self, int u, int pa) -> void {
        p[u] = pa;
        in[u] = ++tid;
        bit.mod(u, 1);
        tot += bit.query(n) - bit.query(u);
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
        }
        bit.mod(u, -1);
        out[u] = tid;
    };
    dfs(dfs, 1, 0);
    // rep (i, 1, n + 1) cout << in[i] << ' ' << out[i] << '\n';
    vector<ll> sub(n + 1, 0); 
    rep (u, 1, n + 1) {
        // cout << in[u] << ' ' << out[u] << '\n';
        sub[u] += bit2.query(n) - (bit2.query(out[u]) - bit2.query(in[u] - 1));
        bit2.mod(in[u], 1);
        for (int v : adj[u]) {
            if (v == p[u]) continue;
            sub[v] -= bit2.query(out[v]) - bit2.query(in[v] - 1);
            // cout << v << ' ' << sub[v] << '\n';
        }
    }
    // rep (i, 1, n + 1) cout << sub[i] << '\n';
    vector<ll> ans(n + 1, 0);
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        ans[u] = tot;
        for (int v : adj[u]) {
            if (v == pa) continue;
            tot += sub[v];
            self(self, v, u);
            tot -= sub[v];
        }
    };
    dfs2(dfs2, 1, 0);
    rep (i, 1, n + 1) cout << ans[i] << " \n" [i == n];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}