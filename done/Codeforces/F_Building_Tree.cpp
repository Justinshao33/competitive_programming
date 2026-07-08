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
 
const int MAXN = 3e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

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
} col(0);

vector<pii> tree[MAXN << 2];
int pa[MAXN], sz[MAXN], ans, tag[MAXN], cc;
vector<pii> st;

void init(int n) {
    col = UnionFind(n);
    ans = 0;
    st.clear();
    rep (i, 0, n) {
        pa[i] = i;
        tag[i] = -1;
        sz[i] = 1;
    }
}

void mod(int pos, int l, int r, int ml, int mr, pii &x) {
    if (ml > mr) return;
    if (ml <= l && mr >= r) {
        tree[pos].pb(x);
        return;
    }
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, x);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, x);
}
 
int find(int x) {
    while (pa[x] != x) x = pa[x];
    return x;
}
 
bool Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b], pa[b] = a;
    st.pb({a, b});
    return true;
}
 
bool same(int a, int b) {
    return find(a) == find(b);
}
 
void undo() {
    auto [a, b] = st.back();
    st.pop_back();
    pa[b] = b;
    sz[a] -= sz[b];
}
 
void dfs(int pos, int l, int r, vector<int> &rc) {
    if (cc == 1) return;
    int cnt = 0;
    for (const auto &[a, b] : tree[pos]) {
        cnt += Union(a, b);
    }
    // erase ssize(tree[pos]) edge
    // -> cc <= ssize(tree[pos]) + 1
    // -> rc <= cc
    // -> tot <= mlogm + 2m - 1?
    vector<int> nxt;
    for (int x : rc) {
        int p = find(x);
        if (tag[p] == -1) {
            tag[p] = x;
            nxt.push_back(x);
        } else {
            if (col.Union(x, tag[p])) {
                cc--;
                ans += l;
            }
        }
    }
    for (int x : rc) tag[find(x)] = -1;
    if (l == r) {
        ;
    } else {
        int mid = l + r >> 1;
        dfs(lpos, l, mid, nxt);
        dfs(rpos, mid + 1, r, nxt);
    }
    rep (i, 0, cnt) undo();
}

void solve() {
    int n, m, q; cin >> n >> m >> q;
    rep (i, 0, (m + 1) << 2) tree[i].clear();
    init(n);
    UnionFind dsu(n);
    rep (i, 0, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        dsu.Union(a, b);
        pii edg = {a, b};
        mod(1, 0, m, 0, c - 1, edg);
        mod(1, 0, m, c + 1, m, edg);
    }
    vector<int> c(q);
    rep (i, 0, q) cin >> c[i], c[i]--;
    rep (i, 1, q) if (!dsu.same(c[0], c[i])) {
        cout << "-1\n";
        return;
    }
    auto rc = c;
    sort(all(rc));
    rc.erase(unique(all(rc)), rc.end());
    cc = ssize(rc);
    dfs(1, 0, m, rc);
    int rt = col.find(c[0]);
    rep (i, 0, q) if (col.find(c[i]) != rt) {
        cout << "-1\n";
        return;
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}