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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

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

void solve() {
    int n, m; cin >> n;
    m = n * 2;
    string t, rt; cin >> t, rt = t;
    reverse(all(rt));
    RollingHash ht(t, 101, MOD), hrt(rt, 101, MOD);
    // abcbac <=> cabcba
    // i, n, n - i
    rep (i, 0, n + 1) {
        ll vt, vrt;
        vt = (ht.query(0, i) * fpow(101, n - i, MOD) % MOD + ht.query(m - (n - i), m)) % MOD;
        vrt = hrt.query(m - i - n, m - i);
        // cout << 0 << ' ' << i << ' ' << m - (n - i) << ' ' << m << '\n';
        // cout << i << ' ' << vt << ' ' << vrt << '\n';
        if (vt == vrt) {
            for (int j = n - 1; j >= 0; --j) {
                cout << t[j + i];
            }
            cout << '\n' << i << '\n';
            return;
        }
    }
    cout << -1 << '\n'; 
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}