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
    vector<pii> edge(m);
    for (auto &[a, b] : edge) read(a), read(b);
    vector<bool> ch(m, 0);
    vector<int> tree, other;
    rep (i, 0, n - 1) {
        int k; read(k);
        ch[k - 1] = 1;
    }
    rep (i, 0, m) {
        (ch[i] ? tree : other).pb(i);
    }
    sort(all(tree), [&](int a, int b) {
        return edge[a] < edge[b];
    });
    sort(all(other), [&](int a, int b) {
        return edge[a] < edge[b];
    });
    vector<vector<pii>> adj(n);
    int sz = tree.size();
    rep (i, 0, sz) {
        auto [a, b] = edge[tree[i]];
        a--, b--;
        adj[a].pb({b, i});
        adj[b].pb({a, i});
    }
    vector pa(n, vector<int>(20)), mx(n, vector<int>(20));
    vector<int> dep(n);
    auto dfs = [&](auto self, int u, int p) -> void {
        for (auto &[v, w] : adj[u]) {
            if (v == p) continue;
            pa[v][0] = u;
            mx[v][0] = w;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);
    rep (j, 1, 20) rep (i, 0, n) {
        pa[i][j] = pa[pa[i][j - 1]][j - 1];
        mx[i][j] = max(mx[i][j - 1], mx[pa[i][j - 1]][j - 1]);
    }
    auto get_mx = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b], res = 0;
        rep (i, 0, 20) if (d & (1 << i)) {
            chmax(res, mx[a][i]);
            a = pa[a][i];
        }
        if (a == b) return res;
        for (int i = 19; i >= 0; --i) {
            if (pa[a][i] != pa[b][i]) {
                res = max({res, mx[a][i], mx[b][i]});
                a = pa[a][i];
                b = pa[b][i];
            }
        }
        res = max({res, mx[a][0], mx[b][0]});
        return res;
    };
    vector<vector<int>> dic(sz);
    for (int x : other) {
        auto [a, b] = edge[x];
        a--, b--;
        int id = get_mx(a, b);
        dic[id].pb(x);
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    rep (i, 0, sz) {
        cout << edge[tree[i]].F << ' ' << edge[tree[i]].S << '\n';
        for (int x : dic[i]) {
            pq.push(edge[x]);
        }
        while (!pq.empty() && (i == sz - 1 || pq.top() < edge[tree[i + 1]])) {
            auto [a, b] = pq.top();
            pq.pop();
            cout << a << ' ' << b << '\n';
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