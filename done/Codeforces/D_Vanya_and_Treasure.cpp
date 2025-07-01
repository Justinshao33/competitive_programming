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

const int dx[4] = {1, 0, -1, 0}, dy[4] ={0, 1, 0, -1};

void solve() {
    int n, m, p; cin >> n >> m >> p;
    vector<vector<pii>> pos(p);
    rep (i, 0, n) rep (j, 0, m) {
        int c; cin >> c;
        c--;
        pos[c].pb({i, j});
    }
    vector dis(n, vector<int>(m, IINF));
    for (auto &[x, y] : pos[0]) {
        dis[x][y] = x + y;
    }
    vector<vector<int>> row(n), col(n);
    rep (i, 0, p - 1) {
        if (ssize(pos[i]) * ssize(pos[i + 1]) <= n * m) {
            for (auto &[x, y] : pos[i]) {
                for (auto &[x2, y2] : pos[i + 1]) {
                    chmin(dis[x2][y2], dis[x][y] + abs(x - x2) + abs(y - y2));
                }
            }
        } else {
            queue<pii> q;
            vector fd(n, vector<int>(m, IINF));
            for (auto &[x, y] : pos[i]) {
                q.push({x, y});
                fd[x][y] = dis[x][y];
            }
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                rep (i, 0, 4) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                    if (chmin(fd[nx][ny], fd[x][y] + 1)) {
                        q.push({nx, ny});
                    }
                }
            }
            for (auto &[x, y] : pos[i + 1]) dis[x][y] = fd[x][y];
        }
    }
    cout << dis[pos[p - 1][0].fi][pos[p - 1][0].se] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}