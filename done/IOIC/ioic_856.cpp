// #pragma GCC optimize("O3,unroll-loops")
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
    vector<int> sz;
    vector<set<int>> ok;
    UnionFind(int n) : sz(n, -1), ok(n) {}

    bool same(int a, int b) { 
        a = find(a);
        return find(a) == find(b) || ok[a].find(b) != ok[a].end();
    }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (ok[a].size() < ok[b].size()) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        for (int x : ok[b]) ok[a].insert(x);
        ok[b].clear();
        return true;
    }
};

void solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<array<int, 3>> edge(m);
    for (auto &[u, v, w] : edge) {
        cin >> u >> v >> w;
        u--, v--;
    }
    vector<vector<int>> tic(n);
    int tot = 0;
    rep (i, 0, n) {
        int k; cin >> k;
        tot += k;
        rep (j, 0, k) {
            int a; cin >> a;
            tic[i].pb(a);
        }
    } 
    UnionFind dsu(n + m * 2 + tot);
    rep (i, 0, n) dsu.ok[i].insert(i);
    int id = n;
    map<pii, int> aru, nai;
    rep (i, 0, n) for (int c : tic[i]) {
        assert(aru.find({i, c}) == aru.end());
        aru[{i, c}] = id;
        dsu.Union(i, id);
        id++;
    }
    for (auto [u, v, w] : edge) {
        int l, r;
        if (aru.find({u, w}) != aru.end()) {
            l = aru[{u, w}];
        } else {
            if (nai.find({u, w}) == nai.end()) {
                nai[{u, w}] = id++;
                dsu.ok[nai[{u, w}]].insert(u);
            }
            l = nai[{u, w}];
        }
        if (aru.find({v, w}) != aru.end()) {
            r = aru[{v, w}];
        } else {
            if (nai.find({v, w}) == nai.end()) {
                nai[{v, w}] = id++;
                dsu.ok[nai[{v, w}]].insert(v);
            }
            r = nai[{v, w}];
        }
        dsu.Union(l, r);
    }
    while (q--) {
        int s, t, l; cin >> s >> t >> l;
        s--, t--;
        bool f = s == t;
        if (nai.find({s, l}) != nai.end()) f = dsu.same(nai[{s, l}], t);
        else if (aru.find({s, l}) != aru.end()) f = dsu.same(s, t);
        if (f) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
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