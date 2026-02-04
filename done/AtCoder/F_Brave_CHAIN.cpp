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
    vector<int> a(3 * n);
    for (int &x : a) cin >> x, x--;
    vector dp(n, vector<int>(n, -IINF));
    vector<int> row_mx(n, -IINF);
    int tot_mx = 0, add = 0;
    auto upd = [&](int x, int y, int v) -> void {
        chmax(dp[x][y], v);
        chmax(dp[y][x], v);
        chmax(row_mx[x], v);
        chmax(row_mx[y], v);
        chmax(tot_mx, v);
    };
    upd(a[0], a[1], 0);
    rep (i, 0, n - 1) {
        vector<int> num;
        rep (j, 0, 3) num.push_back(a[i * 3 + 2 + j]);
        sort(all(num));
        if (num[0] == num[2]) {
            add++;
            continue;
        }
        // x, y, z
        // dp[i][a][b] -> dp[i + 1][a][b] => do nothing
        vector<array<int, 3>> tran;
        rep (j, 0, 3) rep (k, 0, 3) {
            if (j == k) continue;
            int x = num[j], y = num[k], z = num[0] ^ num[1] ^ num[2] ^ x ^ y;
            // dp[i][a][b] -> dp[i + 1][a][x] => from row_mx O(n)
            rep (a, 0, n) {
                int val = row_mx[a];
                if (y == z) chmax(val, dp[a][y] + 1);
                tran.push_back({a, x, val});
            }
            // dp[i][a][b] -> dp[i + 1][x][y] => from tot_mx O(1)
            tran.push_back({x, y, max(tot_mx, dp[z][z] + 1)});
        }
        for (const auto &[x, y, val] : tran) upd(x, y, val);
    }
    // update last one
    upd(a.back(), a.back(), max(tot_mx, dp[a.back()][a.back()] + 1));
    cout << tot_mx + add << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}