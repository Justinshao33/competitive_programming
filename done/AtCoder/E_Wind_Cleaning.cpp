#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> G(n);
    rep (i, 0, n) cin >> G[i];
    queue<array<int, 6>> q;
    map<array<int, 6>, int> mp;
    int tx = 0, ty = 0;
    rep (i, 0, n) rep (j, 0, m) if (G[i][j] == 'T') {
        q.push({0, 0, 0, 0, 0, 0});
        tx = i, ty = j;
    }
    int ans = IINF;
    while (!q.empty()) {
        auto [x, y, u, d, l, r] = q.front(); q.pop();
        bool f = 1;
        rep (i, u, n - d) rep (j, l, m - r) if (G[i][j] == '#') {
            f = 0;
        }
        if (f) {
            chmin(ans, mp[{x, y, u, d, l, r}]);
            continue;
        }
        for (int i : {1, -1}) {
            {
                int nx = x + i, ny = y;
                if (tx + nx < u || tx + nx >= n - d || ty + ny < l || ty + ny >= m - r || G[tx + nx][ty + ny] != '#') {
                    if (!mp.count({nx, ny, max(u, nx), max(d, -nx), l, r})) {
                        mp[{nx, ny, max(u, nx), max(d, -nx), l, r}] = mp[{x, y, u, d, l, r}] + 1;
                        q.push({{nx, ny, max(u, nx), max(d, -nx), l, r}});
                    } else if (chmin(mp[{nx, ny, max(u, nx), max(d, -nx), l, r}], mp[{x, y, u, d, l, r}] + 1)) {
                        q.push({nx, ny, max(u, nx), max(d, -nx), l, r});
                    }
                }
            }
            {
                int nx = x, ny = y + i;
                if (tx + nx < u || tx + nx >= n - d || ty + ny < l || ty + ny >= m - r || G[tx + nx][ty + ny] != '#') {
                    if (!mp.count({nx, ny, u, d, max(l, ny), max(r, -ny)})) {
                        mp[{nx, ny, u, d, max(l, ny), max(r, -ny)}] = mp[{x, y, u, d, l, r}] + 1;
                        q.push({{nx, ny, u, d, max(l, ny), max(r, -ny)}});
                    } else if (chmin(mp[{nx, ny, u, d, max(l, ny), max(r, -ny)}], mp[{x, y, u, d, l, r}] + 1)) {
                        q.push({nx, ny, u, d, max(l, ny), max(r, -ny)});
                    }
                }
            }
        }
    }
    cout << (ans == IINF ? -1 : ans) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}