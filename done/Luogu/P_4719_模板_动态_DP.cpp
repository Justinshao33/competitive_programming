#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

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
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct Mat {
    ll a[2][2];
    Mat() {
        memset(a, -LINF, sizeof a);
    }
    inline Mat operator*(const Mat &oth) const {
        Mat res;
        rep (i, 0, 2) rep (j, 0, 2) rep (k, 0, 2) {
            res.a[i][j] = max(res.a[i][j], a[i][k] + oth.a[k][j]);
        }
        return res;
    }
} tree[MAXN << 2];

int hson[MAXN], sz[MAXN], fa[MAXN], hd[MAXN], id[MAXN], le[MAXN], rid[MAXN];
int w[MAXN];
ll f[MAXN][2], g[MAXN][2];

void upd(Mat &M, int x) {
    M.a[0][0] = M.a[0][1] = g[x][0];
    M.a[1][0] = g[x][1];
    M.a[1][1] = -LINF;
}

void build(int pos, int l, int r) {
    if (l == r) {
        upd(tree[pos], rid[l]);
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    tree[pos] = tree[lpos] * tree[rpos];
};

void mod(int pos, int l, int r, int x, Mat &M) {
    if (l == r) {
        tree[pos] = M;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) mod(lpos, l, mid, x, M);
    else mod(rpos, mid + 1, r, x, M);
    tree[pos] = tree[lpos] * tree[rpos];
}
 
Mat query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos];
    int mid = l + r >> 1;
    if (qr <= mid) return query(lpos, l, mid, ql, qr);
    else if (ql > mid) return query(rpos, mid + 1, r, ql, qr);
    else return query(lpos, l, mid, ql, qr) * query(rpos, mid + 1, r, ql, qr);
}

void solve() {
    int n, q; cin >> n >> q;
    rep (i, 0, n) cin >> w[i];
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
         int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // g:=不看重兒子的可選f最大總和
    // g[u][0] = \sum max(f[v][0], f[v][1])
    // g[u][1] = \sum f[v][0] + w[u]
    // f:=最大權獨立集
    // f[u][0] = max(f[hs[u]][0], f[hs[u]][1]) + g[u][0]
    // f[u][1] = f[hs[u]][0] + g[u][1]
    // [g0, g0]
    // [g1, -inf]
    rep (i, 0, n) hson[i] = -1;
    auto dfs = [&](auto self, int u, int pa) -> void {
        sz[u] = 1;
        fa[u] = pa;
        for (int v : adj[u]) {
            if (v == pa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            if (hson[u] == -1 || sz[hson[u]] < sz[v]) hson[u] = v;
        }
    };
    
    int cnt = 0;
    auto HLD = [&](auto self, int u, int tp) -> void {
        id[u] = ++cnt;
        rid[id[u]] = u;
        hd[u] = tp;
        if (hson[u] != -1) {
            self(self, hson[u], tp);
            le[u] = le[hson[u]];
            f[u][0] = max(f[hson[u]][0], f[hson[u]][1]);
            f[u][1] = f[hson[u]][0];
        } else {
            le[u] = u;
            f[u][1] = g[u][1] = w[u];
            return;
        }
        g[u][1] = w[u];
        for (int v : adj[u]) {
            if (v == fa[u] || v == hson[u]) continue;
            self(self, v, v);
            g[u][0] += max(f[v][0], f[v][1]);
            g[u][1] += f[v][0];
        }
        f[u][0] += g[u][0];
        f[u][1] += g[u][1];
    };
    
    dfs(dfs, 0, -1);
    HLD(HLD, 0, 0);
    
    
    auto modify = [&](int x, ll v) -> void {
        g[x][1] += v - w[x];
        w[x] = v;
        Mat tr;
        upd(tr, x);
        while (true) {
            auto pre = query(1, 1, n, id[hd[x]], id[le[hd[x]]]);
            mod(1, 1, n, id[x], tr);
            auto nxt = query(1, 1, n, id[hd[x]], id[le[hd[x]]]);
            x = fa[hd[x]];
            if (x < 0) break;
            g[x][0] += max(nxt.a[0][0], nxt.a[1][0]) - max(pre.a[0][0], pre.a[1][0]);
            g[x][1] += nxt.a[0][0] - pre.a[0][0];
            upd(tr, x);
        }
    };

    build(1, 1, n);
    while (q--) {
        int x; ll y; cin >> x >> y;
        x--;
        modify(x, y);
        Mat ans = query(1, 1, n, id[0], id[le[0]]);
        cout << max(ans.a[0][0], ans.a[1][0]) << '\n';
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