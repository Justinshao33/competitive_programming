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
    int n; cin >> n;
    vector<int> p(n), pp(n);
    rep (i, 0, n) cin >> p[i], p[i]--;
    UnionFind dsu(n);
    int m; cin >> m;
    vector<vector<pii>> adj(n);
    vector<pii> edge;
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        a--, b--;
        edge.pb({a, b});
        adj[a].pb({b, i});
        adj[b].pb({a, i});
        dsu.Union(a, b);
    }
    rep (i, 0, n) {
        if (!dsu.same(i, p[i])) {
            cout << -1 << '\n';
            return;
        }
    }
    if (is_sorted(all(p))) {
        cout << 0 << '\n';
        return;
    }
    vector<int> ans;
    rep (i, 0, n) {
        if (i == dsu.find(i)) {
            vector<int> comp;
            rep (j, 0, n) if (dsu.find(j) == i) {
                comp.pb(j);
            }
            vector<int> dep(n, IINF);
            vector<bool> ok(m, 0);
            auto dfs = [&](auto self, int u, int pa) -> void {
                for (auto [v, id] : adj[u]) {
                    if (v == pa || dep[v] != IINF) continue;
                    dep[v] = dep[u] + 1;
                    ok[id] = 1;
                    self(self, v, u);
                }
            };
            dep[i] = 0;
            dfs(dfs, i, -1);
            sort(all(comp), [&](int a, int b) {
                return dep[a] > dep[b];
            });
            rep (d, 0, comp.size()) {
                int from, to = comp[d];
                rep (j, 0, n) {
                    if (p[j] == comp[d]) {
                        from = j;
                        break;
                    }
                }
                if (from == to) continue;
                vector<int> ope(n, -1);
                auto dfs2 = [&](auto self, int u, int pa) -> void {
                    for (auto [v, id] : adj[u]) {
                        if (v == pa || !ok[id]) continue;
                        ope[v] = id;
                        self(self, v, u);
                    }
                };
                dfs2(dfs2, to, -1);
                while (from != to) {
                    ans.pb(ope[from]);
                    auto [a, b] = edge[ope[from]];
                    int nxt = from ^ a ^ b;
                    swap(p[from], p[nxt]);
                    from = nxt;
                }
                assert(from == to);
            }
        }
    }
    assert(is_sorted(all(p)));
    cout << ans.size() << '\n';
    for (int x : ans) cout << x + 1 << ' ';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}