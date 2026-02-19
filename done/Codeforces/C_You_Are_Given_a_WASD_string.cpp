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

int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};

void solve() {
    string s; cin >> s;
    int n = ssize(s);
    vector<int> u(n + 1, 0), d(n + 1, 0), l(n + 1, 0), r(n + 1, 0);
    vector<int> u2(n + 1, 0), d2(n + 1, 0), l2(n + 1, 0), r2(n + 1, 0);
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') x--;
        else if (s[i] == 'S') x++;
        else if (s[i] == 'A') y--;
        else y++;
        if (i) u2[i] = u2[i - 1];
        if (i) d2[i] = d2[i - 1];
        if (i) l2[i] = l2[i - 1];
        if (i) r2[i] = r2[i - 1];
        chmin(u2[i], x);
        chmax(d2[i], x);
        chmin(l2[i], y);
        chmax(r2[i], y);
    }
    u[n] = x;
    d[n] = x;
    l[n] = y;
    r[n] = y;
    int ans = (d2[n - 1] - u2[n - 1] + 1) * (r2[n - 1] - l2[n - 1] + 1);
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'W') x++;
        else if (s[i] == 'S') x--;
        else if (s[i] == 'A') y++;
        else y--;
        u[i] = u[i + 1];
        d[i] = d[i + 1];
        l[i] = l[i + 1];
        r[i] = r[i + 1];
        chmin(u[i], x);
        chmax(d[i], x);
        chmin(l[i], y);
        chmax(r[i], y);
        rep (k, 0, 4) {
            int U = min(u2[i], dx[k] + u[i + 1]);
            int D = max(d2[i], dx[k] + d[i + 1]);
            int L = min(l2[i], dy[k] + l[i + 1]);
            int R = max(r2[i], dy[k] + r[i + 1]);
            chmin(ans, (D - U + 1) * (R - L + 1));
        }
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}