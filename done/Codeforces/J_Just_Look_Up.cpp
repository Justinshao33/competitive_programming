#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
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
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

#define pdd pair<double, double>

pdd operator + (const pdd &p1, const pdd &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pdd operator - (const pdd &p1, const pdd &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

double cross(pdd a, pdd b) {
    return a.fi * b.se - a.se * b.fi;
}

double ori(pdd o, pdd a, pdd b) {
    return cross(a - o, b - o);
}

vector<pdd> BuildHull(vector<pdd> pt) {
    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());
    if (pt.size() <= 2) return pt;
    vector<pdd> hull;
    int sz = 1;
    rep (t, 0, 2) {
        rep (i, t, ssize(pt)) {
            while (ssize(hull) > sz && ori(hull.end()[-2], pt[i], hull.back()) >= 0)
                hull.pop_back();
            hull.pb(pt[i]);
        }
        sz = ssize(hull);
        reverse(all(pt));
    }
    hull.pop_back();
    return hull;
}

void rotate(double &a, double &b, double ang) {
    tie(a, b) = make_pair(cos(ang) * a - sin(ang) * b, sin(ang) * a + cos(ang) * b);
}

double sq(double x) {
    return x * x;
}

const double eps = 1E-9;

void solve() {
    int n; cin >> n;
    vector<array<int, 3>> pt(n);
    rep (i, 0, n) rep (j, 0, 3) cin >> pt[i][j];
    rep (i, 0, n) {
        int g = gcd(pt[i][0], gcd(pt[i][1], pt[i][2]));
        if (g) rep (j, 0, 3) pt[i][j] /= g;
    }
    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());
    n = ssize(pt);
    vector<array<double, 3>> upt;
    {
        rep (i, 0, n) {
            double len = sqrt(sq(pt[i][0]) + sq(pt[i][1]) + sq(pt[i][2]));
            upt.pb({1. * pt[i][0] / len, 1. * pt[i][1] / len, 1. * pt[i][2] / len});
        }
    }
    double ans = 0;
    rep (i, 0, n) {
        auto [ox, oy, oz] = upt[i];
        double xy = atan2(oy, ox);
        rotate(ox, oy, -xy);
        double xz = atan2(oz, ox);
        vector<pdd> proj;
        proj.pb({0, 0});
        rep (j, 0, n) if (i != j) {
            auto [x, y, z] = upt[j];
            rotate(x, y, -xy);
            rotate(x, z, -xz);
            // pt[j] - pt[i] = {x - 1, y, z}
            // 1 + t(x - 1) = 0 -> t = 1 / (1 - x)
            // {0, 0 + y / (1 - x), 0 + z / (1 - x)};
            proj.pb({y / (1 - x), z / (1 - x)});
        }
        auto hull = BuildHull(proj);
        rep (j, 0, ssize(hull)) {
            pdd &a = hull[j], &b = hull[(j + 1) % ssize(hull)];
            // h = A / w
            double h = cross(a, b);
            if (h == 0) {
                ans = 90;
                break;
            }
            h /= sqrt(sq((a - b).fi) + sq((a - b).se));
            double ang = (numbers::pi - 2 * atan(h)) / 2;
            ans = max(ans, ang / numbers::pi * 180);
        }
    }
    cout << fixed << setprecision(15) << ans << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}