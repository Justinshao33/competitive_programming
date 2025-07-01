#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct SparseTable{
    vector<vector<int>> sp;
    SparseTable(vector<int> &a) {
        int n = a.size();
        sp.resize(n, vector<int>(__lg(n) + 1));
        for (int i = n - 1; i >= 0; i--) {
            sp[i][0] = a[i];
            for (int j = 1; i + (1 << j) <= n; j++) {
                sp[i][j] = max(sp[i][j - 1], sp[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    auto query(int l, int r) { // [l, r)
        int k = __lg(r - l);
        return max(sp[l][k], sp[r - (1 << k)][k]);
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int su, sv; cin >> su >> sv;
    assert(su == sv);
    su--;
    auto dfs = [&](auto self, int u, int pa, vector<int> &dis, vector<int> &mxd) -> void {
        mxd[u] = 1;
        for (int v : adj[u]) {
            if (v == pa) continue;
            dis[v] = dis[u] + 1;
            self(self, v, u, dis, mxd);
            chmax(mxd[u], mxd[v] + 1);
        }
    };
    vector<int> mxd(n, 0), mxd2(n, 0);
    vector<int> dis(n), dis2(n);
    dis[0] = dis2[su] = 0;
    dfs(dfs, 0, -1, dis, mxd);
    dfs(dfs, su, -1, dis2, mxd2);
    vector<int> a, b;
    for (int cur = su;;) {
        int mx = 0;
        for (int v : adj[cur]) if (dis[v] != dis[cur] - 1 && dis2[v] != dis2[cur] - 1) {
            chmax(mx, mxd[v]);
        }
        a.pb(dis[cur] + mx);
        b.pb(dis2[cur] + mx);
        if (cur == 0) break;
        for (int v : adj[cur]) if (dis[v] == dis[cur] - 1) {
            cur = v;
            break;
        }
    }
    debug(mxd);
    int m = ssize(a);
    assert(m > 1);
    int l = 0, r = m - 1, f = 1;
    SparseTable A(a), B(b);
    while (true) {
        if (l + 1 == r) {
            f = a[r] > b[l];
            break;
        }
        if (a[r] > B.query(l, r)) {
            f = 1;
            break;
        }
        r--;
        if (l + 1 == r) {
            f = b[l] < a[r];
            break;
        }
        if (b[l] >= A.query(l + 1, r + 1)) {
            f = 0;
            break;
        }
        l++;
    }
    cout << (f ? "Alice\n" : "Bob\n");
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}