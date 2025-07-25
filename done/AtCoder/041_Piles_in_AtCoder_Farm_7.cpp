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

ll cross(pll a, pll b) {
    return a.F * b.S - a.S * b.F;
}

void solve() {
    int n; cin >> n;
    vector<pll> pt(n);
    rep (i, 0, n) cin >> pt[i].F >> pt[i].S;
    sort(all(pt));
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
    hull.pop_back();
    sz = hull.size();
    // Pick's Theorem: A = i + b/2 - 1 => 2A = 2i + b - 2
    ll A = 0, b = 0;
    rep (i, 1, sz - 1) {
        A += cross(hull[i] - hull[0], hull[i + 1] - hull[0]);
    }
    A = abs(A);
    rep (i, 0, sz) {
        b += __gcd(abs(hull[i + 1].F - hull[i].F), abs(hull[i + 1].S - hull[i].S));
    }
    cout << (A - b + 2) / 2 + b - n << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}