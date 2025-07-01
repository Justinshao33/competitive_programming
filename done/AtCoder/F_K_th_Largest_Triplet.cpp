#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n, k; cin >> n >> k;
    vector a(3, vector<ll>(n));
    rep (i, 0, 3) rep (j, 0, n) cin >> a[i][j];
    rep (i, 0, 3) sort(all(a[i]), greater<ll>());
    priority_queue<tuple<ll, int, int, int>> pq;
    pq.push({a[0][0] * a[1][0] + a[0][0] * a[2][0] + a[1][0] * a[2][0], 0, 0, 0});
    map<tuple<int, int, int>, int> mp;
    while (k) {
        auto [v, b, c, d] = pq.top();
        pq.pop();
        if (mp[{b, c, d}]) continue;
        mp[{b, c, d}] = 1;
        k--;
        // cout << v << ' ';
        if (k == 0) {
            cout << v << '\n';
            return;
        }
        if (b != n - 1) pq.push({a[0][b + 1] * a[1][c] + a[0][b + 1] * a[2][d] + a[1][c] * a[2][d], b + 1, c, d});
        if (c != n - 1) pq.push({a[0][b] * a[1][c + 1] + a[0][b] * a[2][d] + a[1][c + 1] * a[2][d], b, c + 1, d});
        if (d != n - 1) pq.push({a[0][b] * a[1][c] + a[0][b] * a[2][d + 1] + a[1][c] * a[2][d + 1], b, c, d + 1});
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