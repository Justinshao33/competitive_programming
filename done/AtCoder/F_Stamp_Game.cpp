#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, m; cin >> n >> m;
    vector<int> h(2), w(2);
    rep (i, 0, 2) cin >> h[i] >> w[i];
    chmin(h[1], h[0]);
    chmin(w[1], w[0]);
    vector a(n + 1, vector<ll>(m + 1));
    rep (i, 1, n + 1) rep (j, 1, m + 1) cin >> a[i][j];
    rep (i, 1, n + 1) rep (j, 1, m + 1) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    auto calc = [&](int x, int y, int t) -> ll {
        return a[x][y] - a[x - h[t]][y] - a[x][y - w[t]] + a[x - h[t]][y - w[t]];
    };
    vector col_mx(n + 1, vector<ll>(m + 1, 0));
    rep (j, w[1], m + 1) {
        deque<int> dq;
        rep (i, h[1], n + 1) {
            if (!dq.empty() && i - dq.front() > h[0] - h[1]) dq.pop_front();
            ll cur = calc(i, j, 1);
            while (!dq.empty() && calc(dq.back(), j, 1) <= cur) dq.pop_back(); 
            dq.pb(i);
            col_mx[i][j] = calc(dq.front(), j, 1);
        }
    }
    ll ans = 0;
    rep (i, h[0], n + 1) {
        deque<int> dq;
        rep (j, w[1], w[0]) {
            if (!dq.empty() && j - dq.front() > w[0] - w[1]) dq.pop_front();
            while (!dq.empty() && col_mx[i][dq.back()] <= col_mx[i][j]) dq.pop_back(); 
            dq.pb(j);
        }
        rep (j, w[0], m + 1) {
            if (!dq.empty() && j - dq.front() > w[0] - w[1]) dq.pop_front();
            while (!dq.empty() && col_mx[i][dq.back()] <= col_mx[i][j]) dq.pop_back(); 
            dq.pb(j);
            chmax(ans, calc(i, j, 0) - col_mx[i][dq.front()]);
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