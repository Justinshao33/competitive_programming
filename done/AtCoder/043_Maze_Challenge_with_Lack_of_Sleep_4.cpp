#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void solve() {
    int n, m; cin >> n >> m;
    int sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
    sx--, sy--, tx--, ty--;
    vector<vector<int>> g(n, vector<int>(m, 1));
    rep (i, 0, n) rep (j, 0, m) {
        char c; cin >> c;
        if (c == '.') g[i][j] = 0;
    }
    queue<tuple<int, int, int>> q;
    vector<vector<vector<int>>> dis(n, vector<vector<int>>(m, vector<int>(4, IINF)));
    rep (i, 0, 4) {
        q.push({sx, sy, i});
        dis[sx][sy][i] = 0;
    }
    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();
        rep (i, 0, 4) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny]) continue;
            if (i == d) {
                if (chmin(dis[nx][ny][i], dis[x][y][i])) {
                    q.push({nx, ny, i});
                }
            } else {
                if (chmin(dis[nx][ny][i], dis[x][y][d] + 1)) {
                    q.push({nx, ny, i});
                }
            }
        }
    }
    cout << *min_element(all(dis[tx][ty])) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}