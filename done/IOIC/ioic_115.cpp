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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

int ans[MAXN], vis[MAXN], lp[MAXN];

int my_lcm(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return 1LL * a * b / __gcd(a, b);
}

void solve() {
    vector<int> prime;
    rep (i, 0, 1000001) lp[i] = 1; 
    rep (i, 2, 1000001) {
        if (!vis[i]) {
            lp[i] = i;
            prime.pb(i);
        }
        for (int p : prime) {
            if (i * p > 1000000) break;
            vis[i * p] = 1;
            lp[i * p] = p;
            if (p == lp[i]) break;
        }
    }
    rep (i, 1, 1000001) {
        if (i == 1 || i % 2 == 0 || i % 5 == 0) ans[i] = -1;
        for (int j = 1; i * j < 1000000; j++) {
            if (vis[i * j + 1] || ans[i * j + 1] != 0) continue;
            if (fpow(10, i, i * j + 1) == 1) ans[i * j + 1] = i;
        }
        if (ans[i] != -1 && vis[i]) {
            int x = i;
            while (x > 1) {
                int d = lp[x], cnt = 0;
                while (x % d == 0) {
                    cnt++;
                    x /= d;
                }
                if (d == 3 || d == 487) cnt--;
                ans[i] = my_lcm(ans[i], fpow(d, max(0, cnt - 1)) * ans[d]);
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        cout << ans[n] << '\n';
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