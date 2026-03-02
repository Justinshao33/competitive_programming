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

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void solve() {
    int h, n, m; cin >> h >> n >> m;
    vector G(h, vector<string>(n));
    rep (k, 0, h) rep (i, 0, n) cin >> G[k][i];
    vector id(h, vector (n, vector<int>(m, -1)));
    int cnt = 0;
    rep (k, 0, h) {
        auto &ID = id[k];
        rep (i, 0, n) rep (j, 0, m) {
            if (G[k][i][j] != '#' && ID[i][j] == -1) {
                queue<pii> q;
                q.push({i, j});
                ID[i][j] = cnt;
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    rep (l, 0, 4) {
                        int nx = x + dx[l], ny = y + dy[l];
                        if (nx < 0 || ny < 0 || nx >= n || ny >= m || G[k][nx][ny] == '#') continue;
                        if (ID[nx][ny] != -1) continue;
                        ID[nx][ny] = cnt;
                        q.push({nx, ny});
                    }
                }
                cnt++;
            }
        }
    }
    vector<int> w(cnt);
    rep (k, 0, h) rep (i, 0, n) rep (j, 0, m) if (id[k][i][j] != -1) {
        w[id[k][i][j]] += G[k][i][j] - '0';
    }
    vector<vector<int>> adj(cnt), radj(cnt);
    rep (k, 0, h) rep (i, 0, n) rep (j, 0, m) {
        int cur = id[k][i][j];
        if (cur != -1) {
            if (k + 1 < h) {
                int to = id[k + 1][i][j];
                if (to != -1) adj[cur].push_back(to);
            }
            if (k - 1 >= 0) {
                int to = id[k - 1][i][j];
                if (to != -1) radj[cur].push_back(to);
            }
        }
    }
    auto lisan = [](vector<int> &vec) -> void {
        sort(all(vec));
        vec.erase(unique(all(vec)), vec.end());
    };
    rep (i, 0, cnt) {
        lisan(adj[i]);
        lisan(radj[i]);
    }
    vector<array<int, 3>> dp(cnt, {-LINF, -1, -LINF});
    auto dp2 = dp;
    auto upd = [&](array<int, 3> &x, array<int, 2> y) -> void {
        if (y[1] != -1 && x[1] == y[1]) {
            chmax(x[0], y[0]);
        } else {
            if (y[0] >= x[0]) x[2] = x[0], x[0] = y[0], x[1] = y[1];
            else chmax(x[2], y[0]);
        }
    };
    for (int cur = cnt - 1; cur >= 0; --cur) {
        upd(dp[cur], {w[cur], -1});
        for (int to : adj[cur]) {
            upd(dp[cur], {dp[to][0] + w[cur], to});
        }
    }
    for (int cur = cnt - 1; cur >= 0; --cur) {
        upd(dp2[cur], {dp[cur][0], -1});
        for (int to : radj[cur]) {
            if (dp[to][1] == cur) {
                upd(dp2[cur], {dp[to][0], to});
                upd(dp2[cur], {w[cur] + dp[to][2], to});
            } else {
                upd(dp2[cur], {dp[to][0] + w[cur], to});
            }
        }
        for (int to : adj[cur]) {
            if (dp2[to][1] == cur) {
                upd(dp2[cur], {dp2[to][0], -1});
                upd(dp2[cur], {dp2[to][2] + w[cur], -1});
            } else {
                upd(dp2[cur], {dp2[to][0] + w[cur], -1});
            }
        }
    }
    int q; cin >> q;
    while (q--) {
        int i, j, k; cin >> i >> j >> k;
        i--, j--, k--;
        cout << dp2[id[i][j][k]][0] << '\n';
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