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

int tree[MAXN << 2], tag[MAXN << 2];

void pull(int pos) {
    tree[pos] = tree[lpos] + tree[rpos]; 
}

void build(int pos, int l, int r) {
    if (l == r) {
        tree[pos] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    pull(pos);
}

void upd(int pos, int l, int r) {
    tree[pos] = 0;
    tag[pos] = 1;
}

void push(int pos, int l, int r) {
    if (tag[pos]) {
        int mid = l + r >> 1;
        upd(lpos, l, mid);
        upd(rpos, mid + 1, r);
        tag[pos] = 0;
    }
}

void mod(int pos, int l, int r, int ml, int mr) {
    if (ml > mr) return;
    if (ml <= l && mr >= r) {
        upd(pos, l, r);
        return;
    }
    push(pos, l, r);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr);
    pull(pos);
}

int query(int pos, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && qr >= r) return tree[pos];
    push(pos, l, r);
    int mid = l + r >> 1;
    int res = 0;
    if (ql <= mid) res += query(lpos, l, mid, ql, qr);
    if (qr > mid) res += query(rpos, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n; cin >> n;
    build(1, 1, n);
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> in(n), out(n), fa(n), who(n + 1);
    int t = 0;
    auto dfs = [&](auto self, int u, int pa) -> void {
        t++;
        in[u] = t;
        who[t] = u;
        fa[u] = pa;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
        }
        out[u] = t;
    };
    dfs(dfs, 0, -1);
    // cout << in << out;
    rep (i, 0, n) {
        int b; cin >> b;
        if (b == 0) continue;
        b--;
        if (in[b] <= in[i] && out[b] >= out[i]) {
            mod(1, 1, n, in[i], out[i]);
        } else {
            mod(1, 1, n, 1, in[b] - 1);
            mod(1, 1, n, out[b] + 1, n);
        }
    }
    vector<int> ans;
    rep (i, 1, n) {
        if (adj[i].size() == 1 && query(1, 1, n, in[i], in[i]) == 1) {
            ans.pb(i);
        }
    }
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