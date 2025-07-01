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
    vector<int> dp(n, IINF);
    bool la = 0; //0: L, 1: R
    int pos = 0;
    dp[1] = 0;
    while (q--) {
        char ch; int to; cin >> ch >> to;
        to--;
        vector<int> g(n, IINF);
        auto tr = [&](int x, int c) -> int {
            return x < c ? x + n : x;
        };
        auto dis = [&](int x, int t, int f) -> int { // 0 clock 1 counter
            return f ? n - (tr(t, x) - x) : tr(t, x) - x;
        };
        rep (i, 0, n) if (pos != i && dp[i] != IINF) { // enumerate previous unmove hand 
            auto calc = [&](int c, int o, int t) -> void {
                if (o == t) {
                    chmin(g[(t + 1) % n], dp[i] + dis(o, (t + 1) % n, 0) + dis(c, t, 0));
                    chmin(g[(t - 1 + n) % n], dp[i] + dis(o, (t - 1 + n) % n, 1) + dis(c, t, 1));
                } else if (c < tr(o, c) && tr(o, c) <= tr(t, c)) {
                    chmin(g[(t + 1) % n], dp[i] + dis(o, (t + 1) % n, 0) + dis(c, t, 0));
                    chmin(g[o], dp[i] + dis(c, t, 1));
                } else {
                    chmin(g[o], dp[i] + dis(c, t, 0));
                    chmin(g[(t - 1 + n) % n], dp[i] + dis(o, (t - 1 + n) % n, 1) + dis(c, t, 1));
                }
            };
            if (ch == 'L') {
                if (!la) {
                    calc(pos, i, to);
                } else {
                    calc(i, pos, to);
                }
            } else {
                if (!la) {
                    calc(i, pos, to);
                } else {
                    calc(pos, i, to);
                }
            }
        }
        la = ch == 'R';
        pos = to;
        swap(dp, g);
    }
    cout << *min_element(all(dp)) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}