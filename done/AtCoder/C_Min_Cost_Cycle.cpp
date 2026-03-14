#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n; cin >> n;
    vector<pii> edge;
    rep (i, 1, n + 1) {
        int a, b; cin >> a >> b;
        edge.push_back({a, i});
        edge.push_back({b, -i});
    }
    sort(all(edge));
    int ans = LINF, sum = 0;
    vector<int> ty(n);
    int A = 0, B = 0;
    auto upd = [&](int i, int v) -> void {
        int u = abs(edge[i].se) - 1;
        sum += v * edge[i].fi;
        if (ty[u] == 1) A -= 1;
        if (ty[u] == 2) B -= 1;
        if (edge[i].se > 0) ty[u] += 1 * v;
        else ty[u] += 2 * v;
        if (ty[u] == 1) A += 1;
        if (ty[u] == 2) B += 1;
    };
    rep (i, 0, n) upd(i, 1);
    auto ok = [&]() -> bool { return A == 0 || B == 0 || A + B < n; };
    auto sw = [&](int i, int j) -> void {
        upd(i, -1);
        upd(j, 1);
        if (ok()) chmin(ans, sum);
    };
    if (ok()) chmin(ans, sum);
    sw(n - 1, n);
    sw(n - 2, n - 1);
    sw(n - 1, n - 2);
    sw(n, n + 1);
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}