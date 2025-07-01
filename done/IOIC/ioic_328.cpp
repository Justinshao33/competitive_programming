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
    vector<int> sz, l, r, val;
    UnionFind(int n) : sz(n, -1), l(n), r(n), val(n) {
        iota(all(l), 0);
        iota(all(r), 0);
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        chmin(l[a], l[b]);
        chmax(r[a], r[b]);
        chmin(val[a], val[b]);
        return true;
    }

    ll calc(int x) {
        x = find(x);
        return 1LL * (r[x] - l[x] + 1) * val[x];
    }
};

template<typename T>inline void read(T &x) {
    x = 0;
    static int p; p = 1;
    static char c; c = getchar();
    while (!isdigit(c)) { if (c == '-') p = -1; c = getchar();}
    while (isdigit(c)) { x = (x << 1) + (x << 3) + (c - 48); c = getchar();}
    x *= p;
}

void solve() {
    int n; read(n);
    vector<int> a(n), p(n);
    rep (i, 0, n) read(a[i]);
    iota(all(p), 0);
    reverse(all(p));
    stable_sort(all(p), [&](int i, int j) {
        return a[i] > a[j];
    });
    UnionFind dsu(n);
    rep (i, 0, n) dsu.val[i] = a[i];
    ll ans = 0, cur = 0;
    vector<bool> vis(n, 0);
    rep (_i, 0, n) {
        int i = p[_i];
        vis[i] = true;
        cur += a[i];
        if (i && vis[i - 1]) {
            cur -= dsu.calc(i - 1);
            cur -= dsu.calc(i);
            dsu.Union(i - 1, i);
            cur += dsu.calc(i - 1);
        }
        if (i != n - 1 && vis[i + 1]) {
            cur -= dsu.calc(i);
            cur -= dsu.calc(i + 1);
            dsu.Union(i, i + 1);
            cur += dsu.calc(i + 1);
        }
        chmax(ans, cur);
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