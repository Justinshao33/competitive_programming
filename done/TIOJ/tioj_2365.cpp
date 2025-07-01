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
        if (sz[a] > sz[b]) swap(a, b);
        sz[a] += sz[b]; sz[b] = a;
        return true;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n);
    UnionFind dsu(n);
    int cc = n;
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb({b, i});
        adj[b].pb({a, i});
        cc -= dsu.Union(a, b);
    }
    vector<vector<int>> aans(3);
    if (cc > 1) {
        int id = -1;
        rep (i, 0, n) if (dsu.find(i) == i && dsu.size(i) > 1) {
            id = i;
            break;
        }
        if (id == -1) {
            rep (i, 0, n) {
                aans[i % 3].pb(i);
            }
        } else {
            bool f = 1;
            rep (i, 0, n) {
                if (dsu.find(i) == id) {
                    if (f) {
                        aans[0].pb(i);
                        f = 0;
                    } else {
                        aans[1].pb(i);
                    }
                } else {
                    aans[2].pb(i);
                }
            }
        }
        rep (i, 0, 3) {
            cout << aans[i].size() << ' ';
            for (int k : aans[i]) cout << k + 1 << ' ';
            cout << '\n';
        }
    } else {
        vector<int> ans(n, 0);
        vector<bool> vis(n, 0), evis(m, 0);
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, i] : adj[u]) {
                if (vis[v]) continue;
                vis[v] = 1;
                q.push(v);
                evis[i] = 1;
            }
        }
        fill(all(vis), 0);
        int col = -1;
        rep (i, 0, n) if (!vis[i]) {
            col++;
            q.push(i);
            vis[i] = 1;
            while (!q.empty()) {
                int u = q.front();
                ans[u] = col % 3 + 1;
                q.pop();
                for (auto [v, id] : adj[u]) {
                    if (vis[v] || evis[id]) continue;
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        // assert(col >= 3);
        rep (i, 0, n) {
            if (ans[i] == 0) {
                col++;
                ans[i] = col;
            }
        }
        vector<bool> ch(3, 0);
        rep (i, 0, n) ch[ans[i] - 1] = 1;
        rep (i, 0, 3) if (ch[i] == 0) {
            cout << -1 << '\n';
            return;
        }
        rep (i, 0, n) {
            aans[ans[i] - 1].pb(i);
        }
        rep (i, 0, 3) {
            cout << aans[i].size() << ' ';
            for (int k : aans[i]) cout << k + 1 << ' ';
            cout << '\n';
        }
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