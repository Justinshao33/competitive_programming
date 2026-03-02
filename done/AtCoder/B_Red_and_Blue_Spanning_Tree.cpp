#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

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

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edge;
    map<array<int, 3>, int> id;
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        char c; cin >> c;
        edge.push_back({a, b, c == 'R'});
        id[{a, b, c == 'R'}] = id[{b, a, c == 'R'}] = i;
    }
    string s; cin >> s;
    vector<array<int, 3>> tedge;
    UnionFind dsu(n);
    vector<int> ok(n), used;
    for (const auto &[a, b, c] : edge) {
        int val = 2 - (c == (s[a] == 'R')) - (c == (s[b] == 'R'));
        if (val == 0) {
            if (dsu.Union(a, b)) {
                ok[a] = ok[b] = 1;
                used.push_back(id[{a, b, c}]);
            }
        }
    }
    vector<vector<pii>> adj(n);
    for (const auto &[a, b, c] : edge) {
        if (ok[a] && ok[b]) continue;
        if ((s[b] == 'R') == c) adj[a].push_back({b, c});
        if ((s[a] == 'R') == c) adj[b].push_back({a, c});
    }
    queue<int> q;
    rep (i, 0, n) if (ok[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, c] : adj[u]) {
            if (ok[v]) continue;
            if (dsu.Union(u, v)) {
                ok[v] = 1;
                q.push(v);
                used.push_back(id[{u, v, c}]);
            }
        }
    }
    for (const auto &[a, b, c] : edge) {
        if (dsu.Union(a, b)) {
            used.push_back(id[{a, b, c}]);
        }
    }
    if (accumulate(all(ok), 0) != n) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int x : used) cout << x + 1 << ' ';
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}