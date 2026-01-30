#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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

struct RollingHash {
    string s;
    int n, c, mod;
    vector <long long> pre, pw;
    RollingHash() {}
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
    long long query(int l, int r) { // (l, r]
        return (pre[r] - ((pre[l] * pw[r - l]) % mod) + mod) % mod;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<RollingHash> sh(26);
    rep (c, 0, 26) {
        string t;
        rep (i, 0, n) t.push_back('0' + (s[i] - 'a' == c));
        // cout << t << '\n';
        sh[c] = RollingHash(t, 487, MOD); 
    }
    while (q--) {
        int x, y, len; cin >> x >> y >> len;
        vector<int> S, T;
        rep (i, 0, 26) {
            S.push_back(sh[i].query(x - 1, x + len - 1));
            T.push_back(sh[i].query(y - 1, y + len - 1));
        }
        // cout << S << T;
        sort(all(S));
        sort(all(T));
        cout << ((S == T) ? "YES\n" : "NO\n");
    }
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}