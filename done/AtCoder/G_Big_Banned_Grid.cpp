#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
    vector<int> sz;
    vector<int> l, r, u, d;
    UnionFind(int n, vector<pii> &pt) : sz(n, -1), l(n), r(n), u(n), d(n) {
        rep (i, 0, n) {
            l[i] = r[i] = pt[i].fi;
            u[i] = d[i] = pt[i].se;
        }
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        chmin(l[a], l[b]);
        chmax(r[a], r[b]);
        chmin(u[a], u[b]);
        chmax(d[a], d[b]);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<pii> pt(k);
    map<pii, int> mp; 
    for (auto &[x, y] : pt) cin >> x >> y;
    rep (i, 0, k) mp[pt[i]] = i;
    UnionFind dsu(k, pt);
    rep (i, 0, k) {
        for (int dx : {-1, 0, 1}) for (int dy : {-1, 0, 1}) {
            int nx = pt[i].fi + dx, ny = pt[i].se + dy;
            if (mp.contains({nx, ny})) {
                dsu.Union(i, mp[{nx, ny}]);
            }
        }
    }
    rep (i, 0, k) if (i == dsu.find(i)) {
        if ((dsu.l[i] == 1 && dsu.r[i] == n) || (dsu.u[i] == 1 && dsu.d[i] == m) || 
            (dsu.l[i] == 1 && dsu.u[i] == 1) || (dsu.r[i] == n && dsu.d[i] == m)) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}