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

pll tree[MAXN << 2];
ll tag[MAXN << 2], dep[MAXN], who[MAXN];

void upd(int pos, ll val) {
    tree[pos].F += val;
    tag[pos] += val;
}

void push(int pos) {
    if (tag[pos]) {
        upd(lpos, tag[pos]);
        upd(rpos, tag[pos]);
        tag[pos] = 0;
    }
}

void pull(int pos) {
    tree[pos] = max(tree[lpos], tree[rpos]); 
}

void build(int pos, int l, int r) {
    if (l == r) {
        tree[pos] = {dep[who[l]], who[l]};
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    pull(pos);
}

void mod(int pos, int l, int r, int ml, int mr, ll val) {
    if (ml <= l && mr >= r) {
        upd(pos, val);
        return;
    }
    push(pos);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    pull(pos);
}

void solve() {
    int n; cin >> n;
    vector<vector<pii>> adj(n);
    vector<pii> fa(n);
    vector<int> in(n), out(n);
    int cnt = 0;
    rep (i, 0, n - 1) {
        int a, b, l; cin >> a >> b >> l;
        a--, b--;
        adj[a].pb({b, l});
        adj[b].pb({a, l});
    }
    auto dfs = [&](auto self, int u, int pa) -> void {
        in[u] = ++cnt;
        who[in[u]] = u;
        for (auto [v, l] : adj[u]) {
            if (v == pa) continue;
            fa[v] = {u, l};
            dep[v] = dep[u] + l;
            self(self, v, u);
        }
        out[u] = cnt;
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);
    // rep (i, 0, n) cout << in[i] << ' ' << out[i] << '\n'; 
    build(1, 1, n);
    vector<bool> vis(n, 0);
    vis[0] = 1;
    ll ans = 0;
    rep (i, 0, n) {
        auto [val, id] = tree[1];
        ans += val;
        while (!vis[id]) {
            vis[id] = 1;
            auto [nxt, l] = fa[id];
            mod(1, 1, n, in[id], out[id], -l);
            id = nxt;
        }
        cout << ans * 2 << '\n';
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