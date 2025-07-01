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
#define ld long double
#define F first
#define S second

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
    vector<ll> c(n), pre(n + 1);
    rep (i, 0, n) cin >> c[i];
    reverse(all(c));
    pre[0] = 0;
    rep (i, 0, n) pre[i + 1] = pre[i] + c[i];
    // dp[i] = (i - j <= k) max(dp[j] + pre[j] - (i - j) ^ 2);
    // dp[i] = (i - j <= k) max(dp[j] + pre[j] - i ^ 2 + 2 * i * j - j ^ 2)
    // m = 2 * j, b = dp[j] + pre[j] - j ^ 2;
    // slopes and queries monotonically increasing
    // be careful about the expired lines
    vector<ll> dp(n + 1);
    deque<int> dq;
    auto get_b = [&](int x) -> ll {
        return dp[x] + pre[x] - 1LL * x * x;
    };
    auto check = [&](int o, int a, int b) -> bool {
        // bruh I stupid
        // calculate again the intersection point
        // y = ax + b, y = cx + d
        // 0 = (a - c)x + (b - d)
        // x = (d - b) / (a - c)
        // y = not important
        return min(1LL * o + k, (get_b(a) - get_b(o)) / (2 * o - 2 * a)) > 
            (get_b(b) - get_b(a)) / (2 * a - 2 * b);
    };
    auto calc = [&](int x, int cur) -> ll {
        return 2LL * x * cur + get_b(x);
    };
    dp[0] = 0;
    dq.pb(0);
    rep (i, 1, n + 1) {
        if (!dq.empty() && i - dq.front() > k) dq.pop_front();
        while (dq.size() >= 2 && calc(dq[0], i) < calc(dq[1], i))
            dq.pop_front();
        int cur = dq.front();
        ll m = 2 * cur, b = get_b(cur);
        dp[i] = m * i + b - 1LL * i * i;
        while (dq.size() >= 2 && check(dq.end()[-2], dq.back(), i))
            dq.pop_back();
        dq.pb(i);
    }
    cout << dp[n] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}