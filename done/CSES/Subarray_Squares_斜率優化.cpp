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

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> pre(n + 1);
    pre[0] = 0;
    rep (i, 1, n + 1) {
        cin >> pre[i];
        pre[i] += pre[i - 1];
    }
    /*
    O(NNK)
    dp[i][k + 1] = dp[j][k] + (pre[i] - pre[j]) ^ 2
    dp[i][k + 1] = dp[j][k] + pre[i]^2 - 2*pre[j]*pre[i] + pre[j]^2
    m = -2 * pre[j], b = pre[j]^2 + dp[j][k]
    斜率單調，轉移點單調 => 斜率優化 O(NK)
    */
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, LINF));
    dp[0][0] = 0;
    rep (j, 0, k) {
        deque<int> dq;
        dq.pb(0);
        auto calc = [&](int i, ll x) -> ll {
            return -2 * pre[i] * x + pre[i] * pre[i] + dp[i][j];
        };
        auto check = [&](int o, int a, int b) -> bool {
            return (pre[o] * pre[o] + dp[o][j] - pre[b] * pre[b] - dp[b][j]) * (-2 * pre[a] - -2 * pre[o]) <=
            (pre[o] * pre[o] + dp[o][j] - pre[a] * pre[a] - dp[a][j]) * (-2 * pre[b] - -2 * pre[o]);
        };
        rep (i, 1, n + 1) {
            while (dq.size() > 1 && calc(dq[0], pre[i]) > calc(dq[1], pre[i])) {
                dq.pop_front();
            }
            dp[i][j + 1] = calc(dq.front(), pre[i]) + pre[i] * pre[i];
            while (dq.size() > 1 && check(dq.end()[-2], dq.back(), i)) {
                dq.pop_back();
            }
            dq.pb(i);
        }
    }
    cout << dp[n][k] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}