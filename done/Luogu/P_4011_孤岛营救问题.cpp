// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int info[15][15][15][15];
vector<int> key[15][15];

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void solve() {
    int n, m, p; cin >> n >> m >> p;
    int k; cin >> k;
    rep (i, 0, k) {
        int x, y, x2, y2, g; cin >> x >> y >> x2 >> y2 >> g;
        if (g == 0) g = -1;
        x--, y--, x2--, y2--;
        info[x][y][x2][y2] = g;
        info[x2][y2][x][y] = g; 
    }
    int s; cin >> s;
    rep (i, 0, s) {
        int x, y, q; cin >> x >> y >> q;
        x--, y--;
        key[x][y].pb(q);
    }
    vector vis(n, vector<vector<bool>>(m, vector<bool>(1 << s, 0)));
    queue<tuple<int, int, int, int>> q;
    int ma = 0;
    for (int id : key[0][0]) {
        ma |= 1 << (id - 1);
    }
    q.push({0, 0, ma, 0});
    vis[0][0][ma] = 1;
    while (!q.empty()) {
        auto [x, y, mask, d] = q.front();
        q.pop();
        if (x == n - 1 && y == m - 1) {
            cout << d << '\n';
            return;
        }
        rep (i, 0, 4) {
            int nx = x + dx[i], ny = y + dy[i], nxt = mask;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || info[x][y][nx][ny] == -1) continue;
            for (int id : key[nx][ny]) {
                nxt |= 1 << (id - 1);
            }
            if (vis[nx][ny][nxt]) continue;
            vis[nx][ny][nxt] = 1;
            if (info[x][y][nx][ny] == 0) {
                q.push({nx, ny, nxt, d + 1});
            } else if (nxt >> (info[x][y][nx][ny] - 1) & 1) {
                q.push({nx, ny, nxt, d + 1});
            }
        }
    }
    cout << -1 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}