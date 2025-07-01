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

ll dp[35][35][35][455];

void solve() {
    string s; cin >> s;
    int K; cin >> K;
    K = min(450, K);
    int n = s.size();
    vector<int> a(n);
    rep (i, 0, n) rep (j, 0, 3) if (s[i] == "KEY"[j]) a[i] = j;
    vector<vector<int>> pos(3);
    rep (i, 0, n) pos[a[i]].pb(i);
    dp[0][0][0][0] = 1;
    vector<int> sz(3);
    rep (i, 0, 3) sz[i] = pos[i].size();
    rep (i, 0, sz[0] + 1) rep (j, 0, sz[1] + 1) rep (k, 0, sz[2] + 1) {
        if (i < sz[0]) {
            int x = 0;
            rep (p, 0, j) x += pos[1][p] > pos[0][i];
            rep (p, 0, k) x += pos[2][p] > pos[0][i];
            rep (t, 0, K - x + 1) dp[i + 1][j][k][t + x] += dp[i][j][k][t];
        }
        if (j < sz[1]) {
            int x = 0;
            rep (p, 0, i) x += pos[0][p] > pos[1][j];
            rep (p, 0, k) x += pos[2][p] > pos[1][j];
            rep (t, 0, K - x + 1) dp[i][j + 1][k][t + x] += dp[i][j][k][t];
        }
        if (k < sz[2]) {
            int x = 0;
            rep (p, 0, i) x += pos[0][p] > pos[2][k];
            rep (p, 0, j) x += pos[1][p] > pos[2][k];
            rep (t, 0, K - x + 1) dp[i][j][k + 1][t + x] += dp[i][j][k][t];
        }
    }
    ll ans = 0;
    rep (i, 0, K + 1) ans += dp[sz[0]][sz[1]][sz[2]][i];
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}