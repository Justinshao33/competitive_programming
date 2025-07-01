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

vector<int> pa, dsu_bcc, dsu_cc, cc_sz;
int bridge, tag;
vector<int> vis;

void init(int n) {
    pa.resize(n);
    dsu_bcc.resize(n);
    dsu_cc.resize(n);
    cc_sz.resize(n);
    bridge = tag = 0;
    vis.assign(n, 0);
    rep (i, 0, n) {
        dsu_bcc[i] = dsu_cc[i] = i;
        cc_sz[i] = 1;
        pa[i] = -1;
    }
}

int find_bcc(int x) {
    if (x == -1)
        return -1;
    return dsu_bcc[x] == x ? x : dsu_bcc[x] = find_bcc(dsu_bcc[x]);
}

int find_cc(int x) {
    x = find_bcc(x);
    return dsu_cc[x] == x ? x : dsu_cc[x] = find_cc(dsu_cc[x]);
}

void make_root(int x) {
    int root = x, son = -1;
    while (x != -1) {
        int p = find_bcc(pa[x]);
        pa[x] = son;
        dsu_cc[x] = root;
        son = x;
        x = p;
    }
    cc_sz[root] = cc_sz[son];
}

void compress(int a, int b) {
    tag++;
    vector<int> path_a, path_b;
    int lca = -1;
    while (lca == -1) {
        if (a != -1) {
            a = find_bcc(a);
            path_a.pb(a);
            if (vis[a] == tag) {
                lca = a;
                break;
            }
            vis[a] = tag;
            a = pa[a];
        }
        if (b != -1) {
            b = find_bcc(b);
            path_b.pb(b);
            if (vis[b] == tag) {
                lca = b;
                break;
            }
            vis[b] = tag;
            b = pa[b];
        }
    }
    for (int v : path_a) {
        dsu_bcc[v] = lca;
        if (v == lca) break;
        bridge--;
    }
    for (int v : path_b) {
        dsu_bcc[v] = lca;
        if (v == lca) break;
        bridge--;
    }
}

void add_edge(int a, int b) {
    a = find_bcc(a), b = find_bcc(b);
    if (a == b) return;
    int ca = find_cc(a), cb = find_cc(b);
    if (ca != cb) {
        bridge++;
        if (cc_sz[ca] > cc_sz[cb]) {
            swap(a, b);
            swap(ca, cb);
        }
        make_root(a);
        pa[a] = dsu_cc[a] = b;
        cc_sz[cb] += cc_sz[a];
    } else {
        compress(a, b);
    }
}

template<typename T>inline void read(T &x) {
    x = 0;
    static int p; p = 1;
    static char c; c = getchar();
    while (!isdigit(c)) { if (c == '-') p = -1; c = getchar();}
    while (isdigit(c)) { x = (x << 1) + (x << 3) + (c - 48); c = getchar();}
    x *= p;
}

void solve() {
    int n, m; read(n), read(m);
    init(n);
    int a, b;
    rep (i, 0, m) {
        read(a), read(b);
        a--, b--;
        add_edge(a, b);
        cout << bridge << '\n';
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