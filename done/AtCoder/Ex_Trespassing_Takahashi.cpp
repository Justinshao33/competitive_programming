#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<pll>> adj(n);
    vector<tuple<ll, int, int>> edge; 
    rep (i, 0, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
        edge.pb({c, a, b});
    }
    vector<ll> dis(n, LINF);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    rep (i, 0, k) {
        dis[i] = 0;
        pq.push({dis[i], i});
    }
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dis[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (chmin(dis[v], dis[u] + w)) {
                pq.push({dis[v], v});
            }
        }
    }
    for (auto &[c, a, b] : edge) {
        c = c + dis[a] + dis[b];
    }
    int q; cin >> q;
    vector<tuple<ll, int, int, int>> que(q);
    rep (i, 0, q) {
        auto &[t, x, y, id] = que[i];
        cin >> x >> y >> t;
        x--, y--;
        id = i;
    }
    sort(all(edge));
    sort(all(que));
    vector<bool> ans(q);
    UnionFind dsu(n);
    int ptr = 0;
    for (auto [t, x, y, id] : que) {
        while (ptr < m) {
            auto [c, a, b] = edge[ptr];
            if (c > t) break;
            dsu.Union(a, b);
            ptr++;
        }
        ans[id] = dsu.same(x, y);
    }
    rep (i, 0, q) cout << (ans[i] ? "Yes\n" : "No\n");
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}