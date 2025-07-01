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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, K; ll P; cin >> n >> P >> K;
    vector<vector<int>> a(n, vector<int>(n));
    rep (i, 0, n) rep (j, 0, n) cin >> a[i][j];
    auto check = [&](ll x, int t) -> bool {
        vector<vector<ll>> dis(n, vector<ll>(n, LINF));
        rep (i, 0, n) rep (j, 0, n) {
            dis[i][j] = (a[i][j] == -1 ? x : a[i][j]);
        }
        rep (k, 0, n) rep (i, 0, n) rep (j, 0, n) {
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
        int cnt = 0;
        rep (i, 0, n) rep (j, i + 1, n) {
            cnt += dis[i][j] <= P;
        }
        if (!t) return cnt <= K;
        else return cnt >= K;
    };
    ll l = 0, r = IINF;
    while (r - l > 1) {
        ll mid = l + r >> 1;
        if (check(mid, 0)) r = mid;
        else l = mid;
    }
    ll l2 = 0, r2 = IINF;
    while (r2 - l2 > 1) {
        ll mid = l2 + r2 >> 1;
        if (check(mid, 1)) l2 = mid;
        else r2 = mid;
    }
    if (check(IINF, 0) && check(IINF, 1)) cout << "Infinity\n";
    else if (check(IINF, 1)) cout << 0 << '\n';
    else cout << r2 - r << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}