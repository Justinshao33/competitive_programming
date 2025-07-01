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
    vector<int> sz;
    UnionFind(int n) : sz(n, -1) {}

    bool same(int a, int b) { return find(a) == find(b); }

    int size(int x) { return -sz[find(x)]; }

    int find(int x) { return sz[x] < 0 ? x : sz[x] = find(sz[x]); }

    bool Union(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<int> deg(n);
    UnionFind dsu(n);
    rep (i, 0, n) cin >> deg[i];
    if (accumulate(all(deg), 0LL) != 2 * (n - 1)) {
        cout << -1 << '\n';
        return;
    }
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        if (deg[a] == 0 || deg[b] == 0) {
            cout << -1 << '\n';
            return;
        }
        deg[a]--, deg[b]--;
        if (!dsu.Union(a, b)) {
            cout << -1 << '\n';
            return;
        }
    }
    vector<vector<int>> res(n);
    vector<int> sum(n, 0);
    priority_queue<pii> pq;
    rep (i, 0, n) if (deg[i]) {
        int p = dsu.find(i);
        sum[p] += deg[i];
        res[p].pb(i);
    }
    rep (i, 0, n) if (sum[i]) {
        pq.push({sum[i], i});
    }
    vector<pii> ans;
    rep (i, 0, n - m - 1) {
        if (pq.size() <= 1) {
            cout << -1 << '\n';
            return;
        }
        auto [_, a] = pq.top();
        pq.pop();
        auto [__, b] = pq.top();
        pq.pop();
        ans.pb({res[a].back(), res[b].back()});
        deg[res[a].back()]--;
        deg[res[b].back()]--;
        if (dsu.size(a) < dsu.size(b)) swap(a, b);
        if (deg[res[a].back()] == 0) res[a].pop_back();
        if (deg[res[b].back()] == 0) res[b].pop_back();
        sum[a] += sum[b] - 2;
        for (int v : res[b]) if (deg[v]) res[a].pb(v);
        res[b].clear();
        sum[b] = 0;
        dsu.Union(a, b);
        if (sum[a]) pq.push({sum[a], a});
    }
    if (!pq.empty()) {
        cout << -1 << '\n';
        return;
    }
    for (auto [u, v] : ans) {
        cout << u + 1 << ' ' << v + 1 << '\n';
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