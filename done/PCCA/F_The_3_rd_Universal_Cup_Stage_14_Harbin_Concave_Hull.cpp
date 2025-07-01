#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
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
    int n; cin >> n;
    vector<pll> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    auto cross = [&](pll a, pll b) -> ll {
        return a.F * b.S - a.S * b.F;
    };
    auto convex_hull = [&](vector<pll> &Pt) -> vector<pll> {
        int N = Pt.size();
        if (N <= 2) return Pt;
        sort(all(Pt));
        vector<pll> hull;
        rep (i, 0, N) {
            while (hull.size() >= 2 && cross(Pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) >= 0) {
                hull.pop_back();
            }
            hull.pb(Pt[i]);
        }
        int sz = hull.size();
        for(int i = N - 2; i >= 0; --i){
            while(hull.size() > sz && cross(Pt[i] - hull.end()[-2], hull.back() - hull.end()[-2]) >= 0) hull.pop_back();
            hull.pb(Pt[i]);
        }
        hull.pop_back();
        return hull;
    };
    ll A = 0;
    auto hull = convex_hull(pt);
    int sz = hull.size();
    if (sz == n) {
        cout << -1 << '\n';
        return;
    }
    rep (i, 0, sz) A += cross(hull[i], hull[(i + 1) % sz]);
    A = abs(A);
    map<pii, int> mp;
    for (auto p : hull) mp[p] = 1;
    vector<pll> in_pt;
    rep (i, 0, n) {
        if (mp.find(pt[i]) == mp.end()) in_pt.pb(pt[i]);
    }
    auto hull2 = convex_hull(in_pt);
    int sz2 = hull2.size();
    ll sub = A;
    auto calc = [&](pll a, pll b, pll c) -> ll {
        return abs(cross(b - a, c - a));
    };
    auto mv = [&](int p, int d) -> int {
        p += d;
        if (p < 0) p += sz2;
        if (p >= sz2) p -= sz2;
        return p;
    };
    int ptr = 0;
    rep (i, 0, sz2) if (calc(hull[0], hull[1], hull2[i]) < calc(hull[0], hull[1], hull2[ptr])) {
        ptr = i;
    }
    rep (i, 0, sz) {
        int j = (i + 1) % sz;
        while (calc(hull[i], hull[j], hull2[ptr]) > calc(hull[i], hull[j], hull2[mv(ptr, 1)])) ptr = mv(ptr, 1);
        while (calc(hull[i], hull[j], hull2[ptr]) > calc(hull[i], hull[j], hull2[mv(ptr, -1)])) ptr = mv(ptr, -1);
        chmin(sub, calc(hull[i], hull[j], hull2[ptr]));
    }
    cout << A - sub << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}