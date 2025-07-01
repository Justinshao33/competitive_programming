#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
    int n; cin >> n;
    vector<pll> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    // need vector<pll> pt
    sort(all(pt));
    if (n <= 2) {
        cout << "0\n";
        return;
    }
    auto cross = [&](pll a, pll b) -> ll {
        return a.fi * b.se - a.se * b.fi;
    };
    vector<pll> hull;
    rep (i, 0, n) {
        while (hull.size() >= 2 && cross(pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) > 0) {
            hull.pop_back();
        }
        hull.pb(pt[i]);
    }
    int sz = hull.size();
    for(int i = n - 2; i >= 0; --i){
        while(hull.size() > sz && cross(pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) > 0) hull.pop_back();
        hull.pb(pt[i]);
    }
    sz = hull.size();
    ll ans = 0;
    if (sz <= 2) {
        cout << "0\n";
        return;
    }
    auto nxt = [&](int x) -> int {
        return x == sz - 1 ? 0 : x + 1;
    };
    auto area = [&](int i, int j, int k) -> ll {
        return abs(cross(hull[i] - hull[k], hull[j] - hull[k]));
    };
    rep (i, 0, sz) {
        int ptr = nxt(i);
        for (int j = nxt(nxt(i)); nxt(j) != i; j = nxt(j)) {
            while (nxt(ptr) != j && area(i, j, ptr) < area(i, j, nxt(ptr))) ptr = nxt(ptr);
            ans = max(ans, area(i, j, ptr));
        }
    }
    if (ans & 1) cout << ans / 2 << ".5\n";
    else cout << ans / 2 << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}