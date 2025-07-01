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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> g(n), g2(n);
    rep (i, 0, n) cin >> g[i];
    rep (i, 0, n) cin >> g2[i];
    vector a(n, vector<int>(m, 0));
    auto b = a;
    vector<pii> B;
    int ca = 0, cb = 0;
    rep (i, 0, n) rep (j, 0, m) {
        a[i][j] = g[i][j] == '#';
        b[i][j] = g2[i][j] == '#';
        a[i][j] ^= (i + j) % 2;
        b[i][j] ^= (i + j) % 2;
        ca += a[i][j];
        cb += b[i][j];
        if (b[i][j]) B.pb({i, j});
    }
    if (ca != cb) {
        cout << -1 << '\n';
        return;
    }
    vector<array<int, 4>> ans;
    // move to not previous and maybe the closest one
    rep (tx, 0, n) rep (ty, 0, m) if (a[tx][ty] != b[tx][ty]) {
        queue<pii> q;
        vector from(n, vector<pii>(m, {-1, -1}));
        q.push({tx, ty});
        from[tx][ty] = {tx, ty};
        int sx, sy;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            bool f = 0;
            rep (k, 0, 4) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m || from[nx][ny].fi != -1 || nx * m + ny < tx * m + ty) continue;
                q.push({nx, ny});
                from[nx][ny] = {x, y};
                if (a[nx][ny] == b[tx][ty]) {
                    f = 1;
                    sx = nx, sy = ny;
                    break;
                }
            }
            if (f) break;
        }
        while (sx != tx || sy != ty) {
            auto &[nx, ny] = from[sx][sy];
            ans.pb({sx, sy, nx, ny});
            debug(sx, sy, nx, ny, tx, ty);
            swap(a[sx][sy], a[nx][ny]);
            sx = nx, sy = ny;
        }
        debug(a);
        debug(b);
    }
    assert(a == b);
    assert(ans.size() <= 200 * n * m);
    cout << ans.size() << '\n';
    for (auto &[x, y, x2, y2] : ans) cout << x + 1 << ' ' << y + 1 << ' ' << x2 + 1 << ' ' << y2 + 1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}