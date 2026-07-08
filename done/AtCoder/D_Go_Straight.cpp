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

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> G(n);
    rep (i, 0, n) cin >> G[i];
    vector dis(4, vector(n, vector<int>(m, IINF)));
    vector opt(4, vector(n, vector<array<int, 3>>(m, {-1, -1, -1})));
    queue<array<int, 3>> q;
    rep (i, 0, n) rep (j, 0, m) {
        if (G[i][j] == 'S') {
            rep (k, 0, 4) {
                q.push({k, i, j});
                dis[k][i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto [d, x, y] = q.front(); q.pop();
        rep (k, 0, 4) {
            if (G[x][y] == 'o' && k != d) continue;
            if (G[x][y] == 'x' && k == d) continue;
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || G[nx][ny] == '#') continue;
            if (chmin(dis[k][nx][ny], dis[d][x][y])) {
                q.push({k, nx, ny});
                opt[k][nx][ny] = {d, x, y};
            }
        }
    }
    int ans = IINF;
    array<int, 3> cur;
    rep (i, 0, n) rep (j, 0, m) {
        if (G[i][j] == 'G') {
            rep (k, 0, 4) {
                if (chmin(ans, dis[k][i][j])) cur = {k, i, j};
            }
        }
    }
    if (ans == IINF) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    string dir;
    while (G[cur[1]][cur[2]] != 'S') {
        if (cur[0] == 0) {
            dir.push_back('R');
        } else if (cur[0] == 1) {
            dir.push_back('D');
        } else if (cur[0] == 2) {
            dir.push_back('L');
        } else {
            dir.push_back('U');
        } 
        cur = opt[cur[0]][cur[1]][cur[2]];
    }
    reverse(all(dir));
    cout << dir << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}