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
    vector w(n, vector<ll>(n, LINF));
    vector<pii> edge;
    vector<ll> c(m);
    rep (i, 0, m) {
        int a, b; cin >> a >> b >> c[i];
        a--, b--;
        w[a][b] = w[b][a] = c[i];
        edge.pb({a, b});
    }
    vector<tuple<int, int, int>> que(q);
    for (auto &[t, x, y] : que) {
        cin >> t >> x;
        y = 0;
        if (t == 2) cin >> y;
        x--, y--;
        if (t == 1) {
            auto [a, b] = edge[x];
            w[a][b] = w[b][a] = LINF;
        }
    }
    vector<ll> ans;
    vector dis(n, vector<ll>(n, LINF));
    rep (i, 0, n) dis[i][i] = 0;
    rep (i, 0, n) rep (j, 0, n) chmin(dis[i][j], w[i][j]);
    rep (k, 0, n) rep (i, 0, n) rep (j, 0, n) chmin(dis[i][j], dis[i][k] + dis[k][j]);
    reverse(all(que));
    for (auto [t, x, y] : que) {
        if (t == 1) {
            auto [a, b] = edge[x];
            w[a][b] = w[b][a] = c[x];
            chmin(dis[a][b], w[a][b]);
            chmin(dis[b][a], w[b][a]);
            rep (i, 0, n) rep (j, 0, n) chmin(dis[i][j], dis[i][a] + dis[a][b] + dis[b][j]);
            rep (i, 0, n) rep (j, 0, n) chmin(dis[i][j], dis[i][b] + dis[b][a] + dis[a][j]);
        } else {
            if (dis[x][y] == LINF) ans.pb(-1);
            else ans.pb(dis[x][y]);
        }
    }
    while (!ans.empty()) {
        cout << ans.back() << '\n';
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