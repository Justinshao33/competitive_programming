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
    int n, m, q; cin >> n >> m >> q;
    vector<int> l(n * m), r(n * m), u(n * m), d(n * m);
    rep (i, 0, n) rep (j, 0, m) {
        l[i * m + j] = j;
        r[i * m + j] = j;
        u[i * m + j] = i;
        d[i * m + j] = i;
    }
    int ans = n * m;
    vector g(n, vector<int>(m, 1));
    while (q--) {
        int rr, c; cin >> rr >> c;
        rr--, c--;
        int cur = rr * m + c;
        if (g[rr][c]) {
            g[rr][c]--;
            ans--;
            l[cur]--;
            r[cur]++;
            u[cur]--;
            d[cur]++;
        } else {
            int L = l[cur], R = r[cur], U = u[cur], D = d[cur];
            while (L >= 0 && g[rr][L] == 0) {
                l[cur] = l[rr * m + L];
                L = l[rr * m + L];
            }
            if (L >= 0) {
                l[rr * m + L]--;
                l[cur] = l[rr * m + L];
                g[rr][L]--;
                ans--;
            } 
            while (R < m && g[rr][R] == 0) {
                r[cur] = r[rr * m + R];
                R = r[rr * m + R];
            }
            if (R < m) {
                r[rr * m + R]++;
                r[cur] = r[rr * m + R];
                g[rr][R]--;
                ans--;
            } 
            while (U >= 0 && g[U][c] == 0) {
                u[cur] = u[U * m + c];
                U = u[U * m + c];
            }
            if (U >= 0) {
                u[U * m + c]--;
                u[cur] = u[U * m + c];
                g[U][c]--;
                ans--;
            } 
            while (D < n && g[D][c] == 0) {
                d[cur] = d[D * m + c];
                D = d[D * m + c];
            }
            if (D < n) {
                d[D * m + c]++;
                d[cur] = d[D * m + c];
                g[D][c]--;
                ans--;
            } 
        }
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