// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000009;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct RollingHash {
    string s;
    int n, c, mod;
    vector <long long> pre, pw;
    RollingHash(string _s, int _c, int _mod) : s(_s), n(s.size()), c(_c), mod(_mod) {
        pre.resize(n + 1, 0);
        pw.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = ((pre[i - 1] * c) + s[i - 1]) % mod;
        }
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i - 1] * c % mod;
        }
    }
    long long query(int l, int r) {
        return (pre[r] - ((pre[l] * pw[r - l]) % mod) + mod) % mod;
    }
};

ll dp[5005][5005];

void solve() {
    int n, q; cin >> n >> q;
    string s, t; cin >> s;
    t = s;
    reverse(all(t));
    int c = get_rand(129, 500), c2 = get_rand(129, 500);
    RollingHash hs(s, c, MOD), ht(t, c, MOD), hs2(s, c2, MOD2), ht2(t, c2, MOD2);
    rep (i, 0, n) dp[i][i] = 1;
    auto check = [&](int l, int r) -> bool {
        return (hs.query(l, r + 1) == ht.query(n - r - 1, n - l)) && (hs2.query(l, r + 1), ht2.query(n - r - 1, n - l));
    };
    rep (len, 1, n) {
        rep (i, 0, n) {
            int j = i + len;
            if (j >= n) break;
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + check(i, j);
        }
    }
    while (q--) {
        int l, r; cin >> l >> r;
        l--, r--;
        cout << dp[l][r] << '\n';
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