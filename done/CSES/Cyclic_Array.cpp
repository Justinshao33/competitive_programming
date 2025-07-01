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
    int n; ll k; cin >> n >> k;
    vector<ll> a(n << 1);
    rep (i, 0, n) cin >> a[i], a[i + n] = a[i];
    vector to(n << 1, vector<ll>(20, 2 * n));
    int ptr = 0;
    ll sum = 0;
    rep (i, 0, n << 1) {
        while (ptr < min(2 * n, i + n) && sum + a[ptr] <= k) {
            sum += a[ptr];
            ptr++;
        }
        to[i][0] = ptr;
        sum -= a[i];
    }
    rep (j, 1, 20) rep (i, 0, n << 1) {
        if (to[i][j - 1] == 2 * n) to[i][j] = 2 * n;
        else to[i][j] = to[to[i][j - 1]][j - 1];
    } 
    int ans = n;
    rep (i, 0, n) {
        int cnt = 1, cur = i, len = 0;
        for (int j = 19; j >= 0; --j) {
            if (len + to[cur][j] - cur < n) {
                cnt += 1 << j;
                // cout << i << ' ' << cur << ' ' << j << ' ' << to[cur][j] << ' ' << cnt << '\n';
                len += to[cur][j] - cur;
                cur = to[cur][j] % n;
            }
        }
        chmin(ans, cnt);
    }
    cout << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}