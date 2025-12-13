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

struct UnionFind {
    vector<int> sz, val;
    vector<ll> pre;
    vector<multiset<ll>> slo;
    UnionFind(int n) : sz(n, -1), val(n, 0), pre(n, 0), slo(n) {
        rep (i, 0, n) {
            slo[i].insert(0);
            slo[i].insert(0);
        }
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b, ll w) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        ll v = *slo[a].rbegin();
        slo[a].extract(v);
        slo[a].insert(v + w * val[a] - pre[a]);
        v = *slo[b].rbegin();
        slo[b].extract(v);
        slo[b].insert(v + w * val[b] - pre[b]);
        for (ll x : slo[b]) slo[a].insert(x);
        slo[b].clear();
        // vector<ll> g(-sz[a] + -sz[b] + 1, LINF);
        // rep (i, 0, -sz[a] + 1) rep (j, 0, -sz[b] + 1) {
        //     if (i == 0 && j == 0) g[0] = 0;
        //     else if (i == 0) chmin(g[i + j], dp[a][i] + dp[b][j] + w * val[a]);
        //     else if (j == 0) chmin(g[i + j], dp[a][i] + dp[b][j] + w * val[b]);
        //     else chmin(g[i + j], dp[a][i] + dp[b][j]);
        // }
        // swap(dp[a], g);
        val[a] += val[b];
        pre[a] = w * val[a];
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, m, p; cin >> n >> m >> p;
    UnionFind dsu(n);
    rep (i, 0, p) {
        int s; cin >> s;
        s--;
        dsu.val[s] = 1;
    }
    vector<array<int, 3>> edge;
    rep (i, 0, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        edge.push_back({c, a, b});
    }
    sort(all(edge));
    for (const auto &[w, u, v] : edge) {
        dsu.Union(u, v, w);
    }
    int rt = dsu.find(0);
    // rep (i, 1, n + 1) cout << dsu.dp[rt][i] << " \n" [i == n];
    ll val = dsu.pre[rt];
    auto it = dsu.slo[rt].rbegin();
    for (int i = 0; i < n; i++, it = next(it)) {
        val -= *it;
        cout << val << " \n" [i == n - 1];
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}