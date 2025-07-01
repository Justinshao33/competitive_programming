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

void solve(int n) {
    vector<pll> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    // need vector<pll> pt
    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());
    n = pt.size();
    if (n <= 2) {
        if (n == 1) cout << 1 << '\n' << pt[0].fi << ' ' << pt[0].se << '\n';
        else {
            cout << 2 << '\n';
            rep (i, 0, 2) cout << pt[i].fi << ' ' << pt[i].se << '\n';
        }
        return;
    }
    auto cross = [&](pll a, pll b) -> ll {
        return a.fi * b.se - a.se * b.fi;
    };
    vector<pll> hull;
    rep (i, 0, n) {
        while (hull.size() >= 2 && cross(pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) >= 0) {
            hull.pop_back();
        }
        hull.pb(pt[i]);
    }
    int sz = hull.size();
    for(int i = n - 2; i >= 0; --i){
        while(hull.size() > sz && cross(pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) >= 0) hull.pop_back();
        hull.pb(pt[i]);
    }
    hull.pop_back();
    sz = hull.size();
    cout << sz << '\n';
    for (auto [x, y] : hull) cout << x << ' ' << y << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int n;
    while (cin >> n && n != 0) {
        solve(n);
    }
}