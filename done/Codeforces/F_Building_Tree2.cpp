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

vector<pii> edg[MAXN];
int pa[MAXN], sz[MAXN], ans, cc, pa2[MAXN], id[MAXN];
vector<array<int, 3>> st;

void init(int n) {
    ans = 0;
    st.clear();
    rep (i, 0, n) {
        pa[i] = i;
        sz[i] = 1;
        pa2[i] = i;
        id[i] = -1;
    }
}

int find2(int x) {
    return (x == pa2[x]) ? x : pa2[x] = find2(pa2[x]);
}
 
int find(int x) {
    while (pa[x] != x) x = pa[x];
    return x;
}
 
bool Union(int a, int b, int v) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b], pa[b] = a;
    st.pb({a, b, id[a]});
    if (id[a] >= 0 && id[b] >= 0) {
        int x = find2(id[a]), y = find2(id[b]);
        if (x != y) {
            cc--;
            ans += v;
            pa2[y] = x;
        }
    }
    id[a] = max(id[a], id[b]);
    return true;
}
 
bool same(int a, int b) {
    return find(a) == find(b);
}
 
void undo() {
    auto [a, b, c] = st.back();
    st.pop_back();
    pa[b] = b;
    sz[a] -= sz[b];
    id[a] = c;
}
 
void dfs(int l, int r) {
    if (cc == 1) return;
    if (l == r) return;
    int cnt = 0, mid = l + r >> 1;
    rep (i, mid + 1, r + 1) {
        for (const auto &[a, b] : edg[i]) cnt += Union(a, b, l);
    }
    dfs(l, mid);
    while (cnt--) undo();
    cnt = 0;
    rep (i, l, mid + 1) {
        for (const auto &[a, b] : edg[i]) cnt += Union(a, b, mid + 1);
    }
    dfs(mid + 1, r);
    while (cnt--) undo();
}

void solve() {
    int n, m, q; cin >> n >> m >> q;
    rep (i, 0, m + 1) edg[i].clear();
    init(n);
    rep (i, 0, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        edg[c].push_back({a, b});
    }
    rep (i, 0, q) {
        int c; cin >> c; c--;
        id[c] = c;
    }
    cc = 0;
    rep (i, 0, n) if (id[i] != -1) cc++;
    dfs(0, m);
    if (cc != 1) cout << -1 << '\n';
    else cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}