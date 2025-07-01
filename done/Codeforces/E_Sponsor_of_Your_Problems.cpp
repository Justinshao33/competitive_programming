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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    string s, t; cin >> s >> t;
    int l = stoi(s), r = stoi(t);
    int n = ssize(s);
    int ptr = 0, ans = 0;
    while (ptr < n && s[ptr] == t[ptr]) {
        ans += 2;
        ptr++;
    }
    if (ptr == n) {
        cout << ans << '\n';
        return;
    }
    if (s[ptr] + 1 == t[ptr]) {
        ans += 1;
        ptr++;
        while (ptr < n && t[ptr] == '0' && s[ptr] == '9') {
            ans += 1;
            ptr++;
        }
        cout << ans << '\n';
    } else {
        cout << ans << '\n';
    }
    // vector<int> pw(n, 0);
    // pw[0] = 1;
    // rep (i, 1, n) pw[i] = pw[i - 1] * 3;
    // int ans = 2 * n;
    // auto dfs = [&](auto self, int id, int num, bool bg, bool ls) -> void {
    //     if (id == n) {
    //         if (num < l || num > r) return;
    //         string k = to_string(num);
    //         int res = 0;
    //         rep (i, 0, n) {
    //             if (s[i] == k[i]) res++;
    //             if (t[i] == k[i]) res++;
    //         }
    //         chmin(ans, res);
    //         return;
    //     }
    //     bool nb = bg && s[id] == t[id], nl = ls && s[id] == t[id];
    //     if (bg && ls) {
    //         self(self, id + 1, num * 10 + t[id] - '0', bg, nl);
    //         self(self, id + 1, num * 10 + s[id] - '0', nb, ls);
    //         if () self(self, id + 1, num * 10 + )
    //     } else if (bg) {

    //     } else if ()
    //     if (ls) {
    //         self(self, id + 1, num * 10 + s[id] - '0', bg && s[id] == t[id], ls)
    //     }
    // };
    // dfs(dfs, 0, 0, true, true);
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}