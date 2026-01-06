#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 1e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct info {
    int l, r, mn = IINF;
    void pull();
} tree[MAXN << 6];

void info::pull() {
    mn = min(tree[l].mn, tree[r].mn);
}

int T[MAXN];

int newnode() {
    static int id = 0;
    return ++id;
}

int mod(int p, int l, int r, int id, int val) {
    int root = newnode();
    tree[root] = tree[p];
    if (l == r) {
        tree[root].mn = min(tree[root].mn, val);
        return root;
    }
    int mid = l + r >> 1;
    if (id <= mid) tree[root].l = mod(tree[p].l, l, mid, id, val);
    else tree[root].r = mod(tree[p].r, mid + 1, r, id, val);
    tree[root].pull();
    return root;
}

int merge(int p, int p2, int l, int r) {
    if (!p || !p2) return p ? p : p2;
    int root = newnode();
    if (l == r) {
        tree[root].mn = min(tree[p].mn, tree[p2].mn);
        return root;
    }
    int mid = l + r >> 1;
    tree[root].l = merge(tree[p].l, tree[p2].l, l, mid);
    tree[root].r = merge(tree[p].r, tree[p2].r, mid + 1, r);
    tree[root].pull();
    return root;
}

int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[p].mn;
    int mid = l + r >> 1;
    int res = IINF;
    if (ql <= mid) res = min(res, query(tree[p].l, l, mid, ql, qr));
    if (qr > mid) res = min(res, query(tree[p].r, mid + 1, r, ql, qr));
    return res;
}

void solve() {
    int n, r; cin >> n >> r;
    r--;
    vector<int> w(n);
    rep (i, 0, n) cin >> w[i];
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dep(n);
    auto dfs = [&](auto self, int u, int pa) -> void {
        T[u] = mod(T[u], 0, n - 1, dep[u], w[u]);
        for (int v : adj[u]) {
            if (v == pa) continue;
            dep[v] = dep[u] + 1;
            self(self, v, u);
            T[u] = merge(T[u], T[v], 0, n - 1);
        }
    };
    dfs(dfs, r, -1);
    int q; cin >> q;
    int la = 0;
    while (q--) {
        int p, q; cin >> p >> q;
        p = (p + la) % n, q = (q + la) % n;
        la = query(T[p], 0, n - 1, dep[p], min(n - 1, dep[p] + q));
        cout << la << '\n';
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