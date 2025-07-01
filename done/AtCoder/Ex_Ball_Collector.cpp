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

int pa[MAXN], sz[MAXN], edge[MAXN];
vector<tuple<int, int, int, int, int, int, int>> st;
int ans[MAXN], cur;

int find(int x) {
    while (pa[x] != x) x = pa[x];
    return x;
}
 
bool Union(int a, int b) {
    a = find(a), b = find(b);
    st.pb({pa[a], sz[a], pa[b], sz[b], edge[a], edge[b], cur});
    if (a == b) {
        cur -= min(sz[a], edge[a]);
        edge[a]++;
        cur += min(sz[a], edge[a]);
        return false;
    }
    if (sz[a] < sz[b]) swap(a, b);
    cur -= min(sz[a], edge[a]);
    cur -= min(sz[b], edge[b]);
    pa[b] = a;
    sz[a] += sz[b];
    edge[a] += edge[b] + 1;
    cur += min(sz[a], edge[a]);
    return true;
}
 
bool same(int a, int b) {
    return find(a) == find(b);
}
 
void undo() {
    auto [a, sa, b, sb, ea, eb, pre] = st.back();
    st.pop_back();
    pa[a] = a;
    pa[b] = b;
    sz[a] = sa;
    sz[b] = sb;
    edge[a] = ea;
    edge[b] = eb;
    cur = pre;
}

void solve() {
    int n; cin >> n;
    rep (i, 0, n) {
        pa[i] = i;
        sz[i] = 1;
    }
    vector<int> a(n), b(n);
    rep (i, 0, n) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
    }
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    auto dfs = [&](auto self, int u, int pa) -> void {
        Union(a[u], b[u]);
        ans[u] = cur;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u); 
        }
        undo();
    };
    dfs(dfs, 0, -1);
    rep (i, 1, n) cout << ans[i] << " \n" [i == n - 1];
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}