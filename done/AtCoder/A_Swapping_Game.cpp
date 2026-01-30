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
    int n, L; cin >> n >> L;
    vector<int> c(n + 1);
    vector p(n + 1, vector<int>(L));
    iota(all(p[0]), 0);
    rep (i, 1, n + 1) {
        cin >> c[i];
        rep (j, 0, L) cin >> p[i][j], p[i][j]--;
    }
    vector<int> dp(n + 1, -LINF);
    auto count_inv = [&](int x, int y) -> int {
        int res = 0;
        vector<int> id(L), id2(L);
        rep (i, 0, L) id[p[x][i]] = i;
        rep (i, 0, L) id2[i] = id[p[y][i]];
        rep (i, 0, L) rep (j, i + 1, L) res += id2[i] > id2[j];
        return res;
    };
    if (L == 1) {
        cout << accumulate(all(c), 0LL) << '\n';
        return;
    }
    // step = inv <= L * (L - 1) / 2 <= 36
    // 30000 * 36 * count_inv
    // cout << count_inv(1, 2) << '\n';
    dp[0] = 0;
    int mx = -LINF, tinv = L * (L - 1) / 2;
    rep (i, 1, n + 1) {
        if (i >= tinv) chmax(mx, dp[i - tinv]);
        chmax(dp[i], mx + c[i]);
        rep (j, 1, tinv) {
            if (i - j < 0) break;
            if (count_inv(i - j, i) <= j) chmax(dp[i], dp[i - j] + c[i]);
        }
    }
    // cout << dp;
    cout << *max_element(all(dp)) << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}