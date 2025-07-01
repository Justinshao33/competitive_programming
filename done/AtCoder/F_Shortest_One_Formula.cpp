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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<string> str(2000 + 1), str2(2000 + 1);
    vector<int> dp(2001, IINF), dp2(2001, IINF);
    str[1] = "1", str[11] = "11", str[111] = "111", str[1111] = "1111";
    str2[1] = "1", str2[11] = "11", str2[111] = "111", str2[1111] = "1111";
    dp[1] = 1, dp[11] = 2, dp[111] = 3, dp[1111] = 4;
    dp2[1] = 1, dp2[11] = 2, dp2[111] = 3, dp2[1111] = 4;
    auto dfs = [&](auto self, int num) -> void {
        if (dp[num] != IINF) return;
        int l = -1, r, l2 = -1, r2, t, t2;
        rep (i, 1, num) {
            self(self, i);
            self(self, num - i);
            if (chmin(dp[num], dp[i] + dp[num - i] + 1)) {
                l = i, r = num - i;
                t = 1;
            }
            if (chmin(dp2[num], dp[i] + dp[num - i] + 3)) {
                l2 = i, r2 = num - i;
                t2 = 1;
            }
            if (i != 1 && num % i == 0) {
                self(self, num / i);
                self(self, i);
                if (chmin(dp2[num], dp2[i] + dp2[num / i] + 1)) {
                    l2 = i, r2 = num / i;
                    t2 = 2;
                }
                if (chmin(dp[num], dp2[i] + dp2[num / i] + 1)) {
                    l = i, r = num / i;
                    t = 2;
                }
            }
        }
        if (l != -1) {
            if (t == 1) str[num] = str[l] + "+" + str[r];
            else str[num] = str2[l] + "*" + str2[r];
        }
        if (l2 != -1) {
            if (t2 == 1) str2[num] = "(" + str[l2] + "+" + str[r2] + ")";
            else str2[num] = str2[l2] + "*" + str2[r2];
        }
    };
    dfs(dfs, n);
    cout << (dp[n] < dp2[n] ? str[n] : str2[n]) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}