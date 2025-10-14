#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    string s, t; cin >> s >> t;
    int n = ssize(s), m = ssize(t);
    if (m > n) {
        cout << 0 << '\n';
        return;
    }
    vector<int> fail(m);
    fail[0] = -1;
    int ptr = -1;
    rep (i, 1, m) {
        while (ptr >= 0 && t[ptr + 1] != t[i]) ptr = fail[ptr];
        ptr += t[ptr + 1] == t[i];
        fail[i] = ptr;
    }
    vector nxt(m, vector<int>(26, 0));
    rep (i, 0, m) {
        rep (j, 0, 26) {
            if (t[i] - 'a' == j) {
                nxt[i][j] = i + 1;
            } else {
                nxt[i][j] = i == 0 ? 0 : nxt[fail[i - 1] + 1][j];
            }
        }
    }
    vector dp(n + 1, vector<int>(m, -IINF));
    dp[0][0] = 0;
    rep (i, 0, n) rep (j, 0, m) {
        if (dp[i][j] == -IINF) continue;
        rep (k, 0, 26) if (s[i] == '?' || s[i] - 'a' == k) {
            chmax(dp[i + 1][nxt[j][k] == m ? fail[m - 1] + 1 : nxt[j][k]], dp[i][j] + (nxt[j][k] == m));
        }
    }
    cout << *max_element(all(dp[n])) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}