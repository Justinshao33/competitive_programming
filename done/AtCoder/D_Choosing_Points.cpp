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
    // int upp = 2e5, mx = 0, num = 0;
    // rep (s, 1, upp + 1) {
    //     int cnt = 0;
    //     for (int i = 1; i * i <= s; i++) {
    //         int j = sqrt(s - i * i);
    //         if (i * i + j * j == s) {
    //             cnt++;
    //         }
    //     }
    //     if (chmax(mx, cnt)) num = s;
    // }
    // debug(mx, num);
    int n; cin >> n;
    n *= 2;
    auto work = [&]() -> vector<vector<int>> {
        int d; cin >> d;
        vector<pii> pace;
        for (int i = 0; i * i <= d; i++) {
            int j = sqrt(d - i * i);
            if (i * i + j * j == d) {
                pace.push_back({i, j});
                pace.push_back({-i, j});
                pace.push_back({i, -j});
                pace.push_back({-i, -j});
            }
        }
        vector col(n, vector<int>(n, -1));
        auto dfs = [&](auto self, int x, int y) -> void {
            for (const auto &[dx, dy] : pace) {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if (col[nx][ny] != -1) {
                    assert(col[nx][ny] == (col[x][y] ^ 1));
                } else {
                    col[nx][ny] = col[x][y] ^ 1;
                    self(self, nx, ny);
                }
            }
        };
        rep (i, 0, n) rep (j, 0, n) if (col[i][j] == -1) {
            col[i][j] = 0;
            dfs(dfs, i, j);
        }
        return col;
    };
    auto c1 = work();
    auto c2 = work();
    vector<vector<pii>> pos(4);
    rep (i, 0, n) rep (j, 0, n) {
        pos[(c1[i][j] << 1) | c2[i][j]].push_back({i, j});
    }
    int mx = 0;
    rep (i, 0, 4) {
        if (ssize(pos[i]) > ssize(pos[mx])) mx = i;
    }
    assert(ssize(pos[mx]) >= n * n / 4);
    for (int cnt = 0; const auto &[x, y] : pos[mx]) {
        cout << x << ' ' << y << '\n'; 
        cnt++;
        if (cnt == n * n / 4) break; 
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