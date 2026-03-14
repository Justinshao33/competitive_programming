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

void solve() {
    int n; cin >> n;
    vector tr(n * 2 * 30, vector<int>(2));
    vector<int> a(n * 2 * 30), b(n * 2 * 30);
    int id = 0;
    auto ins = [&](int x, vector<int> &c) -> void {
        int cur = 0;
        bool f = 0;
        for (int i = 29; i >= 0; --i) {
            int b = x >> i & 1;
            if (!b && !f) continue;
            f = 1;
            if (!tr[cur][b]) tr[cur][b] = ++id;
            cur = tr[cur][b];
        }
        c[cur]++;
    };
    rep (i, 0, n) {
        int x; cin >> x;
        ins(x, a);
    }
    rep (i, 0, n) {
        int x; cin >> x;
        ins(x, b);
    }
    int ans = 0;
    id++;
    vector<vector<int>> da(id), db(id);
    auto merge = [&](int x, int y) -> void {
        if (ssize(da[x]) < ssize(da[y])) swap(da[x], da[y]);
        for (int z : da[y]) da[x].push_back(z);
        if (ssize(db[x]) < ssize(db[y])) swap(db[x], db[y]);
        for (int z : db[y]) db[x].push_back(z);
    };
    // debug(n * 2 * 30);
    auto dfs = [&](auto self, int u, int d) -> void {
        // debug(u);
        rep (i, 0, a[u]) da[u].push_back(d);
        rep (i, 0, b[u]) db[u].push_back(d);
        if (tr[u][0]) {
            self(self, tr[u][0], d + 1);
            a[u] += a[tr[u][0]];
            b[u] += b[tr[u][0]];
            merge(u, tr[u][0]);
        }
        if (tr[u][1]) {
            self(self, tr[u][1], d + 1);
            if (b[tr[u][1]] > 0) {
                cout << -1 << '\n';
                exit(0);
            }
            a[u] += a[tr[u][1]];
            b[u] += b[tr[u][1]];
            merge(u, tr[u][1]);
        }
        while (!da[u].empty() && !db[u].empty()) {
            ans += da[u].back() + db[u].back() - 2 * d;
            a[u]--, b[u]--;
            // debug(d, da[u].back(), db[u].back());
            da[u].pop_back();
            db[u].pop_back();
        }
    };
    dfs(dfs, 0, 0);
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}