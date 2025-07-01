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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n; cin >> n;
    vector<pii> pt;
    pt.pb({0, 0});
    int x; cin >> x;
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }
    pt.pb({x, 0});
    vector<int> wall(n);
    rep (i, 0, n) {
        cin >> wall[i];
        pt.pb({wall[i], 1});
    }
    map<int, int> mp;
    rep (i, 0, n) {
        int z; cin >> z;
        mp[wall[i]] = z;
        pt.pb({z, 2});
    }
    n = 2 * n + 2;
    sort(all(pt));
    vector dp(n, vector<vector<ll>>(n, vector<ll>(2, LINF))); // 0L1R
    rep (i, 0, n) if (pt[i].F == 0 && pt[i].S == 0) {
        dp[i][i][0] = dp[i][i][1] = 0;
        break;
    }
    rep (len, 1, n) {
        rep (i, 0, n) {
            int j = i + len;
            if (j >= n) break;
            if (pt[i].S != 1 || (mp[pt[i].F] >= pt[i].F && mp[pt[i].F] <= pt[j].F)) {
                dp[i][j][0] = min(dp[i + 1][j][0] + pt[i + 1].F - pt[i].F, dp[i + 1][j][1] + pt[j].F - pt[i].F);
            }
            if (pt[j].S != 1 || (mp[pt[j].F] >= pt[i].F && mp[pt[j].F] <= pt[j].F)) {
                dp[i][j][1] = min(dp[i][j - 1][0] + pt[j].F - pt[i].F, dp[i][j - 1][1] + pt[j].F - pt[j - 1].F);
            }
        }
    }
    rep (i, 0, n) if (pt[i].F == x) {
        ll ans = LINF;
        rep (j, 0, i + 1) rep (k, i, n) chmin(ans, min(dp[j][k][0], dp[j][k][1]));
        cout << (ans == LINF ? -1 : ans) << '\n';
        return;
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}