// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

#ifdef LOCAL
#define ZTMYACANESOCUTE freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

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
    vector a(n, vector<ll>(n));
    rep (i, 0, n) rep (j, 0, n) cin >> a[i][j];
    vector dis(n, vector<ll>(n, LINF));
    vector<vector<vector<ll>>> ans(n);
    auto dfs = [&](auto self, int l, int r) -> void {
        if (l == r) {
            ans[l] = dis;
            return;
        }
        auto tmp = dis;
        int mid = l + r >> 1;
        rep (k, l, mid + 1) {
            rep (i, 0, n) {
                chmin(dis[k][i], a[k][i]);
                chmin(dis[i][k], a[i][k]);
            }
            rep (i, 0, n) rep (j, 0, n) {
                chmin(dis[i][j], dis[i][k] + dis[k][j]);
                chmin(dis[j][i], dis[j][k] + dis[k][i]);
            }
        }
        self(self, mid + 1, r);
        dis = tmp;
        rep (k, mid + 1, r + 1) {
            rep (i, 0, n) {
                chmin(dis[k][i], a[k][i]);
                chmin(dis[i][k], a[i][k]);
            }
            rep (i, 0, n) rep (j, 0, n) {
                chmin(dis[i][j], dis[i][k] + dis[k][j]);
                chmin(dis[j][i], dis[j][k] + dis[k][i]);
            }
        }
        self(self, l, mid);
    };
    dfs(dfs, 0, n - 1);
    while (q--) {
        int s, t, p; cin >> s >> t >> p;
        s--, t--, p--;
        cout << ans[p][s][t] << '\n';
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