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

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0, f = 1; char c = GU; while (c == ' ' || c == '\n') {c = GU;} if (c == '-') {f = -1, c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return f * re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

void solve() {
    int n = in(), k = in(), e = in();
    vector<int> hole(e + 1, 0), s(k);
    rep (i, 0, n) {
        int a = in();
        hole[a] = 1;
    }
    rep (i, 0, k) s[i] = in();
    sort(all(s), greater<int>());
    vector<int> id(e + 1, -1);
    vector<bool> ok(e - n + 1, 0);
    vector dp(e - n + 1, vector<int>(k, 0));
    vector<int> opt(e - n + 1, -1), who(e - n + 1);
    id[0] = 0;
    who[0] = 0;
    ok[0] = 1; 
    int cnt = 0;
    rep (i, 1, e + 1) {
        if (hole[i]) continue;
        cnt++;
        id[i] = cnt;
        who[cnt] = i;
        rep (j, 0, k) {
            if (i - s[j] < 0) continue;
            if (hole[i - s[j]] || !ok[id[i - s[j]]]) continue;
            dp[id[i - s[j]]][j] += 1;
            if (!ok[id[i]]) {
                dp[id[i]] = dp[id[i - s[j]]];
                opt[id[i]] = id[i - s[j]];
                ok[id[i]] = 1;
            } else {
                rep (l, 0, k) {
                    if (dp[id[i - s[j]]][l] == dp[id[i]][l]) continue;
                    if (dp[id[i - s[j]]][l] > dp[id[i]][l]) {
                        dp[id[i]] = dp[id[i - s[j]]];
                        opt[id[i]] = id[i - s[j]];
                    }
                    break;
                }
            }
            dp[id[i - s[j]]][j] -= 1;
        }
    }
    if (!ok[id[e]]) {
        cout << -1 << '\n';
        return;
    }
    vector<int> ans;
    int cur = id[e];
    while (cur != 0) {
        ans.pb(who[cur]);
        cur = opt[cur];
    }
    cout << ans.size() << '\n';
    while (!ans.empty()) {
        cout << ans.back() << ' ';
        ans.pop_back();
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