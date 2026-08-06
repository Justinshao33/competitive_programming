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
    vector<vector<int>> adj(n);
    rep (i, 0, n - 1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> L(n, -IINF), R(n, IINF);
    int q; cin >> q;
    int rt = 0;
    while (q--) {
        int v, p; cin >> v >> p;
        v--;
        rt = v;
        L[v] = R[v] = p;
    }
    auto dfs = [&](auto self, int u, int pa) -> void {
        for (int v : adj[u]) {
            if (v == pa) continue;
            chmax(L[v], L[u] - 1);
            chmin(R[v], R[u] + 1);
            self(self, v, u);
            chmax(L[u], L[v] - 1);
            chmin(R[u], R[v] + 1);
        }
    };
    dfs(dfs, rt, -1);
    rep (i, 0, n) if (L[i] > R[i]) {
        cout << "No\n";
        return;
    }
    bool f = 1;
    auto dfs2 = [&](auto self, int u, int pa) -> void {
        for (int v : adj[u]) {
            if (v == pa) continue;
            bool f2 = 0;
            for (int x : {L[u] - 1, L[u] + 1}) {
                if (L[v] <= x && x <= R[v]) {
                    L[v] = R[v] = x;
                    f2 = 1;
                }
            }
            if (!f2) f = 0;
            self(self, v, u);
        }
    };
    dfs2(dfs2, rt, -1);
    if (f) {
        cout << "Yes\n";
        rep (i, 0, n) cout << L[i] << '\n';
    } else {
        cout << "No\n";
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