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

// mt19937_ll rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

const ull mask = chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
    x ^= mask;
    x ^= x << 6;
    x ^= x >> 10;
    x ^= x << 20;
    x ^= x >> 1;
    x ^= mask;
    return x;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n + 1), adj2(n + 1);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        adj2[a].pb(b);
        adj2[b].pb(a);
    }
    vector<ull> hash(n + 1), hash2(n + 1);
    auto dfs = [&](auto self, int u, int pa) -> void {
        hash[u] = 1;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            hash[u] += shift(hash[v]);
        }
    };
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        hash2[u] = 1;
        for (int v : adj2[u]) {
            if (v == pa) continue;
            self(self, v, u);
            hash2[u] += shift(hash2[v]);
        }
    };
    dfs(dfs, 1, 0);
    dfs2(dfs2, 1, 0);
    cout << (hash[1] == hash2[1] ? "YES\n" : "NO\n");
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}