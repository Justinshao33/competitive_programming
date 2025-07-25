#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
    vector<int> sz, col, l, r;
    UnionFind(int n) : sz(n, -1), col(n), l(n), r(n) {
        iota(all(col), 0);
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
        l[a] = min(l[a], l[b]);
        r[a] = max(r[a], r[b]);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    UnionFind dsu(n);
    vector<int> cnt(n, 1);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, c; cin >> x >> c;
            x--, c--;
            cnt[dsu.col[dsu.find(x)]] -= dsu.size(x);
            dsu.col[dsu.find(x)] = c;
            cnt[dsu.col[dsu.find(x)]] += dsu.size(x);
            if (dsu.l[dsu.find(x)] && dsu.col[dsu.find(dsu.l[dsu.find(x)] - 1)] == dsu.col[dsu.find(x)]) dsu.Union(dsu.l[dsu.find(x)] - 1, x);
            if (dsu.r[dsu.find(x)] != n - 1 && dsu.col[dsu.find(x)] == dsu.col[dsu.find(dsu.r[dsu.find(x)] + 1)]) dsu.Union(x, dsu.r[dsu.find(x)] + 1);
        } else {
            int c; cin >> c;
            c--;
            cout << cnt[c] << '\n';
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