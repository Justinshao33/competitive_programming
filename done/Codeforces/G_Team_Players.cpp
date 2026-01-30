#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int unsigned long long

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
    int n, m; cin >> n >> m;
    int A, B, C; cin >> A >> B >> C;
    vector<vector<int>> adj(n);
    rep (i, 0, m) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    auto C2 = [&](int x) -> int { return x * (x - 1) / 2; };
    auto sum = [&](int l, int r) -> int { 
        if (l > r) return 0;
        return (l + r) * (r - l + 1) / 2;
    };
    // #0 - #1 + #2 - #3
    int c0 = 0, c1 = 0, c2 = 0, c3 = 0;
    { // #0
        rep (x, 0, n) {
            c0 += x * ( A * C2(n - 1 - x) + B * x * (n - x - 1) + C * C2(x) );
        }
    }
    { // #1
        rep (x, 0, n) for (int y : adj[x]) if (x < y) {
            c1 += A * x * (n - 1 - y) + B * y * (n - 1 - y) + C * sum(y + 1, n - 1) + 
                  A * x * (y - x - 1) + B * sum(x + 1, y - 1) + C * y * (y - x - 1) + 
                  A * sum(0, x - 1) + B * x * (x) + C * y * (x); 
        }        
    }
    { // #2
        rep (x, 0, n) {
            sort(all(adj[x]));
            pii L{0, 0}, R{0, 0};
            for (int y : adj[x]) {
                if (y < x) {
                    c2 += A * L.fi + B * L.se * y;
                    L = L + make_pair(y, 1ULL);
                } else {
                    c2 += B * R.fi + C * R.se * y;
                    R = R + make_pair(y, 1ULL);
                }
            }
            c2 += A * x * C2(R.se) + B * x * (L.se * R.se) + C * x * C2(L.se);
            c2 += A * L.fi * R.se + C * R.fi * L.se;
        }
    }
    { // #3
        vector<int> ord(n), rk(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int a, int b) {
            return adj[a].size() > adj[b].size();
        });
        rep (i, 0, n) rk[ord[i]] = i;
        vector<vector<int>> D(n);
        rep (u, 0, n) {
            for (int v : adj[u]) if (rk[u] < rk[v]) {
                D[u].pb(v);
            }
        }
        vector<int> vis(n);
        for (int x : ord) { // c3
            for (int y : D[x]) vis[y] = 1;
            for (int y : D[x]) for (int z : D[y]) if (vis[z]) {
                int mn = min({x, y, z}), mx = max({x, y, z});
                c3 += A * mn + B * (x + y + z - mn - mx) + C * mx;
            }
            for (int y : D[x]) vis[y] = 0;
        }
    }
    debug(c0, c1, c2, c3);
    cout << c0 - c1 + c2 - c3 << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}