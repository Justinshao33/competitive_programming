#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int pa[MAXN], sz[MAXN], ans[MAXN], W[MAXN];
vector<int> adj[MAXN];
array<int, 4> que[MAXN];
vector<array<int, 3>> st;
int K, cnt;

int get(int x) {
    x %= K;
    if (x < 0) x += K;
    return x;
}

void init(int n) {
    rep (i, 0, n) {
        pa[i] = i;
        sz[i] = 1;
    }
}
 
pii find(int x) {
    int res = 0;
    while (pa[x] != x) {
        res += W[x];
        x = pa[x];
    }
    return {x, res};
}
 
bool Union(int a, int b, int w) {
    auto [ra, wa] = find(a);
    auto [rb, wb] = find(b);
    if (ra == rb) return get(wb - wa) == w;
    cnt++;
    int ww = w - wb + wa;
    if (sz[ra] < sz[rb]) {
        swap(ra, rb);
        ww = -ww;
    }
    st.push_back({ra, rb, W[rb]});
    pa[rb] = ra;
    sz[ra] += sz[rb];
    W[rb] = get(ww);
    return true;
}
 
bool same(int a, int b) {
    return find(a).fi == find(b).fi;
}
 
void undo() {
    auto [a, b, pw] = st.back();
    st.pop_back();
    pa[b] = b;
    sz[a] -= sz[b];
    W[b] = pw;
}
 
void dfs(int u) {
    int pc = cnt;
    if (u != 0) {
        auto [t, l, r, x] = que[u];
        if (t == 0) {
            if (Union(l - 1, r, x)) ans[u] = -1;
            else ans[u] = -2;
        } else {
            if (!same(l - 1, r)) ans[u] = -3;
            else ans[u] = get(find(r).se - find(l - 1).se);
        }
    }
    for (int v : adj[u]) {
        dfs(v);
    }
    while (cnt > pc) {
        undo();
        cnt--;
    }
}

void solve() {
    int n, q; cin >> n >> K >> q;
    init(n + 1);
    rep (i, 1, q + 1) {
        int t, b, l, r; cin >> t >> b >> l >> r;
        adj[b].push_back(i);
        if (t == 0) {
            int x; cin >> x;
            que[i] = {t, l, r, x};
        } else {
            que[i] = {t, l, r, -1};
        }
    }
    dfs(0);
    rep (i, 1, q + 1) {
        if (ans[i] == -1) cout << "YES\n";
        else if (ans[i] == -2) cout << "NO\n";
        else if (ans[i] == -3) cout << "UNKNOWN\n";
        else cout << ans[i] << '\n';
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