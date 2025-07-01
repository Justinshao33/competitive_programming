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
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> pre(n + 1), suf(n + 2);
    vector<int> ml(n + 1, IINF), mr(n + 1, -1);
    pre[0] = 0;
    ml[0] = 0;
    rep (i, 0, n) {
        pre[i + 1] = pre[i] + (s[i] == '1');
        if (s[i] == '/' && ml[pre[i + 1]] == IINF) ml[pre[i + 1]] = i + 1;
    }
    for (int i = n - 1; i > 0; i--) {
        if (ml[i] == IINF) ml[i] = ml[i + 1];
    }
    suf[n + 1] = 0;
    mr[0] = n + 1;
    for (int i = n; i > 0; --i) {
        suf[i] = suf[i + 1] + (s[i - 1] == '2');
        if (s[i - 1] == '/' && mr[suf[i]] == -1) mr[suf[i]] = i;
    }
    for (int i = n - 1; i > 0; i--) {
        if (mr[i] == -1) mr[i] = mr[i + 1];
    }
    // cout << pre;
    // cout << suf;
    // cout << ml[pre[1 - 1] + 2] << ' ' << mr[suf[7 + 1] + 2] << '\n';
    while (q--) {
        int L, R; cin >> L >> R;
        if (pre[R] - pre[L - 1] + suf[L] - suf[R + 1] == R - L + 1) {
            cout << 0 << '\n';
            continue;
        }
        int l = 0, r = R - L + 2;
        while (r - l > 1) {
            int mid = l + r >> 1;
            if (ml[pre[L - 1] + mid] <= mr[suf[R + 1] + mid]) l = mid;
            else r = mid;
        }
        cout << l * 2 + 1 << '\n';
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