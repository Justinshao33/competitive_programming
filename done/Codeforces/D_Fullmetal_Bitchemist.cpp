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

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int ans = n * (n + 1) / 2;
    // vector<int> dif;
    // rep (i, 0, n - 1) {
    //     dif.push_back(s[i] ^ s[i + 1]);
    // }
    // rep (t, 0, 2) {
    //     vector<int> cnt(2, 0);
    //     int z = 0;
    //     cnt[0]++;
    //     rep (i, 0, n - 1) {
    //         z += dif[i] == 0;
    //         if (dif[i] == 0) ans += cnt[(z % 2) ^ 1];
    //         cnt[z % 2]++;
    //     }
    //     reverse(all(dif));
    // }
    // int z = count(all(dif), 0);
    // for (int i = 1  ; i <= z; i += 2) ans -= z - i + 1;
    // cout << ans << '\n';
    // vector<int> cnt(2 * n + 1);
    // cnt[n] = 1;
    // vector<int> c(2, 0);
    // rep (i, 0, n) {
    //     // debug(c);
    //     c[s[i] - '0']++;
    //     ans -= cnt[c[0] - c[1] + n];
    //     cnt[c[0] - c[1] + n]++;
    // }
    // vector<int> pre(n), suf(n);
    // int ss = 0;
    // rep (i, 0, n) {
    //     if (i == 0 || s[i] == s[i - 1]) ss++;
    //     pre[i] = ss;
    // }
    // ss = 0;
    // for (int i = n - 1; i >= 0; --i) {
    //     if (i == n - 1 || s[i] == s[i + 1]) ss++;
    //     suf[i] = ss;
    // }
    // rep (i, 0, n - 1) {
    //     if (s[i] != s[i + 1]) ans -= min(pre[i], suf[i + 1]);
    // }

    rep (i, 0, n) {
        int ptr = i;
        while (ptr + 1 < n && s[ptr] != s[ptr + 1]) ptr++;
        int len = ptr - i + 1;
        ans -= len * (len - 1) / 2;
        for (int j = 2; j <= len; j += 2) ans += len - j + 1;
        i = ptr;
    }
    vector<int> cnt(3, 0);
    int sum = 0;
    cnt[sum]++;
    rep (i, 0, n) {
        if (s[i] == '0') sum += 1;
        else sum += 2;
        ans -= cnt[sum % 3];
        cnt[sum % 3]++;
    }
    cout << ans << '\n';
    // 1101 -> 011 -> 10 -> 1
    // 000 -> 10 -> 0
    // 1110111 -> 110011 -> 11101 -> 1100 -> 101 -> 00 -> 1
    // 00 -> 100
    // vector<int> dif; 
    // int ans = n;
    // if (n == 1) {
    //     cout << ans << '\n';
    //     return;
    // }
    // rep (i, 0, n - 1) {
    //     dif.push_back(s[i] ^ s[i + 1]);
    // }
    // vector<int> cnt(4, 0);
    // // cnt[0]++;
    // rep (i, 0, n - 1) {
    //     if (dif[i] == 0) ans += cnt[1];
    //     else ans += cnt[0];
    //     vector<int> nxt(4, 0);   
    //     if (dif[i] == 0) {
    //         nxt[0] += cnt[1];
    //         nxt[1] += cnt[0];
    //         nxt[0]++;
    //     } else {
    //         nxt[1] += cnt[1];
    //         nxt[0] += cnt[0];
    //         nxt[1]++;
    //     } 
    //     cnt = nxt;
    // }
    // cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}